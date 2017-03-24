#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "KD_Tree.h"

// CONSTRUCTOR 
KD_Tree::KD_Tree(point2D* pts, int numPoints) {

	assert(pts);
	assert(numPoints > 0);

	setNumNodes(numPoints); // TODO verify
	initializeHeight();

	if (numPoints == 1) {

		Node* root = new Node(pts);
		root->setNumPoints(numPoints);
		root->setDepth(getHeight());
		setRoot(root); // note: Node type set to LEAF by default

	} else {

		// Initialize root node
		int median = numPoints / 2; // TODO VERIFY, should round up tho
		Node* root = new Node(&sorted_by_x[median]); 
		root->setType(INITIAL_CUT);
		root->setNumPoints(numPoints);
		root->setDepth(getHeight());
		setRoot(root);

		// allocate memory for sorted arrays and initialize by copying data from pts
		// TODO need to allocate for size of structs? probs not... 
		sorted_by_x = (point2D*)malloc(numPoints * sizeof(point2D*));
		sorted_by_y = (point2D*)malloc(numPoints * sizeof(point2D*)); // TODO might not need this

		assert(sorted_by_x);
		assert(sorted_by_y); // TODO might not need this

		for(int i = 0; i < numPoints; i++) {
			sorted_by_x[i] = pts[i];
			sorted_by_y[i] = pts[i];
		}

		// TODO QSORT - includes and implementation

		// build tree recursively
		// left and right arrays
		point2D* x_left = (point2D*)malloc(median * sizeof(point2D*));
		point2D* x_right = (point2D*)malloc(median * sizeof(point2D*));
		point2D* y_left = (point2D*)malloc(median * sizeof(point2D*));
		point2D* y_right = (point2D*)malloc(median * sizeof(point2D*));

		for (int i = 0; i < median; i++) {
			x_left[i] = sorted_by_x[i];
			x_right[i] = sorted_by_x[median + i];
		} // 0 1 2 3 4, median 3
		  // 0 1 2 3, median 2

		// TODO qsort x_left and x_right by y-coordinate and initialize y_ARRAYS

		root->setLeft(build_kd_tree(x_left, y_left, median, getHeight() ));
		root->setRight(build_kd_tree(x_right, y_right, median, getHeight() ));

		free(x_left);
		free(x_right);
		free(y_left);
		free(y_right);

		computeHeight();

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
		Node* node = new Node(&points_by_x[median]);
		node->setType(VERTICAL);
		node->setNumPoints(median);
		node->setDepth(depth);

		// split arrays and allocate memory
		point2D* x_left = (point2D*)malloc(median * sizeof(point2D*));
		point2D* x_right = (point2D*)malloc(median * sizeof(point2D*));
		point2D* y_left = (point2D*)malloc(median * sizeof(point2D*));
		point2D* y_right = (point2D*)malloc(median * sizeof(point2D*));

		// copy data from sorted x array
		for (int i = 0; i < median; i++) {
			x_left[i] = points_by_x[i];
			x_right[i] = points_by_x[median + i];
			y_left[i] = points_by_x[i];
			y_right[i] = points_by_x[median + i];
		}

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
		Node* node = new Node(&points_by_y[median]);
		node->setType(HORIZONTAL);
		node->setNumPoints(median);
		node->setDepth(depth);

		// split arrays and allocate memory
		point2D* x_left = (point2D*)malloc(median * sizeof(point2D*));
		point2D* x_right = (point2D*)malloc(median * sizeof(point2D*));
		point2D* y_left = (point2D*)malloc(median * sizeof(point2D*));
		point2D* y_right = (point2D*)malloc(median * sizeof(point2D*));

		// copy data from sorted x array
		for (int i = 0; i < median; i++) {
			y_left[i] = points_by_y[i];
			y_right[i] = points_by_y[median + i];
			x_left[i] = points_by_y[i];
			x_right[i] = points_by_y[median + i];
		}

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

	// if num is 1, return a leaf
	if (DEBUG) {
		printf("num should be 1 and is %d\n", num);
	}

	assert(equals(points_by_x[0], points_by_y[0])); // TODO IF THIS FAILS DEBUG!! --> print statement
	Node* node = new Node(points_by_x); // default type is LEAF
	node->setNumPoints(num);
	node->setDepth(depth);
	return node;

}

// traverses tree from root to leftmost leaf and returns height of tree
int KD_Tree::computeHeight() {

	Node* temp = root;
	int height = 0;
	while (temp->isLeaf()) {
		height++; 
		temp = temp->getLeft();
	}
	return height;

}

// SORTING METHODS - TODO move all qsort things here
point2D* KD_Tree::sortByX(point2D* pts) {
	return sorted_by_x;
}

point2D* KD_Tree::sortByY(point2D* pts) {
	return sorted_by_y;
}

// comparison functions
int KD_Tree::orderByX(point2D a, point2D b) {
	if (fabs(a.x - b.x) < EPSILON) {
		return (orderByY(a, b));
	}
	return ( (a.x < b.x) ); // TODO TEST ORDERING
}

int KD_Tree::orderByY(point2D a, point2D b) {
	if (fabs(a.y - b.y) < EPSILON) {
		if( fabs(a.x - b.x) < EPSILON) {
			return 0; // TODO TEST THIS
		}
		return ( orderByX(a, b) );
	}
	return (a.y < b.y); // TODO TEST ORDERING
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

	// deallocate arrays
	free(sorted_by_x);
	free(sorted_by_y);
}