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
void print_perimiter(PartNumber num, LineWindow* lw);
void print__single(PartNumber num, i32 len, String s);


int main(int argc, char** argv) {
  String input = read_entire_file("input.txt");
  Strings lines = string_split_on(input, '\n');

  LineWindow lw = {0};

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
        numbers[pcount].end = i;
        numbers[pcount].value = atoi(digit);
        pcount++;
      }
    }

    for (size_t i = 0; i < pcount; i++) {
      print_perimiter(numbers[i], &lw);
    }
  }
  return EXIT_SUCCESS;
}

bool is_digit (char const c) {
  return c <= '9' && c >= '0';
}

void print_perimiter(PartNumber num, LineWindow* lw) {
  i32 len = (num.end + 1) - (num.start - 1);

  if (lw->prev.data) {
    print__single(num, len, lw->prev);
  }

  print__single(num, len, lw->center);

  if (lw->next.data) { 
    print__single(num, len, lw->next);
  }
  printf("\n");
}

void print__single(PartNumber num, i32 len, String s) {
  char pbuf[8] = {0};

  strncpy(pbuf, &s.data[num.start - 1], len);
  printf("%s\n", pbuf);
  pbuf[len] = '\0';
}
