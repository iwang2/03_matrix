#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

int main() {

  screen s;
  color cl;
  cl.red = MAX_COLOR;
  cl.green = MAX_COLOR;
  cl.blue = MAX_COLOR;
  
  struct matrix *edges, *identity;

  edges = new_matrix(4, 4);
  identity = new_matrix(4, 4);

  printf("\ncreate identity matrix:\n");
  ident(identity);
  print_matrix(identity);

  printf("new matrix:\n");
  int r, c;
  for(r = 0; r < edges->rows; r++)
    for(c = 0; c < edges->cols; c++)
      edges->m[r][c] = r + c;
  print_matrix(edges);
  
  printf("multiply new matrix by identity matrix:\n");
  matrix_mult(identity, edges);
  print_matrix(edges);

  printf("adding points:\n");
  add_point(edges, 0, 250, 0);
  add_point(edges, 250, 0, 0);
  print_matrix(edges);

  printf("adding edges:\n");
  add_edge(edges, 0, 250, 0, 250, 500, 0);
  print_matrix(edges);

  add_edge(edges, 250, 500, 0, 500, 250, 0);
  add_edge(edges, 250, 0, 0, 500, 250, 0);

  int i, j, col;
  int inc = 15;
  for(i = 0; i < 30; i++){
    col = edges->lastcol;
    add_edge(edges,
	     edges->m[0][col-7]+inc, edges->m[1][col-7]+inc, 0,
	     edges->m[0][col-6]-inc, edges->m[1][col-6]+inc, 0);
    add_edge(edges,
	     edges->m[0][col-5]+inc, edges->m[1][col-5]+inc, 0,
	     edges->m[0][col-4]+inc, edges->m[1][col-4]-inc, 0);
    add_edge(edges,
	     edges->m[0][col-3]+inc, edges->m[1][col-3]-inc, 0,
	     edges->m[0][col-2]-inc, edges->m[1][col-2]-inc, 0);
    add_edge(edges,
	     edges->m[0][col-1]+inc, edges->m[1][col-1]+inc, 0,
	     edges->m[0][col]-inc, edges->m[1][col]-inc, 0);
  }
  
  draw_lines(edges, s, cl);
  display(s);

  free_matrix( edges );
}
