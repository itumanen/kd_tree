#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Node.h"

class KD_Tree {

	// CONSTRUCTORS AND DESTRUCTOR
	KD_Tree();
	KD_Tree(point2D* pts, int numPoints);
	~KD_Tree();

	// INITIALIZATION AND HELPER FUNCTIONS
	void construct_tree();

	// GETTERS AND SETTERS
	int getHeight() { return this->height; }
	int getNumNodes() { return this->num_nodes; }
	Node* getRoot() { return this->root; }

	void setRoot(Node* r) { this->root = r; }
	void setHeight(int h) { this->height = h; }
	void updateNumNodes(int num) { this->num_nodes = num; }

	// PRINT FUNCTIONS
	void printNumNodes();


private:
	Node* root;
	int height;
	int num_nodes;

};