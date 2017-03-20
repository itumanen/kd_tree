#include "geom.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>

using namespace std;

class Node {

	Node();
	Node(point2D* points);
	~Node();

	// helper functions
	void printNumPoints();

	// getters and setters
	int getNumPoints() { return this->num_points; }
	Node* getLeft() { return this->left; }
	Node* getRight() { return this->right; }

private:
	point2D* pts;
	char type;
	Node* left;
	Node* right;

	int num_points;

};
