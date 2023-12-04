#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 256

typedef struct {
  char* string;
  size_t len;
} Buffer;

bool is_digit(char c) {
  return c >= '0' && c <= '9';
}

char* move_past_gameid(char* cp) {
  if (cp) {
    while (*cp != ':') {
      cp++;
    }
    cp++; // Move past :
  }
  return cp;
}

int main(int argc, char **argv) {
  FILE* input;
  input = fopen("input.txt", "r");

  char buffer[MAX_LINE_LENGTH];
  char* cp;
  char current_draw[MAX_LINE_LENGTH];
  char* drawp; 

  int reds = 0;
  int blues = 0;
  int greens = 0;

  char digits[3];

  int digit_count = 0;

  Buffer draw_buffer;
  int i = 0;

  while (fgets(buffer, sizeof(buffer), input) != NULL) {
    cp = buffer;
    printf("%s\n", buffer);
    cp = move_past_gameid(cp);

    for (; 
    while (*cp != ';' && *cp != '\n' && *cp != '\0') {
      draw_buffer.string[i++] = *cp;
      cp++;
    }
    draw_buffer.string[i] = '\0';
    draw_buffer.len = i;

    printf("%s\n", draw_buffer.string);
    break;
    


  }
  fclose(input);
  return EXIT_SUCCESS;
}

