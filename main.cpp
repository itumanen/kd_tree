#include "KD_Tree.h"

using namespace std;

/* GLOBAL VECTORS -- FOR GRAPHICS CODE */
vector<point2D> points; 
int num_points;
const int WINDOWSIZE = 500; 

/* FORWARD DECLARATIONS OF FUNCTIONS */
void print_points();
void initialize_points_random();


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
