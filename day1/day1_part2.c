#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

typedef char u8;

char number_word(char* cp, u8* length) {
  if (cp) {
    switch (*cp) {
      case 'o': 
        if (strncmp(cp, "one", 3) == 0) {
          *length = 3;
          return '1';
        } break;
      case 't': 
        if (strncmp(cp, "two", 3) == 0)  {
          *length = 3;
          return '2';
        }
        if (strncmp(cp, "three", 5) == 0) {
          *length = 5;
          return '3';
        } break;
      case 'f':
        if (strncmp(cp, "four", 4) == 0) {
          *length = 4;
          return '4';
        } 
        if (strncmp(cp, "five", 4) == 0) {
          *length = 4;
          return '5';
        } break;
      case 's':
        if (strncmp(cp, "six", 3) == 0) {
          *length = 3;
          return '6';
        }
        if (strncmp(cp, "seven", 5) == 0) {
          *length = 5;
          return '7';
        } break;
      case 'e': 
        if (strncmp(cp, "eight", 5) == 0) {
          *length = 5;
          return '8';
        } break;
      case 'n': 
        if (strncmp(cp, "nine", 4) == 0) {
          *length = 4;
          return '9';
        } break;
    }
  }
  return 0;
}

int main(int argc, char** argv) {

  FILE* input;
  input = fopen("input.txt", "r");

  char buffer[MAX_LINE_LENGTH];

  int first_num = 0;
  int second_num = 0;

  char concat[3];

  char* cp;
  char num;
  u8 length;

  int running_sum = 0;

  while (fgets(buffer, sizeof(buffer), input) != NULL) {
    cp = buffer;
    printf("%s\n", buffer);
    while (*cp) {
      if (isdigit(*cp)) {
        if (first_num == 0)
          first_num = *cp;
        second_num = *cp;
      } else if ((num = number_word(cp, &length)) != 0) {
        if (first_num == 0) {
          first_num = num;
        }
        second_num = num;
        //cp += length;
      }
      cp++;
    }
    concat[0] = first_num;
    concat[1] = second_num;
    concat[2] = '\0';

    printf("%s\n", concat);

    running_sum += atoi(concat);

    first_num = 0;
    second_num = 0;

    memset(concat, 0, sizeof(concat));
  }

  printf("Sum: %d\n", running_sum);
  fclose(input);
}
