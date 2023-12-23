#include "../aoc_common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef int32_t i32;

typedef struct {
  String prev;
  String center;
  String next;
} LineWindow;

typedef struct {
  i32 value;
  size_t start;
  size_t end;
} PartNumber;

bool is_digit(char const c);

int main(int argc, char** argv) {
  String input = read_entire_file("input.txt");
  Strings lines = string_split_on(input, '\n');

  LineWindow lw;

  for (size_t i = 0; i < lines.len; i++) {
    lw.center = lines.data[i];
    if (i == 0) {
      lw.next = lines.data[i+1];
    } else if (i == (lines.len - 1)) {
      lw.prev = lines.data[i-1];
    } else {
      lw.next = lines.data[i+1];
      lw.prev = lines.data[i-1];
    }

    PartNumber numbers[32];
    size_t pcount = 0;

    for (size_t i = 0; i < lw.center.len; i++) {
      char digit[4];
      size_t dcount = 0;

      if (is_digit(lw.center.data[i])) {
        numbers[pcount].start = i;
        while (is_digit(lw.center.data[i])) {
          digit[dcount++] = lw.center.data[i++];
        }
        digit[dcount] = '\0';
        numbers[pcount].end = i - 1;
        numbers[pcount].value = atoi(digit);
        pcount++;
      }
    }

    for (size_t i = 0; i < pcount; i++) {
      char printbuf[6];
      printf("%d\n", numbers[i].value);
    }
  }




  return EXIT_SUCCESS;
}

bool is_digit (char const c) {
  return c <= '9' && c >= '0';
}
