#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Node.h"

class KD_Tree {

	// CONSTRUCTORS AND DESTRUCTOR
	// KD_Tree(); // TODO necessary?
	KD_Tree(point2D* pts, int numPoints);
	~KD_Tree();

	// HELPER FUNCTIONS
	Node* build_kd_tree(point2D* points_by_x, point2D* points_by_y, int num, int depth);
	void initializeHeight() { this->height = 1; }
	int computeHeight();
	void deallocate_tree(Node* node);

	// SORTING METHODS
	point2D* sortByX(point2D pts);
	point2D* sortByY(point2D pts);
	// comparison functions
	int orderByX(point2D a, point2D b);
	int orderByY(point2D a, point2D b);

	// PRINT FUNCTIONS
	void printInfo();
	void printNumNodes();

	// INLINE GETTERS AND SETTERS
	int getHeight() { return this->height; }
	int getNumNodes() { return this->num_nodes; }
	Node* getRoot() { return this->root; }

	void setRoot(Node* r) { this->root = r; }
	void setHeight(int h) { this->height = h; }
	void incrementHeight() { this->height++; }
	void setNumNodes(int num) { this->num_nodes = num; }
	void incrementNumNodes() { this->num_nodes++; }


private:
	Node* root;
	int height;
	int num_nodes;
	point2D* sorted_by_x;
	point2D* sorted_by_y;

};