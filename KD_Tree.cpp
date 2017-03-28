#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "KD_Tree.h"

// DEFAULT CONSTRUCTOR
KD_Tree::KD_Tree() {
	setRoot(NULL); 
	setHeight(0); 
	setNumNodes(0); 
	setPts(NULL);
}

// CONSTRUCTOR 
KD_Tree::KD_Tree(point2D* points, int numPoints) {

	// check that input is valid and numPoints is strictly positive
	assert(points);
	assert(numPoints > 0);

	setPts(points); // save points array in tree
	setNumNodes(numPoints); 
	initializeHeight();

	if (numPoints == 1) {

		Node* root = new Node(pts[0]);
		root->setNumPoints(numPoints);
		root->setDepth(getHeight());
		setRoot(root); // note: Node type set to LEAF by default

	} else if (numPoints == 2) {  // Case: no right side

		Node* root = new Node(pts[1]);
		root->setNumPoints(numPoints);
		root->setDepth(getHeight());
		root->setType(INITIAL_CUT);
		setRoot(root);

		Node* left = new Node(pts[0]); // type set to LEAF by default
		left->setNumPoints(numPoints - 1);
		left->setDepth(getHeight() + 1);
		root->setLeft(left);

		incrementHeight();


	} else {

		// Initialize root node
		int median = numPoints / 2; // integer division rounds DOWN
		// if the number of points is even, the right array is one 
		// index smaller than the left
		// Example:
		// 0 1 2 3 4, median index 2 --> left [0,1] right [3,4]
		// 0 1 2 3, median 2 --> left [0,1] right [3]
		int even = 1; // for proper memory allocation and recursive params
		if (ptsIsEven()) {
			even = 0;
		}

		Node* root = new Node(points[median]); 
		root->setType(INITIAL_CUT);
		root->setNumPoints(numPoints);
		root->setDepth(getHeight());
		setRoot(root);

		// allocate memory for sorted arrays
		point2D* x_left = (point2D*)malloc(median * sizeof(point2D));
		point2D* x_right = (point2D*)malloc((median - even) * sizeof(point2D));
		point2D* y_left = (point2D*)malloc(median * sizeof(point2D));
		point2D* y_right = (point2D*)malloc((median - even) * sizeof(point2D));

		// initialize by copying data from pts
		// for loops done separately because left/right arrays could
		// be of different sizes
		for (int i = 0; i < median; i++) {
			x_left[i] = pts[i];
			y_left[i] = pts[i];
		} 

		for (int i = median + 1; i < numPoints; i++) {
			x_right[i] = pts[i];
			y_right[i] = pts[i];
		}

		// TODO qsort x_left and x_right by x-coords
		// TODO qsort y_left and y_right by y-coords

		// BUILD TREE RECURSIVELY
		root->setLeft(build_kd_tree(x_left, y_left, median, getHeight() ));
		root->setRight(build_kd_tree(x_right, y_right, median, getHeight() ));

		free(x_left);
		free(x_right);
		free(y_left);
		free(y_right);

		setHeight(computeHeight());

	}

}

// INITIALIZATION AND HELPER FUNCTIONS - TODO 
Node* KD_Tree::build_kd_tree(point2D* points_by_x, point2D* points_by_y, int num, int depth) {

	assert(num > 0); // TODO IF THIS FAILS DEBUG!! --> print statement
	int median = num / 2;
	setHeight(depth);

	// if only one point, return leaf containing point
	if (depth % 2 == 0 && num > 1) {

		// add node to the tree
		Node* node = new Node(points_by_x[median]);
		node->setType(VERTICAL);
		node->setNumPoints(median);
		node->setDepth(depth);

		// TODO ALLOCATE ARRAYS
		// COPY DATA
		// SORT

		// TODO SORT y arrays BY Y COORDINATE

		// recursive call
		node->setLeft(build_kd_tree(x_left, y_left, median, depth + 1));
		node->setRight(build_kd_tree(x_right, x_right, median, depth + 1));

		// free arrays before returning
		free(x_left);
		free(x_right);
		free(y_left);
		free(y_right);

		return node;

	} else if (depth % 2 != 0 && num > 1) {

		// add node to the tree
		Node* node = new Node(points_by_y[median]);
		node->setType(HORIZONTAL);
		node->setNumPoints(median);
		node->setDepth(depth);

		// TODO ALLOCATE ARRAYS
		// COPY DATA
		// SORT

		// TODO SORT BY X-COORDINATE

		// recursive call
		node->setLeft(build_kd_tree(x_left, y_left, median, depth + 1));
		node->setRight(build_kd_tree(x_right, x_right, median, depth + 1));

		// free arrays before returning
		free(x_left);
		free(x_right);
		free(y_left);
		free(y_right);

		return node;
	}

	// BASE CASE: IF NUMBER OF POINTS IS 1, RETURN A LEAF
	if (DEBUG) {
		printf("num should be 1 and is %d\n", num);
	}

	assert(equals(points_by_x[0], points_by_y[0])); // TODO IF THIS FAILS DEBUG!! --> print statement
	Node* node = new Node(points_by_x[0]); // default type is LEAF
	node->setNumPoints(num);
	node->setDepth(depth);
	return node;

}

// traverses tree from root to leftmost leaf and returns height of tree
// if n is even, then the "left side" array is larger than the right – thus,
// the longest path from root to leaf is the leftmost one
int KD_Tree::computeHeight() {

	Node* temp = root;
	int height = 0;
	while (temp->isLeaf()) {
		height++; 
		temp = temp->getLeft();
	}
	return height;

}

// comparison functions for system qsort - todo pointers
int KD_Tree::orderByX(point2D a, point2D b) {
	if (fabs(a.x - b.x) < EPSILON) {
		return (orderByY(a, b)); // if a and b have the same x-coord, order by y
	}
	if (a.x < b.x) {
		return -1;
	}
	// (a.x > b.x) 	
	return 1;
	
}

// todo pointers
int KD_Tree::orderByY(point2D a, point2D b) {
	if (fabs(a.y - b.y) < EPSILON) {  // a and b have same y-coordinate
		if( fabs(a.x - b.x) < EPSILON) { // a and b also have same x-coordinate (not likely)
			return 0;
		}
		return (orderByX(a, b)); // same y-coord but different x-coord, sort by x
	}
	if (a.y < b.y) {
		return -1; 
	}
	// a.y > b.y)
		return 1;
}

// PRINT FUNCTIONS

void KD_Tree::printInfo() {
	printNumNodes();
	printf("Height: %d\n", getHeight() );
	printf("Root: \n");
	root->printInfo(); // flushes STDOUT
}

void KD_Tree::printNumNodes() {
	printf("Number of nodes %d\n", getNumNodes());
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

	// deallocate array TODO DOUBLE CHECK -- DONE IN MAIN?
	// free(pts);

}