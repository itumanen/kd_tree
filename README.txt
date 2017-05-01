Author: Bella Tumaneng

Assignment 4: KD Tree
Implementation of a 2-dimensional KD-Tree in C++
Computational Geometry, Spring 2017
Laura Toma, Bowdoin College



USAGE: ./kdtree <nb_of_points>

KEYPRESS:
q: quit
i: iterate through test cases and render them in window


CLASSES
- Node - stores metatdata for each node in the tree (ex: node is root or leaf, corresponding cut type) and pointers to left and right children, if any.
- KD_Tree
	* stores root of the tree, vector of points initialized in main()
	* tree is built recursively 
	* maintains a vector of Node* in level order - for printing the tree
	* colorize() traverses the tree recursively; for every node in the tree that has at least one child, exactly one segment is created and stored for rendering. If the node is a leaf or one of its children is NULL (eg, no right node), a rectangle is stored and the recursion returns.


DATA STRUCTURES / GLOBAL VARS
- point2D: stores doubles x and y
- segment2D: stores start and end points, point2D objects
- rectangle2D: stores coordinates of upper left and lower right vertices, all doubles. 
- vector<point2D> points: initialized with test cases. Each tree stores this vector so that the tree can be rendered again.
- KD_Tree* tree: Pointer to a KD Tree object - the 'current' tree that has been rendered
- vector<KD_Tree*> trees: Each test case is a different object; the pointer to this object is stored in a global vector. Iterating through the test cases updates the current tree pointer to something in this vector. In the case of random point initialization, where the points are different at every iteration, the 'random' tree is deallocated and then recomputed according to the new vector of points.
- vector<segment2D> cuts: set when tree->colorize() is called. Stores all the segments that divide the plane.
- vector<rect2D> leaves: set when tree->colorize() is called. Stores each region of the tree that has to be colorized.


VARIABLES/DEFINES
- cutType - horizontal, vertical, leaf, initial (set to vertical, but can be swapped)
- DEBUG, boolean defined in geom.h that only executes certain statements (e.g. prints) for debugging