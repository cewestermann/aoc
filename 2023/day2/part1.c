#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

int main(int argc, char **argv) {
  FILE* input;
  input = fopen("input.txt", "r");


  char buffer[MAX_LINE_LENGTH];

  while (fgets(buffer, sizeof(buffer), input) != NULL) {
    printf("%s\n", buffer);
    char* token;

    token = strtok(buffer, ": ,;");

    while (token != 0) {
      printf("%s\n", token);
      token = strtok(0, buffer);
    }

  }


  fclose(input);
  return EXIT_SUCCESS;
}

