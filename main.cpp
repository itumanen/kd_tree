#include "KD_Tree.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>




#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;




/* GLOBAL VARIABLES -- FOR GRAPHICS CODE */
const int WINDOWSIZE = 500; 
int init_case = 0; 
const int NB_TEST_CASES = 1; 

int num_points;
vector<point2D> points; 
vector<Node*> points_by_level;





/* PREDEFINED COLORS */
GLfloat red[3] = {1.0, 0.0, 0.0};
GLfloat green[3] = {0.0, 1.0, 0.0};
GLfloat blue[3] = {0.0, 0.0, 1.0};
GLfloat black[3] = {0.0, 0.0, 0.0};
GLfloat white[3] = {1.0, 1.0, 1.0};
GLfloat gray[3] = {0.5, 0.5, 0.5};
GLfloat yellow[3] = {1.0, 1.0, 0.0};
GLfloat magenta[3] = {1.0, 0.0, 1.0};
GLfloat cyan[3] = {0.0, 1.0, 1.0};





/* FORWARD DECLARATIONS OF FUNCTIONS */
void print_points();
void initialize_points_random();
void initialize_points();




int main(int argc, char** argv) {

	// READ NUM OF POINTS FROM COMMAND LINE
	if (argc!= 2) {
	  printf("usage: main <number_of_points>\n"); fflush(stdout);
	  return(EXIT_FAILURE); 
	}

	num_points = atoi(argv[1]); 
	printf("Input: %d points.\n", num_points);

	// if num points is zero, create empty tree with default constructor
	if (num_points == 0) {
		KD_Tree* tree = new KD_Tree();
		tree->printTree();
		printf("Exiting.\n");
		return (EXIT_SUCCESS); // todo see if something else should be done
	}
	
	// INITIALIZE POINTS AT RANDOM
	initialize_points_random();

	if (DEBUG) {
		print_points();
	}

	// BUILD KD TREE
	KD_Tree* tree = new KD_Tree(points);
	tree->printInfo();

	points_by_level = tree->getPoints();


	if (DEBUG) tree->printTree();

	return (EXIT_SUCCESS);

}




void print_points() {
	printf("POINTS VECTOR\n");
	for (int i = 0; i < points.size(); i++) {
		printPoint(points[i]);
	}
}




void initialize_points_random() {
  
 	//clear the vector just to be safe 
 	points.clear(); 

 	int i; 
 	point2D p; 

 	for (i = 0; i < num_points; i++) {
 		p.x = (double)(.3*WINDOWSIZE)/2 + (double)random() / RAND_MAX * (((double)(.7*WINDOWSIZE)) - (double)(.3*WINDOWSIZE)/2);
 		p.y =  (double)(.3*WINDOWSIZE)/2 + (double)random() / RAND_MAX * (((double)(.7*WINDOWSIZE)) - (double)(.3*WINDOWSIZE)/2);
 		points.push_back(p);
	}

}




void initialize_points() {

  switch (init_case)  {
      
    case 0: 
      initialize_points_random(); 
      break;
      
    // case 1: 
    //   initialize_segments_horizontal(); 
    //   break; 
      
    default: 
      initialize_points_random(); 
    }

  init_case = (init_case+1) % NB_TEST_CASES;
  return; 
}
