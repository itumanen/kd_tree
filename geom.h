#ifndef __geom_h
#define __geom_h

// todo look up how to implement this as char?
enum cutType {
	HORIZONTAL = 100,
	VERTICAL,
	LEAF
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


#endif