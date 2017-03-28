#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Node.h"

class KD_Tree {

	// CONSTRUCTORS AND DESTRUCTOR
	KD_Tree();
	KD_Tree(point2D* points, int numPoints);
	~KD_Tree();

	// HELPER FUNCTIONS
	Node* build_kd_tree(point2D* points_by_x, point2D* points_by_y, int num, int depth);
	int computeHeight();
	void deallocate_tree(Node* node);
	
	// INLINE HELPER FUNCTIONS
	bool ptsIsEven() { return (num_nodes % 2 == 0); }

	// SORTING METHODS
	int orderByX(point2D a, point2D b);
	int orderByY(point2D a, point2D b);

	// PRINT FUNCTIONS
	void printInfo();
	void printTree();
	void printNumNodes();


	// GETTERS AND SETTERS
	int getHeight() { return this->height; }
	int getNumNodes() { return this->num_nodes; }
	Node* getRoot() { return this->root; }

	void setRoot(Node* r) { this->root = r; }
	void setHeight(int h) { this->height = h; }
	void initializeHeight() { this->height = 1; }
	void incrementHeight() { this->height++; }
	void setNumNodes(int num) { this->num_nodes = num; }
	void setPts(point2D* points) { this->pts = points; }

private:
	Node* root;
	int height;
	int num_nodes;
	point2D* pts;

};