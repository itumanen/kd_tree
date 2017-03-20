#ifndef __geom_h
#define __geom_h


typedef struct _point2d {
  double x,y; 
} point2D;


typedef struct _segment2d {
  point2D start; 
  point2D end; 
} segment2D;

void printPoint(point2D p);
void printSegment(segment2D s);


#endif