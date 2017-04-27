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




/* GLOBAL VARIABLES */
const int WINDOWSIZE = 500; 
int init_case = 0; 
const int NB_TEST_CASES = 5; 

int n;
vector<point2D> points; 
vector<Node*> points_by_level;

KD_Tree* tree;
vector<KD_Tree*> trees;
vector<rect2D> leaves;
vector<segment2D> cuts;

bool DEBUG_MAIN = true;
bool DEBUG_GRAPHICS = false;


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

float transparency = 0.8;



/* FORWARD DECLARATIONS OF FUNCTIONS */
void print_points();

// Test cases
void initialize_points();

void initialize_points_random();
void initialize_points_grid();
void initialize_points_diag();
void initiallize_points_circle();
void initializePointsX();

// GLUT
void display();
void keypress(unsigned char key, int x, int y);
void reshape();
void timerfunc();







/* ****************************** */
/* 			MAIN FUNCTION 		  */
/* ****************************** */
int main(int argc, char** argv) {

	// READ NUM OF POINTS FROM COMMAND LINE
	if (argc!= 2) {
	  printf("usage: main <number_of_points>\n"); fflush(stdout);
	  return(EXIT_FAILURE); 
	}

	n = atoi(argv[1]); 
	printf("Input: %d points.\n", n);

	// if num points is zero, create empty tree with default constructor
	if (n == 0) {
		tree = new KD_Tree();
		tree->printTree();
		printf("Exiting.\n");
		return (EXIT_SUCCESS); // todo see if something else should be done
	}
	
	// DEFAULT: INITIALIZE POINTS AT RANDOM
	initialize_points_random();

	if (DEBUG) {
		print_points();
	}

	// BUILD KD TREE
	tree = new KD_Tree(points);
	tree->printInfo();
	points_by_level = tree->getPoints();

	// initialize graphics vectors
	tree->colorize(0, WINDOWSIZE, 0, WINDOWSIZE, tree->getRoot());
	cuts = tree->cuts;
	leaves = tree->leaves;
	trees.push_back(tree);


	if (DEBUG) {
		tree->printTree();
	}

	if (DEBUG_GRAPHICS) {
		tree->printTree();
		printf("number of cuts: %lu\n", cuts.size());
		printf("number of rectangles: %lu\n", leaves.size());
	}

	/* initialize GLUT  */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WINDOWSIZE, WINDOWSIZE);
	glutInitWindowPosition(100,100);
	glutCreateWindow(argv[0]);

	/* register callback functions */
	glutDisplayFunc(display); 
	glutKeyboardFunc(keypress);
	glutIdleFunc(timerfunc);  //<--------note we got an idle function, we'll use it to animate 

	/* init GL */
	/* set background color gray */
	glClearColor(0.2, 0.2, 0.2, 0);   
	// glClearColor(0, 0, 0, 0);   

	
	/* give control to event handler */
	glutMainLoop();
	return 0;


	return (EXIT_SUCCESS);

}



/* ****************************** */
/* 		 HELPER FUNCTIONS 	  	  */
/* ****************************** */



// PRINT FUNCTIONS
void print_points() {
	printf("POINTS VECTOR\n");
	for (int i = 0; i < points.size(); i++) {
		printPoint(points[i]);
	}
}

void printSegments() {
	if (cuts.empty()) return;
	for (int i = 0; i < cuts.size(); i++) {
		printSegment(cuts[i]);
	}
}



/* ****************************** */
/* 		 	TEST CASES 	  	  	  */
/* ****************************** */



void initialize_points_random() {
  
 	//clear the vector just to be safe 
 	points.clear(); 
 	point2D p; 

 	for (int i = 0; i < n; i++) {
 		p.x = (double)(.3*WINDOWSIZE)/2 + (double)random() / RAND_MAX * (((double)(.7*WINDOWSIZE)) - (double)(.3*WINDOWSIZE)/2);
 		p.y =  (double)(.3*WINDOWSIZE)/2 + (double)random() / RAND_MAX * (((double)(.7*WINDOWSIZE)) - (double)(.3*WINDOWSIZE)/2);
 		points.push_back(p);
	}

}

// Jack Ward
// Initialize the `points` vector to a grid.
void initialize_points_grid() {
	// clear the vector
	points.clear();

	double window  = (double) WINDOWSIZE;
	double padding = window / 8;
	double width   = window - 2 * padding;
	int    side    = sqrt(n);
	double spacing = width / (double) side;

	for (int row = 0; row < side; row++) {
		for (int col = 0; col < side; col++) {
			double x = fma(col, spacing, padding); // col * spacing + padding
	    	double y = fma(row, spacing, padding); // row * spacing + padding
	    	point2D p = {x,y};
	    	points.push_back(p);
	  }
	}
}

// Bo Bleckel & Henry Daniels Koch
// Initialize the points in a downward sloping diagonal
// Works best with n <= 100
void initialize_points_diag() {
	points.clear();

	point2D point;
	for (int i = 0; i < n; i++) {
	    double x = i * (WINDOWSIZE/n);
	    double y = (n-i) * (WINDOWSIZE/n);
	    point.x = x;
	    point.y = y;

	    points.push_back(point);
	}
}

//Erik and Grace code
void initialize_points_circle() {
	points.clear();
	double radius = WINDOWSIZE / 5;
	point2D p;
	for (int i = 0; i < n; i++){
		p.x = radius * cos (2*M_PI / n * i) + WINDOWSIZE / 2;
		p.y = radius * sin (2*M_PI / n * i) + WINDOWSIZE / 2;
		points.push_back(p);
	}
}

// initializes the points in a x shape - Bella
// modified, based on test case on piazza and 
// initialize_points_diagonal()
void initializePointsX() {

	points.clear();

	point2D point1, point2;
	for(int i = 0; i < n / 2; ++i) {

		double x = i * (WINDOWSIZE / n * 2);

		point1.x = x;
		point1.y = x;

		point2.x = x;
		point2.y = WINDOWSIZE - x;

		points.push_back(point1);
		points.push_back(point2);
	}

	return;
}



// FOR LOOPING THROUGH TEST CASES
void initialize_points() {

	init_case = (init_case+1) % NB_TEST_CASES;

	  switch (init_case)  {
	      
	    case 0: 
	      initialize_points_random();
	      break;
	      
	    case 1: 
	      initialize_points_grid(); 
	      break; 

	    case 2:
	      initialize_points_diag();
	      break;

	    case 3:
	      initialize_points_circle();
	      break;

	    case 4:
	      initializePointsX();
	      break;
	      
	    default: 
	      printf("default \n");
	      initialize_points_random(); 
	    }

	  return; 
}


/* ****************************** */
/* 		  DRAW FUNCTIONS 	  	  */
/* ****************************** */

void draw_points() {

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3fv(black);
	glPointSize(5);
	glBegin(GL_POINTS);

	  for (int i = 0; i < points.size(); i++) {
	  	glVertex2f(points[i].x, points[i].y); 
	  }

  	glEnd();

}


void draw_segments() {

	if (cuts.empty()) return;
	glColor3fv(black);

	for (int i = 0; i < cuts.size(); i++) {
		glBegin(GL_LINES);
		glLineWidth(15);
		glVertex2d(cuts[i].start.x, cuts[i].start.y);
		glVertex2d(cuts[i].end.x, cuts[i].end.y);
		glEnd();
	}

}

void draw_regions() {
	if (leaves.empty()) return;

	// glColor3fv(blue);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// glColor4f(0.0, 1.0, 1.0, 0.2);

	for (int i = 0; i < leaves.size(); i++) {
		if (i % 4 == 0) {
			glColor4f(0.0, 0.0, 1.0, transparency);
		} else if (i % 3 == 0) {
			glColor4f(0.3, 0.0, 1.0, transparency);
		} else if (i % 2 == 0) {
			glColor4f(0.0, 7.0, 1.0, transparency);
		} else {
			glColor4f(1.0, 1.0, 1.0, transparency);
		}
		glRectd(leaves[i].xmin, leaves[i].ymin, 
				leaves[i].xmax, leaves[i].ymax);
	}

}



/* ****************************** */
/* 		  WINDOW FUNCTIONS 	  	  */
/* ****************************** */



/* ****************************** */
void display(void) {

	  //clear everything, start from scratch 
	  glClear(GL_COLOR_BUFFER_BIT);
	  glMatrixMode(GL_MODELVIEW); 
	  glLoadIdentity(); 


	  /* The default GL window is [-1,1]x[-1,1] with the origin in the center. 
	     
	     The points are in the range (0,0) to (WINSIZE,WINSIZE). This is our local coordinate system. 

	     We first transform our local coordinate system to [-1,1] x [-1,1]
	  */
	  glScalef(2.0/WINDOWSIZE, 2.0/WINDOWSIZE, 1.0);  
	  glTranslatef(-WINDOWSIZE/2, -WINDOWSIZE/2, 0); 


	  //draw my scene in the local coordinate system (0,0) to (WINSIZE,WINSIZE)
	  draw_regions();
	  draw_segments();
	  draw_points();

	  /* execute the drawing commands */
	  glFlush();
}


/* ****************************** */
void keypress(unsigned char key, int x, int y) {

	  switch(key) {
	  
	  case 'q':
	    exit(0);
	    break;
	  
	  case 'i': 

	    points_by_level.clear();
	    cuts.clear();
	    leaves.clear();
	    initialize_points(); 

	    // build new tree for new test case, store the pointer in global vect
	    if (init_case + 1 > trees.size()) {
	    	if (DEBUG_MAIN) {
	    		printf("number of points %lu\n", points.size());
	    	}
	    	
	    	KD_Tree* newTree = new KD_Tree(points);	
	    	newTree->printInfo();
	    	points_by_level = newTree->getPoints();
	    	trees.push_back(newTree);

	    } 	else if (init_case == 0 && trees.size() > 0) {

	    	// if there already exists a 'random' tree
	    	// need to rebuild tree with new set of random
	    	// points
	    	trees[0]->rebuildTree(points);
	    	points_by_level = trees[0]->getPoints();
	    	trees[0]->printInfo();

	    }

	    // switch tree to be rendered
	    tree = trees[init_case];
	    glutPostRedisplay();
	    break; 
	  
	  case 'c':
	  	tree->colorize(0, WINDOWSIZE, 0, WINDOWSIZE, tree->getRoot());
	  	cuts = tree->cuts;
	  	leaves = tree->leaves;

	  	if (DEBUG_GRAPHICS) {
	  		printf("number of cuts: %lu\n", cuts.size());
	  		printf("number of rectangles: %lu\n", leaves.size());
	  		tree->printTree();
	  		printSegments();
	  	}

	  	break;

	  }

}



/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
	   // Set the viewport to cover the new window
	   glViewport(0, 0, width, height);
	 
	   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	   glLoadIdentity();             // Reset
	   gluOrtho2D(0.0, (GLdouble) width, 0.0, (GLdouble) height); 
}


/* Nothing yet */
void timerfunc() {
	glutPostRedisplay(); 
}