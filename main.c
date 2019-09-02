#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#include "paint.h"

int main(int argc, char**argv) {
  canvas_size myCanvas;

  //ask_user_for_input
  get_start_input(&myCanvas, argc, argv);
  //display_the_broad
  char** canvas = make_size_broad(myCanvas.rows, myCanvas.cols);
  print_broad(myCanvas.rows, myCanvas.cols, canvas);
  //ask_user_for_command
  get_input(myCanvas, canvas);
  //change_the_broad_as_commanded
//  print_broad();
  //keep_asking_and_changing_until_quit
  free_arr(myCanvas.rows, &canvas);

}

