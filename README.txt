Author: Bella Tumaneng

Assignment 4: KD Tree
Implementation of a 2-dimensional KD-Tree in C++
Computational Geometry, Spring 2017
Laura Toma, Bowdoin College

USAGE: ./kdtree <nb_of_points>

PART I: BUILD KD TREE
- TODO: 
	* add rtimer code to makefile + use to compute the run time of KD tree construction
	* if number of points is odd, right is one spot too big
	* look up what qsort does under the hood -- operate only on pointers to point2D?
	* check that copying elements into newly allocated arrays copies ADDRESSES TO POINTS - should?
- Known Bugs:
	* setting height during recursive calls could yield incorrect results - thus this isn't done on the fly, but before exiting the constructor


PART II: VISUALIZE TREE LIKE A MONDRIAN PAINTING
- 