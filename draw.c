#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

/*======== void add_point() ==========
Inputs:   struct matrix * points
         int x
         int y
         int z 
Returns: 
adds point (x, y, z) to points and increment points.lastcol
if points is full, should call grow on points
====================*/
void add_point( struct matrix * points, double x, double y, double z) {
  int cols = points->lastcol;
  if (cols == points->cols) grow_matrix(points, cols+3);
  
  points->m[0][cols] = x;
  points->m[1][cols] = y;
  points->m[2][cols] = z;

  points->m[3][cols] = 1;

  points->lastcol++;
}

/*======== void add_edge() ==========
Inputs:   struct matrix * points
          int x0, int y0, int z0, int x1, int y1, int z1
Returns: 
add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
should use add_point
====================*/
void add_edge( struct matrix * points, 
	       double x0, double y0, double z0, 
	       double x1, double y1, double z1) {
  add_point(points, x0, y0, z0);
  add_point(points, x1, y1, z1);
}

/*======== void draw_lines() ==========
Inputs:   struct matrix * points
         screen s
         color c 
Returns: 
Go through points 2 at a time and call draw_line to add that line
to the screen
====================*/
void draw_lines( struct matrix * points, screen s, color c) {
  int col;
  for(col = 0; col < points->lastcol; col += 2){
    draw_line(points->m[0][col], points->m[1][col],
	      points->m[0][col+1], points->m[1][col+1],
	      s, c);
  }
}

void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {
  if(x0 > x1){
    int xt = x0;
    int yt = y0;
    x0 = x1;
    y0 = y1;
    x1 = xt;
    y1 = yt;
  }
  int
    x = x0,
    y = y0;
  int
    a = y1 - y0,
    b = x0 - x1;
  int d;

  double m;
  if ( b == 0 ) m = 2;
  else m = a * 1.0 / -b;

  if ( b == 0 ) {
    if ( y > y1 ) {
      int temp = y;
      y = y1;
      y1 = temp;
    }
    while ( y <= y1 ) {
      plot(s, c, x, y);
      y++;
    }
  }
    
  // VII
  else if ( m < -1 ) {
    d = a - 2*b;
    while ( x <= x1 ) {
      plot(s, c, x, y);
      if ( d > 0 ) {
	x++;
	d += 2*a;
      }
      y--;
      d -= 2*b;
    }
  }

  // VIII
  else if ( m < 0 ) {
    d = 2*a - b;
    while ( x <= x1 ) {
      plot(s, c, x, y);
      if ( d < 0 ) {
	y--;
	d -= 2*b;
      }
      x++;
      d += 2*a;
    }
  }

  // I
  else if ( m < 1 ) {
    d = 2*a + b;
    while ( x <= x1 ) {
      plot(s, c, x, y);
      if ( d > 0 ) {
	y++;
	d += 2*b;
      }
      x++;
      d += 2*a;
    }
  }  

  // II
  else {
    d = a + 2*b;
    while ( x <= x1 ) {
      plot(s, c, x, y);
      if ( d < 0 ) {
	x++;
	d += 2*a;
      }
      y++;
      d += 2*b;
    }
  }

}
