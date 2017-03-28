#include "Node.h"

// default constructor
Node::Node() {
	// set to empty point
	point2D null_point; 
	null_point.x = 0.0;
	null_point.y = 0.0;
	setPoint(null_point); 
	setType(LEAF); 
	setNumPoints(0); 
	setDepth(0); 
	setLeft(NULL);
	setRight(NULL);
}

Node::Node(point2D point) {
	setPoint(point);
	setNumPoints(0); // todo this is default for now

	// default; these get set when kd-tree is built
	setType(LEAF); 
	setDepth(1);
	setLeft(NULL);
	setRight(NULL);
}

// PRINT FUNCTIONS
void Node::printInfo() {
	printPoint(getPoint());
	printType();
	printNumPoints();
	fflush(stdout);
}

void Node::printType() {
	string type;
	if (getType() == VERTICAL) {
		type = "VERTICAL";
	} else if (getType() == HORIZONTAL) {
		type = "HORIZONTAL";
	} else if (getType() == LEAF) {
		type = "LEAF";
	}
	printf("Type: %s\n", type.c_str());
}

// TODO not necessary?
void Node::printNumPoints() {
	printf("Number of points in region: %d\n", getNumPoints() );
} 

Node::~Node() {
	delete(left);
	delete(right);
}