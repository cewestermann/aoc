#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 256

bool is_digit(char c) {
  return c >= '0' && c <= '9';
}

char* advance_past_gameid(char* linp) {
  while (*linp != ':') ++linp;
  ++linp;
  return linp;
}

int get_next_draw(char* linp, char* drawbuf) {
  char* drawp = drawbuf;
  int drawlen = 0;
  while (*linp != ';' && *linp != '\n') {
    *drawp++ = *linp++;
    ++drawlen;
  }
  /* Add one to go past ; */
  return drawlen;
}



int main(int argc, char **argv) {
  FILE* input = fopen("input.txt", "r");

  char lbuf[MAX_LINE_LENGTH];
  char* linp = lbuf;

  char drawbuf[MAX_LINE_LENGTH];
  int drawlen;

  int reds = 0;
  int greens = 0;
  int blues = 0;

  if (fgets(lbuf, sizeof lbuf, input)) {
    linp = advance_past_gameid(linp);
    printf("%s\n", lbuf);

    while ((drawlen = get_next_draw(linp, drawbuf) != 0)) {
      printf("%s\n", drawbuf);
      while (!is_digit(*linp)) ++linp;

      char digitbuf[MAX_LINE_LENGTH];
      char* dp = digitbuf;

      while (is_digit(*linp)) {
        *dp++ = *linp++;
      }
      *dp = '\0'; 

      int number = atoi(digitbuf);
      
      char colorbuf[MAX_LINE_LENGTH];
      char* cp = colorbuf;

      while (*linp != ',' && *linp != ';') {
        if (*linp == ' ') {
          linp++; 
          continue;
        }
        *cp++ = *linp++;
      }
      *cp = '\0';

      if (strcmp(colorbuf, "red")) reds += number;
      if (strcmp(colorbuf, "green")) greens += number;
      if (strcmp(colorbuf, "blue")) blues += number;

      //printf("%d, %d, %d\n", reds, greens, blues);

      linp += drawlen - 1;
     // printf("%c\n", *linp);

    }

    //linp += drawlen;

  }

  //printf("%s\n", drawbuf);
  //printf("%d\n", drawlen);
  //printf("%c\n", *linp);
  

  return EXIT_SUCCESS;
}


