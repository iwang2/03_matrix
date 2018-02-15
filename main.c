#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

int main() {

  screen s;
  color c;
  struct matrix *edges;

  edges = new_matrix(4, 4);

  /*
  draw_lines(edges, s, c);
  display(s);
  */

  ident(edges);
  print_matrix(edges);
  
  matrix_mult(edges, edges);
  print_matrix(edges);

  for(int c = 0; c < edges->cols; c++){
    for(int r = 0; r < edges->rows; r++){
      edges->m[r][c] = r+c;
    }
  }

  matrix_mult(edges, edges);
  print_matrix(edges);
  
  free_matrix( edges );
}
