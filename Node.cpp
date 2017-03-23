#include "Node.h"

// default constructor TODO not necessary?
// Node::Node() {

// }

Node::Node(point2D* point) {
	setPoint(point);
	setType(LEAF); // default; this gets set when kd-tree is built
}

Node::~Node() {
	delete(left);
	delete(right);
}