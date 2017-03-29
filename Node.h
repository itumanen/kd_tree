#include "geom.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>

#include <string>

using namespace std;

class Node {

public:

	// CONSTRUCTORS AND DESTRUCTOR
	Node();
	Node(point2D point);
	~Node();

	// helper functions
	bool isLeaf() { return (type == LEAF); }
	bool isRoot() { return root; }

	// print functions
	void printInfo();
	void printType();

	// inline getters and setters
	point2D getPoint() { return this->pt; }
	Node* getLeft() { return this->left; }
	Node* getRight() { return this->right; }
	int getType() { return this->type; }
	int getDepth() { return this->depth; }

	void setType(int t) { this->type = t; }
	void setRoot(bool r) { this->root = r; }
	void setDepth(int d) { this->depth = d; }
	void setPoint(point2D point) { this->pt = point; }
	void setLeft(Node* l) { this->left = l; }
	void setRight(Node* r) { this->right = r; }

private:
	int type;
	bool root;
	int depth;
	point2D pt; // if node is a leaf, pt is contained in the region; else point is the median
	Node* left;
	Node* right;

};
