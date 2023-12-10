#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 256
#define MAX_CHAR 512

typedef struct {
  char lines[MAX_LINES][MAX_CHAR];
  size_t n_lines;
} Data;

typedef struct {
  char* previous;
  char* center;
  char* next;
} LineWindow;

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

int main(int argc, char** argv) {
  Data data = read_data("input.txt");


  return EXIT_SUCCESS;
}
