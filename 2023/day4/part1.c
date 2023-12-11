#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  int winning_numbers[10];
  int hand[25];
  int card_number;
} Card;

int main(int argc, char** argv) {
  FILE* input = fopen("input.txt", "r");

  Card cards[204];
  char buffer[512];

  while (fgets(buffer, sizeof buffer, input)) {

  }


  return EXIT_SUCCESS;
}
