#include "Node.h"

// default constructor TODO not necessary?
// Node::Node() {

// }

Node::Node(point2D* point) {
	setPoint(point);

	// default; these get set when kd-tree is built
	setType(LEAF); 
	setDepth(1);
	setLeft(NULL);
	setRight(NULL);
}

// PRINT FUNCTIONS
void Node::printInfo() {
	printPoint(*getPoint());
	printType();
	printNumPoints();
	fflush(stdout);
}

void Node::printType() {
	printf("Type: %d\n", getType() );
}

// TODO not necessary?
void Node::printNumPoints() {
	printf("Number of points in region: %d\n", getNumPoints() );
} 

Node::~Node() {
	delete(left);
	delete(right);
}