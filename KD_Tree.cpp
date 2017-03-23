#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "KD_Tree.h"

// CONSTRUCTOR 
KD_Tree::KD_Tree(point2D* pts, int numPoints) {

	updateNumNodes(numPoints); // TODO verify
	
	// allocate memory for sorted arrays and initialize by copying data from pts
	// TODO need to allocate for size of structs? probs not... 
	sorted_by_x = (point2D*)malloc(numPoints * sizeof(point2D*));
	sorted_by_y = (point2D*)malloc(numPoints * sizeof (point2D*));

	for(int i = 0; i < numPoints; i++) {
		sorted_by_x[i] = pts[i];
		sorted_by_y[i] = pts[i];
	}

	// TODO QSORT - includes and implementation

	// build tree recursively
	// build_kd_tree(sorted_by_x, sorted_by_y, numPoints, INITIAL_CUT); // TODO DEFINE

}

// INITIALIZATION AND HELPER FUNCTIONS
Node* KD_Tree::build_kd_tree(point2D* points_by_x, point2D* points_by_y, int num, int cutType) {
	Node* node = new Node(points_by_x); // TODO
	return node;
}

void KD_Tree::add_node(Node* node) {

}

void KD_Tree::delete_node(Node* node) {

}

// SORTING METHODS
point2D* KD_Tree::sortByX(point2D pts) {
	return sorted_by_x;
}

point2D* KD_Tree::sortByY(point2D pts) {
	return sorted_by_y;
}

// comparison functions
int KD_Tree::orderByX(point2D a, point2D b) {
	return 0;
}

int KD_Tree::orderByY(point2D a, point2D b) {
	return 0;
}

// PRINT FUNCTIONS
void KD_Tree::printNumNodes() {
	printf("Number of nodes %d\n", getNumNodes());
}

// DESTRUCTOR
KD_Tree::~KD_Tree() {

	// recurse through entire tree and call destructors of all nodes

	// delete the last node
	delete(root);

	// deallocate arrays
	free(sorted_by_x);
	free(sorted_by_y);
}