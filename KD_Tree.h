#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "Node.h"

class KD_Tree {

public:

	// CONSTRUCTORS AND DESTRUCTOR
	KD_Tree();
	KD_Tree(vector<point2D> points);
	~KD_Tree();

	// HELPER FUNCTIONS
	Node* build_kd_tree(vector<point2D> points_by_x, vector<point2D> points_by_y, int depth);
	int computeHeight();
	void deallocate_tree(Node* node);
	
	// INLINE HELPER FUNCTIONS
	bool ptsIsEven() { return (num_nodes % 2 == 0); }

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
	void setNumNodes(int num) { this->num_nodes = num; }
	void setPts(vector<point2D> points) { this->pts = points; }

private:
	Node* root;
	int height;
	int num_nodes;
	vector<point2D> pts;

	// STRUCTS FOR SORTING POINT VECTORS BY COORDINATE
	struct _sortByX {
		bool operator() (const point2D &p1, const point2D &p2) { 
			if (fabs(p1.x - p2.x) < EPSILON) {
				return (p1.y < p2.y);
			}
			return (p1.x < p2.x); 
		}
	} sortByX;

	struct _sortByY {
		bool operator() (const point2D &p1, const point2D &p2) { 
			if (fabs(p1.y - p2.y) < EPSILON) {
				return (p1.x < p2.x);
			}
			return (p1.y < p2.y); 
		}
	} sortByY;

};