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
	* Error messages for assert?  -- less important
	* MAIN FILE!!! look at previous projects
	* PRINT TREE METHOD
	* resize/shrink to fit or declare size of vector for space optimization
- Known Bugs (and "bugs"):
	* setting height during recursive calls originally yielded incorrect results – this isn't a real bug anymore, but
	  the extra computeHeight() is still called at the end of constructor as a sanity check even though it's redundant


PART II: VISUALIZE TREE LIKE A MONDRIAN PAINTING
- 


DATA STRUCTURES

VARIABLES/DEFINES
- DEBUG, boolean defined in geom.h that only executes certain statements (e.g. prints) for debugging