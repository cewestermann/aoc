#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

#define min(a, b) ((a) > (b) ? (b) : (a))

typedef int32_t i32;

char const* read_lines(char const* filename, i32 maxlines);

int main(int argc, char** argv) {
  read_lines("input.txt", 1500);

  return EXIT_SUCCESS;
}

char const* read_lines(char const* filename, i32 maxlines) {
  FILE* input = fopen(filename, "r");

  i32 n_lines = 0;

  char linebuf[MAX_LINE_LENGTH];

  while (fgets(linebuf, MAX_LINE_LENGTH, input)) {
    n_lines++;
  }
  i32 minimum = min(n_lines, maxlines);

  char const* lines = malloc(minimum * sizeof(char));

  for (size_t i = 0; i < minimum; i++) {
    printf("%s\n", lines[i]);
  }

  fclose(input);
}

