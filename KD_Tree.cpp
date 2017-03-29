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

	// check that input is valid / the number of points is strictly positive
	assert(points.size() > 0);
	sort(points.begin(), points.end(), sortByX); // sort input vector by x-coords
	setPts(points); // save points as initialized to class
	setNumNodes(points.size()); 
	initializeHeight();

	if (num_nodes == 1) {

		Node* root = new Node(pts[0]);
		root->setDepth(getHeight());
		root->setRoot(true);
		setRoot(root); // note: Node type set to LEAF by default

	} else if (num_nodes == 2) {  // Case: no right side

		Node* root = new Node(pts[1]);
		root->setDepth(getHeight());
		root->setType(INITIAL_CUT);
		root->setRoot(true);
		setRoot(root);

		Node* left = new Node(pts[0]); // type set to LEAF by default
		left->setDepth(getHeight() + 1);
		root->setLeft(left);

		setHeight(computeHeight());

	} else {

		// Initialize root node
		int median = num_nodes / 2; 

		Node* root = new Node(points[median]); 
		root->setType(INITIAL_CUT);
		root->setDepth(getHeight());
		root->setRoot(true);
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
			printf("RECURSIVE CALL\n"); fflush(stdout);
		}

		// use the depth of the root (height of the tree at root node) for
		// recursive call because the height is updated during the call
		root->setLeft(build_kd_tree(x_left, y_left, root->getDepth() + 1 ));
		root->setRight(build_kd_tree(x_right, y_right, root->getDepth() + 1));

		// redundant, but was implemented as a sanity check
		setHeight(computeHeight());

	}

	// Clear pts for a clean start
	// Traverse tree and save the points in level order
	pts.clear();
	levelOrderPts(); 

}



// HELPER FUNCTIONS
/*
Recursively builds KD tree; takes vectors of points sorted by x/y and the current depth (height)
of the tree and returns a pointer to a node, which is stored as the left or the right node of the parent.
Base cases: 
- Vector of points only contains one point -- this is a leaf; the children of this node are NULL.
- Vector of points is empty -- this happens AFTER the vector only has two points. That node will only
	have a left child and will pass an empty vector to the recursive call. This could be handled within 
	the if/else block but to ensure that the function exits with a return value, the code for this base 
	executes if the first three conditions fail. 
IF/ELSE block:
- If the vector only has one point (base case)
- If the vector has more than one point and the depth is odd, then the cut type is VERTICAL. 
- If the vector has more than one point and the depth is even, then the cut type is HORIZONTAL.
PARAMETERS
- vectors of the same n points sorted by their x-coordinates, and sorted by their y-coordinates. The size
	of these is approximately half (+/- 1) of the size of the vectors at the previous level.
- the value of depth is the height of the tree AFTER the new nodes have been created, so that the height of the 
	tree does not change if the vector is empty (and no node is added)
*/ 
Node* KD_Tree::build_kd_tree(vector<point2D> points_by_x, vector<point2D> points_by_y, int depth) {

	int num = points_by_x.size();
	int median = num / 2;

	// BASE CASE: if only one point, return leaf containing point
	// If the height of the tree is ODD at the new node, then the cut type is VERTICAL
	// ie, at the root the height is 1 and the initial cut is VERTICAL
	// Thus if the height is even then the cut type is HORIZONTAL
	if (num == 1) {

		if (DEBUG) printf("LEAF at depth %d\n", depth);
		assert(equals(points_by_x[0], points_by_y[0])); // TODO IF THIS FAILS DEBUG!! --> print statement
		Node* node = new Node(points_by_x[0]); // default type is LEAF
		node->setDepth(depth);
		node->setLeft(NULL); // redundant but here for sanity checks
		node->setRight(NULL);
		
		setHeight(depth);
		return node;

	} else if (depth % 2 != 0 && num > 1) {   // height of tree is odd at this node

		// if (DEBUG) printf("VERTICAL at depth%d\n", depth);

		// create new node and add median point to the tree
		Node* node = new Node(points_by_x[median]);
		node->setType(VERTICAL);
		node->setDepth(depth);

		// cut type is vertical, so split x-array into two parts and
		// sort the parts by y-coordinate
		vector<point2D> x_left, x_right, y_left, y_right;

		// COPY DATA
		for (int i = 0; i < median; i++) {
			x_left.push_back(points_by_x[i]);
			y_left.push_back(points_by_x[i]);
		} 
		for (int i = median + 1; i < num; i++) {
			x_right.push_back(points_by_x[i]);
			y_right.push_back(points_by_x[i]);
		}

		// SORT BY Y-COORDINATE
		sort(y_left.begin(), y_left.end(), sortByY);
		sort(y_right.begin(), y_right.end(), sortByY);

		// recursive calls
		node->setLeft(build_kd_tree(x_left, y_left, depth + 1));
		node->setRight(build_kd_tree(x_right, x_right, depth + 1));

		setHeight(depth);
		return node;

	} else if (depth % 2 == 0 && num > 1) {   // depth is even and num > 1

		// if (DEBUG) printf("HORIZONTAL at depth%d\n", depth);

		// add node to the tree
		Node* node = new Node(points_by_y[median]);
		node->setType(HORIZONTAL);
		node->setDepth(depth);

		// cut type is horizontal, so split y-array into two parts and
		// sort the parts by x-coordinate
		// LEFT refers to the part above the horizontal line, RIGHT
		// refers to the points below it
		vector<point2D> x_left, x_right, y_left, y_right;

		// COPY DATA
		for (int i = 0; i < median; i++) {
			x_left.push_back(points_by_y[i]);
			y_left.push_back(points_by_y[i]);
		} 
		for (int i = median + 1; i < num; i++) {
			x_right.push_back(points_by_y[i]);
			y_right.push_back(points_by_y[i]);
		}

		// SORT BY X-COORDINATE
		sort(x_left.begin(), x_left.end(), sortByX);
		sort(x_right.begin(), x_right.end(), sortByX);

		// recursive call
		node->setLeft(build_kd_tree(x_left, y_left, depth + 1));
		node->setRight(build_kd_tree(x_right, x_right, depth + 1));

		setHeight(depth);
		return node;
	}

	// ELSE
	// if the arrays are empty (ex: there is no right leaf for Node n), 
	// return NULL to set n->right to NULL
	return NULL;
}


/* Returns an int whose value is the height of the tree. 
For checking correctness: HEIGHT = CEIL ( lg(NUM_NODES) )
traverses tree from root to leftmost leaf, increments a counter, and returns that value
If n is even, then the "left side" array is larger than the right – thus,
the longest path from root to leaf is the leftmost one.
Height is computed on the fly; this method was originally written to make sure that those
values were correct. It is redundant to leave it in, but it serves as a sanity check.
*/
int KD_Tree::computeHeight() {

	Node* temp = root;
	int height = 1;

	while (!temp->isLeaf()) {
		height++; 
		temp = temp->getLeft();
	}
	return height;

}


/* LEVEL ORDER POINTS
	adds all nodes in KD-Tree to the pts vector using a simple
	breadth first traversal
Iterates through the "levels" of the tree – calls addLevel to traverse
tree to find appropriate nodes.
*/
void KD_Tree::levelOrderPts() {
	for (int depth = 1; depth < height + 1; depth++) {
		addLevel(getRoot(), depth);
	}
}

/* ADD LEVEL adds all nodes at depth x to the vector, from left->right
	called by levelOrderPts()
BASE CASES: node is NULL (parent only has one child node, or invalid input);
	node is at desired depth, so add to the vector and exit
RECURSIVE CALLS: traverse subtrees and print all nodes of desired depth
*/
void KD_Tree::addLevel(Node* node, int depth) {
	if (!node) {
		return;
	}
	if (node->getDepth() == depth) {
		level_ordered_pts.push_back(node);
		return;
	}
	addLevel(node->getLeft(), depth);
	addLevel(node->getRight(), depth);
}




// PRINT FUNCTIONS

void KD_Tree::printInfo() {
	printf("\nTREE INFO\n");
	printNumNodes();
	printf("Height: %d\n", getHeight() );
	printf("Root: ");
	root->printInfo(); // flushes STDOUT
}


/* PRINTS NODES IN TREE -- LEVEL ORDER TREE TRAVERSAL?
*/
void KD_Tree::printTree() {
	if(!getRoot()) {
		printf("Root is NULL; tree is empty.\n");
	}
	printf("\nPRINTING TREE:\n");
	for (int i = 0; i < level_ordered_pts.size(); i++) {
		level_ordered_pts[i]->printInfo(); printf("\n");
	}
	fflush(stdout);
}

void KD_Tree::printNumNodes() {
	printf("Number of nodes: %d\n", getNumNodes());
}



/* Helper function for the destructor
Recurses through entire tree and call Node destructor to deallocate 
(delete) every node in the tree. 
*/
void KD_Tree::deallocate_tree(Node* node) {

	if (node->isLeaf()) {
		return;
	}
	
	deallocate_tree(node->getLeft());
	deallocate_tree(node->getRight());
	node->~Node();

}



/* DESTRUCTOR
delete nodes from leaves to the root's left/right children,
then delete root
*/
KD_Tree::~KD_Tree() {
	deallocate_tree(getRoot());
	delete(getRoot());
}