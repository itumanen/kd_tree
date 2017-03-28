Author: Bella Tumaneng

Assignment 4: KD Tree
Implementation of a 2-dimensional KD-Tree in C++
Computational Geometry, Spring 2017
Laura Toma, Bowdoin College

USAGE: ./kdtree <nb_of_points>

PART I: BUILD KD TREE
- TODO: 
	* add rtimer code to makefile + use to compute the run time of KD tree construction
	* To use less space, declare enum using chars instead of ints
	* Error messages for assert? 
	* MAIN FILE!!! look at previous projects
	* test code on small inputs + compare results by hand
	* PRINT TREE METHOD
	* double check "right subtree" check for nodes that only have one child
	* make sure all array names are correct in recursive function
- Known Bugs:
	* setting height during recursive calls could yield incorrect results - thus this isn't done on the fly, but before exiting the constructor
	* if number of points is odd, the right-side array needs to be allocated one space more


PART II: VISUALIZE TREE LIKE A MONDRIAN PAINTING
- 


DATA STRUCTURES

VARIABLES/DEFINES
- DEBUG, boolean defined in geom.h that only executes certain statements (e.g. prints) for debugging