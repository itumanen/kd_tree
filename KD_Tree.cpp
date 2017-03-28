#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "KD_Tree.h"

using namespace std;

// DEFAULT CONSTRUCTOR
KD_Tree::KD_Tree() {
	setRoot(NULL); 
	setHeight(0); 
	setNumNodes(0); 
}

// CONSTRUCTOR 
KD_Tree::KD_Tree(vector<point2D> points) {

	// check that input is valid and numPoints is strictly positive
	// assert(points);
	assert(points.size() > 0);

	setPts(points); // save points vector in tree
	setNumNodes(points.size()); 
	initializeHeight();

	if (num_nodes == 1) {

		Node* root = new Node(pts[0]);
		root->setNumPoints(num_nodes);
		root->setDepth(getHeight());
		setRoot(root); // note: Node type set to LEAF by default

	} else if (num_nodes == 2) {  // Case: no right side

		Node* root = new Node(pts[1]);
		root->setNumPoints(num_nodes);
		root->setDepth(getHeight());
		root->setType(INITIAL_CUT);
		setRoot(root);

		Node* left = new Node(pts[0]); // type set to LEAF by default
		left->setNumPoints(num_nodes - 1);
		left->setDepth(getHeight() + 1);
		root->setLeft(left);

		incrementHeight();

	} else {

		// Initialize root node
		int median = num_nodes / 2; 

		Node* root = new Node(points[median]); 
		root->setType(INITIAL_CUT);
		root->setNumPoints(num_nodes);
		root->setDepth(getHeight());
		setRoot(root);

		// declare vectors for sorted arrays
		vector<point2D> x_left, x_right, y_left, y_right;

		// initialize by copying data from pts
		// for loops done separately because left/right arrays could
		// be of different sizes 
		// if the number of points is even, the right array is one 
		// index smaller than the left
		// Example:
		// 0 1 2 3 4, median index 2 --> left [0,1] right [3,4]
		// 0 1 2 3, median 2 --> left [0,1] right [3]
		for (int i = 0; i < median; i++) {
			x_left.push_back(pts[i]);
			y_left.push_back(pts[i]);
		} 

		for (int i = median + 1; i < num_nodes; i++) {
			x_right.push_back(pts[i]);
			y_right.push_back(pts[i]);
		}

		sort(x_left.begin(), x_left.end(), sortByX);
		sort(x_right.begin(), x_right.end(), sortByX);
		sort(y_left.begin(), y_left.end(), sortByY);
		sort(y_right.begin(), y_right.end(), sortByY);

		// BUILD TREE RECURSIVELY
		if (DEBUG) {
			printf("RECURSIVE CALL\n");
		}
		root->setLeft(build_kd_tree(x_left, y_left, getHeight() + 1 ));
		root->setRight(build_kd_tree(x_right, y_right, getHeight() + 1));
		printf("RECURSIVE CALL HERE\n"); fflush(stdout);

		// setHeight(computeHeight());

	}

}


Node* KD_Tree::build_kd_tree(vector<point2D> points_by_x, vector<point2D> points_by_y, int depth) {

	
	setHeight(depth);
	
	int num = points_by_x.size();
	int median = num / 2;

	// if (num == 0) {
	// 	return NULL;
	// }

	if (DEBUG) {
		printf("num is %d\n", num);
		printf("median is %d\n", median);
	}

	// If there are only two points in the vectors that are passed in,
	// then the first point is the left child of the second, and the second has no right node. 
	// thus, we don't have a right "side" and can't make a recursive call on it.
	bool rightNode = true;
	if (median == num) { 
		rightNode = false; 
	}

	// BASE CASE: if only one point, return leaf containing point
	if (num == 1) {

		printf("LEAF at depth %d\n", depth);
		assert(equals(points_by_x[0], points_by_y[0])); // TODO IF THIS FAILS DEBUG!! --> print statement
		Node* node = new Node(points_by_x[0]); // default type is LEAF
		node->setNumPoints(num);
		node->setDepth(depth);
		node->setLeft(NULL);
		node->setRight(NULL);
		return node;

	} else if (depth % 2 != 0 && num > 1) {   // height of tree is odd at this node

		// create new node and add median point to the tree
		Node* node = new Node(points_by_x[median]);
		node->setType(VERTICAL);
		node->setNumPoints(median);
		node->setDepth(depth);

		// cut type is vertical, so split x-array into two parts and
		// sort the parts by y-coordinate
		vector<point2D> x_left, x_right, y_left, y_right;

		// COPY DATA
		for (int i = 0; i < median; i++) {
			x_left.push_back(pts[i]);
			y_left.push_back(pts[i]);
		} 
		for (int i = median + 1; i < num; i++) {
			x_right.push_back(pts[i]);
			y_right.push_back(pts[i]);
		}

		// SORT BY Y-COORDINATE
		sort(y_left.begin(), y_left.end(), sortByY);
		sort(y_right.begin(), y_right.end(), sortByY);

		// recursive calls
		node->setLeft(build_kd_tree(x_left, y_left, depth + 1));
		node->setRight(build_kd_tree(x_right, x_right, depth + 1));

		return node;

	} else if (depth % 2 == 0 && num > 1) {   // depth is even and num > 1

		// add node to the tree
		Node* node = new Node(points_by_y[median]);
		node->setType(HORIZONTAL);
		node->setNumPoints(median);
		node->setDepth(depth);

		// cut type is horizontal, so split y-array into two parts and
		// sort the parts by x-coordinate
		// LEFT refers to the part above the horizontal line, RIGHT
		// refers to the points below it
		vector<point2D> x_left, x_right, y_left, y_right;

		// COPY DATA
		for (int i = 0; i < median; i++) {
			x_left.push_back(pts[i]);
			y_left.push_back(pts[i]);
		} 
		for (int i = median + 1; i < num; i++) {
			x_right.push_back(pts[i]);
			y_right.push_back(pts[i]);
		}

		// SORT BY X-COORDINATE
		sort(x_left.begin(), x_left.end(), sortByX);
		sort(x_right.begin(), x_right.end(), sortByX);

		// recursive call
		node->setLeft(build_kd_tree(x_left, y_left, depth + 1));
		node->setRight(build_kd_tree(x_right, x_right, depth + 1));

		return node;
	}

	// ELSE
	// if the arrays are empty (ex: there is no right leaf for Node n), 
	// return NULL to set n->right to NULL
	return NULL;
}

// traverses tree from root to leftmost leaf and returns height of tree
// if n is even, then the "left side" array is larger than the right – thus,
// the longest path from root to leaf is the leftmost one
int KD_Tree::computeHeight() {

	Node* temp = root;
	int height = 1;

	if (DEBUG){
		printf("height is %d\n", getHeight());
		printf("temp->isLeaf returns %d\n", temp->isLeaf());
		printf("temp->left is %d\n", temp->getLeft()->isLeaf());
	}

	while (!temp->isLeaf()) {
		height++; 
		temp = temp->getLeft();
	}
	return height;

}

// PRINT FUNCTIONS

void KD_Tree::printInfo() {
	printf("\nTREE INFO\n");
	printNumNodes();
	printf("Height: %d\n", getHeight() );
	printf("Root: ");
	root->printInfo(); // flushes STDOUT
}

void KD_Tree::printNumNodes() {
	printf("Number of nodes: %d\n", getNumNodes());
}

// recurse through entire tree and call destructors of all nodes
void KD_Tree::deallocate_tree(Node* node) {

	if (node->isLeaf()) {
		return;
	}
	
	deallocate_tree(node->getLeft());
	deallocate_tree(node->getRight());
	node->~Node();

}

// DESTRUCTOR
KD_Tree::~KD_Tree() {

	// delete all nodes of the tree
	deallocate_tree(getRoot());
	delete(getRoot());

}