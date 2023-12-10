#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 256
#define MAX_CHAR 512

typedef struct {
  char lines[MAX_LINES][MAX_CHAR];
  size_t n_lines;
  size_t center_idx;
} Data;

typedef struct {
  size_t start;
  size_t end;
  int num;
} Number;

typedef struct {
  char* previous;
  char* center;
  char* next;
} LineWindow;

Data read_data(char* filename);
int next_window(Data* data, LineWindow* lw);

Data read_data(char* filename) {
  FILE* input = fopen(filename, "r");
  Data data = {0};

  while (fgets(data.lines[data.n_lines], MAX_CHAR, input)) {
    data.lines[data.n_lines][strlen(data.lines[data.n_lines]) - 1] = '\0';
    data.n_lines++;
  }

  fclose(input);
  return data;
}

int next_window(Data* data, LineWindow* lw) {
  if (!data->center_idx) {
    lw->previous = 0;
  } else {
    lw->previous = data->lines[data->center_idx - 1];
  }
  lw->center = data->lines[data->center_idx];
  lw->next = data->lines[data->center_idx + 1];
  return EXIT_SUCCESS;
}

int main(int argc, char** argv) {
  Data data = read_data("input.txt");
  LineWindow lw = {0};
  next_window(&data, &lw);

  printf("%s\n", lw.previous);
  printf("%s\n", lw.center);
  printf("%s\n", lw.next);

  return EXIT_SUCCESS;
}
