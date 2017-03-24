#ifndef __geom_h
#define __geom_h

#include <math.h>

#define EPSILON 0.00000001
#define DEBUG true

// todo look up how to implement this as char?
enum cutType {
	VERTICAL = 100,
	HORIZONTAL,
	LEAF,
	INITIAL_CUT = VERTICAL
};

typedef struct _point2d {
  double x,y; 
} point2D;


// used for graphics implementation
typedef struct _segment2d {
  point2D start; 
  point2D end;
  int type; 
} segment2D;

void printPoint(point2D p);
void printSegment(segment2D s);

bool equals(point2D a, point2D b);


#endif