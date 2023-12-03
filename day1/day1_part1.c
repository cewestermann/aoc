#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256


int main(int argc, char **argv) {
  FILE* input;
  input = fopen("input.txt", "r");

  char buffer[MAX_LINE_LENGTH];

  int first_num = -1;
  int second_num = -1;

  char current_char;
  char concatenated[3];

  int running_sum = 0;


  while (fgets(buffer, sizeof(buffer), input) != NULL) {
    printf("%s\n", buffer);

    for (int i = 0; buffer[i] != '\0'; i++) {
      current_char = buffer[i];
      if (isdigit(current_char)) {
        if (first_num == -1) {
          first_num = current_char;
        }
        second_num = current_char;
      }
    }

    concatenated[0] = first_num;
    concatenated[1] = second_num;
    concatenated[2] = '\0';

    running_sum += atoi(concatenated);

    first_num = -1;
    second_num = -1;

    memset(concatenated, 0, sizeof(concatenated));
  }

  printf("%d\n", running_sum);
  fclose(input);
}
