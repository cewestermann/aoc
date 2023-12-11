#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINES 256
#define MAX_CHAR 512

typedef struct {
  char lines[MAX_LINES][MAX_CHAR];
  size_t n_lines;
  size_t center_idx;
} Data;

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
  if (data->center_idx == data->n_lines) {
    lw->next = 0;
  } else {
    lw->next = data->lines[data->center_idx + 1];
  }
  return 1;
}

int main(int argc, char** argv) {
  Data data = read_data("input.txt");
  LineWindow lw = {0};
  next_window(&data, &lw);
  data.center_idx++;

  char* cp = lw.center;

  char digit[4];
  char* dp = digit;

  int lineidx = 0;
  int prior;

  int part_sum = 0;

  while (next_window(&data, &lw)) {
    while (*cp != '\0') {
      if (isdigit(*cp)) {
        prior = lineidx;
        while (isdigit(*cp)) {
          *dp++ = *cp++;
          lineidx++;
        }
        *dp = '\0';
  
        int value = atoi(digit);
        int before = prior - 1;
        int after = prior + 3;
  
        int is_bad = false;
  
        if (lw.previous) {
          for (int i = before; i != (after + 1); i++) {
            if (lw.previous[i] != '.') {
              printf("Above: %c\n", lw.previous[i]);
              is_bad = true;
            }
          }
        }
  
        if (is_bad) continue;
  
        if (lw.center[before] != '.' || lw.center[after] != '.') {
          printf("Before: %c\n", lw.center[before]);
          printf("After: %c\n", lw.center[after]);
          continue;
        }
  
        if (lw.next) {
          for (int i = before; i != (after + 1); i++) {
            if (lw.next[i] != '.') {
              printf("Below: %c\n", lw.next[i]);
              is_bad = true;
            }
          }
        }
  
        if (is_bad) continue;
  
        part_sum += value;
      }
      cp++;
      lineidx++;
      dp = digit;
    }
  }

  printf("%d\n", part_sum); // 1226

  printf("%s\n", lw.previous);
  printf("%s\n", lw.center);
  printf("%s\n", lw.next);

  return EXIT_SUCCESS;
}
