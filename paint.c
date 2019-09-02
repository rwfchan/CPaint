//
// Created by Raymond Chan on 12/7/17.
//

#include "paint.h"

void get_start_input(canvas_size*myCanvas, int argc, char**argv) {
  if(argc == 1) {
    myCanvas->rows = 10;
    myCanvas->cols = 10;
  } else if(argc != 3) {
    printf("Wrong number of command line arguements entered.\n");
    printf("Usage: ./paint.out [num_rows num_cols]\n");
    printf("Making default board of 10 X 10.\n");
    myCanvas->rows = 10;
    myCanvas->cols = 10;
  } else {
    int input_row = sscanf(argv[1], "%d", &myCanvas->rows);
    int input_col = sscanf(argv[2], "%d", &myCanvas->cols);

    if(input_row == 0) {
      printf("The number of rows is not an integer.\n");
      printf("Making default board of 10 X 10.\n");
      myCanvas->rows = 10;
      myCanvas->cols = 10;
      return;
    }
    if(input_col == 0) {
      printf("The number of columns is not an integer.\n");
      printf("Making default board of 10 X 10.\n");
      myCanvas->rows = 10;
      myCanvas->cols = 10;
      return;
    }

    if(myCanvas->rows < 1) {
      printf("The number of rows is less than 1.\n");
      printf("Making default board of 10 X 10.\n");
      myCanvas->rows = 10;
      myCanvas->cols = 10;
      return;
    }
    if(myCanvas->cols < 1) {
      printf("The number of columns is less than 1.\n");
      printf("Making default board of 10 X 10.\n");
      myCanvas->rows = 10;
      myCanvas->cols = 10;
      return;
    }
  }


}

char** make_size_broad(int rows, int cols) {
  char**arr = (char**) malloc((rows + 1) * sizeof(char*));
  for(int i = 0; i <= rows; i++) {
    arr[i] = (char*) malloc((cols + 1) * sizeof(char));
    for(int j = 0; j <= cols; j++) {
      if(i == 0 && j == 0) {
        arr[i][j] = ' ';
      }else if(i == 0) {
        arr[i][j] = ' ';
      }else if(j == 0) {
        arr[i][j] = ' ';
      }else {
        arr[i][j] = '*';
      }
    }
  }
  return arr;
}
void print_broad(int rows, int cols, char** arr) {
  for(int i = rows; i >= 0; i--) {
    for(int j = 0; j <= cols; j++) {
      if(j == 0 && i == 0) {
        printf("%c ", arr[i][j]);
      }else if(j == 0) {
        printf("%d ", i - 1);
      }else if(i == 0) {
        printf("%d ", j - 1);
      }else {
        printf("%c ", arr[i][j]);
      }
    }
    printf("\n");
  }
}

void get_input(canvas_size myCanvas, char** canvas) {
  char user_input;
  int num_args_wanted = 1;
  do {
    printf("Enter your command: ");
    int num_args_have = scanf(" %c", &user_input);
    switch (user_input) {
      case 'q':
        if(!isVaildFormat(num_args_wanted, num_args_have)){
          printf("Unrecognized command. Type h for help.\n");
          print_broad(myCanvas.rows, myCanvas.cols, canvas);
          break;
        }
        exit(0);
      case 'h':
        if(!isVaildFormat(num_args_wanted, num_args_have)){
          printf("Unrecognized command. Type h for help.\n");
          print_broad(myCanvas.rows, myCanvas.cols, canvas);
          break;
        }
        print_help(myCanvas, canvas);
        break;
      case 'w':drawLine(myCanvas, canvas);
        break;
      case 'e':erase(myCanvas, canvas);
        break;
      case 'r':resize(&myCanvas, &canvas);
        break;
      case 'a':add(&myCanvas, canvas);
        break;
      case 'd':delete(&myCanvas, canvas);
        break;
      case 's':save(myCanvas, canvas);
        break;
      case 'l':read(myCanvas, canvas);
        break;
      default:
        if(!isVaildFormat(num_args_wanted, num_args_have)){
          printf("Unrecognized command. Type h for help.\n");
          print_broad(myCanvas.rows, myCanvas.cols, canvas);
          break;
        }
        printf("Unrecognized command. Type h for help.\n");
        print_broad(myCanvas.rows, myCanvas.cols, canvas);
        break;
    }
  }while (true);
}
void read(canvas_size myCanvas, char **canvas) {
  char string[30];
  scanf(" %s", string);

  FILE*file_name = fopen(string, "rb");

  if(file_name == NULL) {
    printf("Failed to open file: %s\n", string);
    print_broad(myCanvas.rows, myCanvas.cols, canvas);
    return;
  }

  int num;
  fread(&num, sizeof(int), 1, file_name);
/*  while(!feof(file_name)) {

  }*/
  fclose(file_name);

}

void save(canvas_size myCanvas, char **canvas) {
  char string[30];
  int num_args_wanted = 1;
  int num_args_have = scanf(" %s", string);

  if(!isVaildFormat(num_args_wanted, num_args_have)) {
    printf("Improper delete command.\n");
  }

  FILE*file_name = fopen(string, "wb");

  if(file_name == NULL) {
    return;
  }
  for(int i = 0; i <= myCanvas.rows; i++) {
    fwrite(canvas[i], sizeof(char), sizeof(canvas[i]), file_name);
  }

  fclose(file_name);

  print_broad(myCanvas.rows, myCanvas.cols, canvas);
}

void delete(canvas_size*myCanvas, char**canvas) {
  char input, input2;
  int remove_line;
  int num_args_wanted = 3;
  int num_args_have = scanf("%c %c %d", &input, &input2, &remove_line);

  if(!isVaildFormat(num_args_wanted, num_args_have)) {
    printf("Improper delete command.\n");
    print_broad(myCanvas->rows, myCanvas->cols, canvas);
    return;
  }

  if(input2 == 'r') {
    if(remove_line >= myCanvas->rows || remove_line < 0) {
      printf("Improper delete command.\n");
      print_broad(myCanvas->rows, myCanvas->cols, canvas);
      return;
    }

    for(int i = remove_line + 1; i < myCanvas->rows; i++) {
      for(int j = 1; j <= myCanvas->cols; j++) {
        canvas[i][j] = canvas[i + 1][j];
      }
    }
    canvas = (char**) realloc(canvas, (myCanvas->rows) * sizeof(char*));
    myCanvas->rows --;
  }else if(input2 == 'c') {
    if(remove_line >= myCanvas->cols || remove_line < 0) {
      printf("Improper delete command.\n");
      print_broad(myCanvas->rows, myCanvas->cols, canvas);
      return;
    }
    for(int i = 0; i <= myCanvas->rows; i++) {
      for(int j = remove_line + 1; j < myCanvas->cols; j++) {
        canvas[i][j] = canvas[i][j + 1];
      }
      canvas[i] = (char*) realloc(canvas[i], (myCanvas->cols) * sizeof(char));
    }
    myCanvas->cols --;
  }

  print_broad(myCanvas->rows, myCanvas->cols, canvas);
}
void add_sub(canvas_size*myCanvas, char***canvas) {
  *canvas = (char**) realloc((*canvas), (myCanvas->rows + 2) * sizeof(char*));
  (*canvas)[myCanvas->rows + 1] = (char*) malloc((myCanvas->cols + 1) * sizeof(char));
}
void add(canvas_size*myCanvas, char**canvas) {
  char input, input2;
  int add_line;
  int num_args_wanted = 3;
  int num_args_have = scanf("%c %c %d", &input, &input2, &add_line);

  if(!isVaildFormat(num_args_wanted, num_args_have) || add_line < 0) {
    printf("Improper add command.\n");
    print_broad(myCanvas->rows, myCanvas->cols, canvas);
    return;
  }

  if(input2 == 'r') {
    if(add_line > myCanvas->rows) {
      printf("Improper add command.\n");
      print_broad(myCanvas->rows, myCanvas->cols, canvas);
      return;
    }
    add_sub(myCanvas, &canvas);
    for(int i = myCanvas->rows; i > add_line; i--) {
      for(int j = 1; j <= myCanvas->cols + 1; j++) {
        canvas[i + 1][j] = canvas[i][j];
      }
    }
    for(int i = 1; i <= myCanvas->cols + 1; i++) {
      canvas[add_line + 1][i] = '*';
    }
    myCanvas->rows++;
  } else if(input2 == 'c') {
    if(add_line > myCanvas->cols) {
      printf("Improper add command.\n");
      print_broad(myCanvas->rows, myCanvas->cols, canvas);
      return;
    }
    for(int i = 0; i <= myCanvas->rows; i++) {
      canvas[i] = (char*) realloc(canvas[i], (myCanvas->cols + 2) * sizeof(char));
      for(int j = myCanvas->cols + 1; j > add_line; j--) {
        canvas[i][j + 1] = canvas[i][j];
      }
      canvas[i][add_line + 1] = '*';
    }
    myCanvas->cols++;
  }

  print_broad(myCanvas->rows, myCanvas->cols, canvas);
}

void resize(canvas_size*myCanvas, char***canvas) {
  char input;
  int new_rows, new_cols;
  int num_args_wanted = 3;
  int num_args_have = scanf("%c %d %d", &input, &new_rows, &new_cols);

  if(!isVaildFormat(num_args_wanted, num_args_have) || new_rows < 1 || new_cols < 1) {
    printf("Improper resize command.\n");
    print_broad(myCanvas->rows, myCanvas->cols, *canvas);
    return;
  }

  *canvas = (char**) realloc(*canvas, (new_rows + 1) * sizeof(char*));
  for(int i = 0; i <= new_rows; i++) {
    (*canvas)[i] = (char*) realloc((*canvas)[i], (new_cols + 1) * sizeof(char));
  }
  for(int i = 1; i <= new_rows; i++) {
    for(int j = 0; j <= new_cols; j++) {
      if(i > myCanvas->rows || j > myCanvas->cols) {
        (*canvas)[i][j] = '*';
      }
    }
  }

  myCanvas->rows = new_rows;
  myCanvas->cols = new_cols;

  print_broad(myCanvas->rows, myCanvas->cols, *canvas);
}

void erase(canvas_size myCanvas, char**canvas) {
  char input;
  int row, col;
  int num_args_wanted = 3;
  int num_args_have = scanf("%c %d %d", &input, &row, &col);

  if(!isVaildFormat(num_args_wanted, num_args_have)) {
    printf("Improper erase command.\n");
    print_broad(myCanvas.rows, myCanvas.cols, canvas);
    return;
  }

  if(row < 0) {
    printf("Improper erase command.\n");
    print_broad(myCanvas.rows, myCanvas.cols, canvas);
    return;
  }
  if(col < 0) {
    printf("Improper erase command.\n");
    print_broad(myCanvas.rows, myCanvas.cols, canvas);
    return;
  }
  if(row >= myCanvas.rows || col >= myCanvas.cols) {
    printf("Improper erase command.\n");
    print_broad(myCanvas.rows, myCanvas.cols, canvas);
    return;
  }

  canvas[row + 1][col + 1] = '*';
  print_broad(myCanvas.rows, myCanvas.cols, canvas);
}

void drawLine(canvas_size myCanvas, char** canvas) {
  char input;
  int row1, col1, row2, col2;
  int num_args_wanted = 5;
  int num_args_have = scanf("%c %d %d %d %d", &input, &row1, &col1, &row2, &col2);

  if(!isVaildFormat(num_args_wanted, num_args_have)) {
    printf("Improper draw command.\n");
    print_broad(myCanvas.rows, myCanvas.cols, canvas);
    return;
  }

  if(row1 < 0 || row2 < 0 || row1 >= myCanvas.rows || row2 >= myCanvas.rows) {
    printf("Improper draw command.\n");
    print_broad(myCanvas.rows, myCanvas.cols, canvas);
    return;
  }
  if(col1 < 0 || col2 < 0 || col1 >= myCanvas.cols || col2 >= myCanvas.cols) {
    printf("Improper draw command.\n");
    print_broad(myCanvas.rows, myCanvas.cols, canvas);
    return;
  }

  int slope = 0;
  if(col2 != col1){
    slope = (row2 - row1)/(col2 - col1);
  }
  //draw_stuff
  if(slope == 0) {
    if(row1 == row2) {
      drawHorizontal(row1, col1, col2, canvas);
    } else if (col1 == col2){
      drawVertical(row1, row2, col1, canvas);
    } else {
      printf("Cannot draw the line as it is not straight.\n");
    }
  } else if (slope == 1 || slope == -1) {
    if (slope < 0) {
      //slope is -1
      draw_slope_neg(row1, row2, col1, col2, canvas);
    } else if (slope > 0) {
      //slope is... well you know
      draw_slope_pos(row1, row2, col1, col2, canvas);
    }
  } else {
    printf("Cannot draw the line as it is not straight.\n");
  }

  print_broad(myCanvas.rows, myCanvas.cols, canvas);
}
void draw_slope_pos(int row1, int row2, int col1, int col2, char** canvas) {
  if(row1 > row2 && col1 > col2) {
    int j = col2 + 1;
    for(int i = row2 + 1; i <= row1 + 1; i++) {
      if(j <= col1 + 1){
        if(canvas[i][j] == '*' || canvas[i][j] == '/') {
          canvas[i][j] = '/';
        } else {
          canvas[i][j] = '+';
        }
      }
      j++;
    }
  } else {
    int j = col1 + 1;
    for(int i = row1 + 1; i <= row2 + 1; i++) {
      if(j <= col2 + 1){
        if(canvas[i][j] == '*' || canvas[i][j] == '/') {
          canvas[i][j] = '/';
        } else {
          canvas[i][j] = '+';
        }
      }
      j++;
    }
  }
}
void draw_slope_neg(int row1, int row2, int col1, int col2, char** canvas) {
  if(row1 < row2 && col1 > col2) {
    int j = col2 + 1;
    for(int i = row2 + 1; i >= row1 + 1; i--) {
      if(j <= col1 + 1){
        if(canvas[i][j] == '*' || canvas[i][j] == '\\') {
          canvas[i][j] = '\\';
        } else {
          canvas[i][j] = '+';
        }
      }
      j++;
    }
  } else {
    int j = col1 + 1;
    for(int i = row1 + 1; i >= row2 + 1; i--) {
      if(j <= col2 + 1){
        if(canvas[i][j] == '*' || canvas[i][j] == '\\') {
          canvas[i][j] = '\\';
        } else {
          canvas[i][j] = '+';
        }
      }
      j++;
    }
  }
}
void drawHorizontal(int rows, int col1, int col2, char **canvas) {
  int row = rows + 1;
  if(col1 < col2) {
    for(int i = col1 + 1; i <= col2 + 1; i++) {
      if(canvas[row][i] == '*' || canvas[row][i] == '-') {
        canvas[row][i] = '-';
      } else {
        canvas[row][i] = '+';
      }
    }
  } else {
    for(int i = col2 + 1; i <= col1 + 1; i++) {
      if(canvas[row][i] == '*' || canvas[row][i] == '-') {
        canvas[row][i] = '-';
      } else {
        canvas[row][i] = '+';
      }
    }
  }
}
void drawVertical(int row1, int row2, int cols, char **canvas) {
  int col = cols + 1;
  if (row1 < row2) {
    for (int i = row1 + 1; i <= row2 + 1; i++) {
      if (canvas[i][col] == '*' || canvas[i][col] == '|') {
        canvas[i][col] = '|';
      } else {
        canvas[i][col] = '+';
      }
    }
  } else {
    for (int i = row2 + 1; i <= row1 + 1; i++) {
      if (canvas[i][col] == '*' || canvas[i][col] == '|') {
        canvas[i][col] = '|';
      } else {
        canvas[i][col] = '+';
      }
    }
  }
}

void free_arr(int rows, char***arr) {
  for(int i = 0; i <= rows; i++) {
    free((*arr)[i]);
  }
  free(*arr);
  *arr = NULL;
}
void print_help(canvas_size myCanvas, char**canvas){
  printf("Commands:\n");
  printf("Help: h\n");
  printf("Quit: q\n");
  printf("Draw line: w row_start col_start row_end col_end\n");
  printf("Resize: r num_rows num_cols\n");
  printf("Add row or column: a [r | c] pos\n");
  printf("Delete row or column: d [r | c] pos\n");
  printf("Erase: e row col\n");
  printf("Save: s file_name\n");
  printf("Load: l file_name\n");
  print_broad(myCanvas.rows, myCanvas.cols, canvas);
}

bool isVaildFormat(int num_args_wanted, int num_args_have) {
  bool format_is_good = num_args_wanted == num_args_have;

  char character;

  do{
    scanf("%c",&character);
    if(!isspace(character)){
      format_is_good = false;
    }
  }while(character != '\n');

  return format_is_good;
}

