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
	* handle odd-numbered inputs (number of points)
- Known Bugs:
	* setting height during recursive calls could yield incorrect results - thus this isn't done on the fly, but before exiting the constructor
	* if number of points is odd, the right-side array needs to be allocated one space more


PART II: VISUALIZE TREE LIKE A MONDRIAN PAINTING
- 