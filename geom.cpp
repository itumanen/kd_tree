#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "geom.h"

void printPoint(point2D p) {
	printf("point (%lf, %lf)\n", p.x, p.y);
	fflush(stdout);
}

void printSegment(segment2D s) {
	printf("start (%lf, %lf)  end (%lf, %lf)\n", s.start.x, s.start.y, s.end.x, s.end.y);
	fflush(stdout);
}

bool equals(point2D a, point2D b) {
	return( fabs(a.x - b.x) < EPSILON && fabs(a.y - b.y) < EPSILON );
}