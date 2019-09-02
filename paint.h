//
// Created by Raymond Chan on 12/7/17.
//

#ifndef PAINT_REMAKE_PAINT_H
#define PAINT_REMAKE_PAINT_H
typedef struct canvas_size_struct{
  int rows;
  int cols;
} canvas_size;

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

void get_start_input(canvas_size*myCanvas, int argc, char**argv);

char** make_size_broad(int rows, int cols);
void print_broad(int rows, int cols, char** arr);
void free_arr(int rows, char***arr);
bool isVaildFormat(int num_args_wanted, int num_args_have);

void get_input(canvas_size myCanvas, char** canvas);
void print_help(canvas_size myCanvas, char**canvas);
void erase(canvas_size myCanvas, char**canvas);
void resize(canvas_size*myCanvas, char***canvas);
void add(canvas_size*myCanvas, char**canvas);
void delete(canvas_size*myCanvas, char**canvas);

void save(canvas_size myCanvas, char **canvas);
void read(canvas_size myCanvas, char **canvas);

void drawLine(canvas_size myCanvas, char** canvas);
void draw_slope_pos(int row1, int row2, int col1, int col2, char** canvas);
void draw_slope_neg(int row1, int row2, int col1, int col2, char** canvas);
void drawHorizontal(int rows, int col1, int col2, char **canvas);
void drawVertical(int row1, int row2, int cols, char **canvas);

#endif //PAINT_REMAKE_PAINT_H
