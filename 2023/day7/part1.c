#include <stdio.h>
#include <stdlib.h>

typedef int32_t i32;

#define MAX_LINE_LENGTH 32

enum {
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  NINE,
  TEN,
  JACK,
  QUEEN,
  KING,
  ACE,
  N_ELEMENTS
};

i32 map2enum(char const c) {
  switch (c) {
    case '2': return TWO;
    case '3': return THREE;
    case '4': return FOUR;
    case '5': return FIVE;
    case '6': return SIX;
    case '7': return SEVEN;
    case '8': return EIGHT;
    case '9': return NINE;
    case 'T': return TEN;
    case 'J': return JACK;
    case 'Q': return QUEEN;
    case 'K': return KING;
    case 'A': return ACE;
    default: return -1;
  }
}

typedef struct {
  char hand[5];
  i32 bid;
} Draw;

Draw parse_draw(char const* input) {
  Draw draw = {0};
  sscanf(input, "%s %d", draw.hand, &draw.bid);
  return draw;
}

// Find out the number of distict cards in a hand:
//
// 5 distinct = High card
// 4 distinct = One pair
// 3 distinct = Two Pair | Three of a kind
// 2 distinct = Full House | Four of a kind
// 1 distinct = Five of a kind

int main(int argc, char** argv) {

  FILE* input = fopen("input.txt", "r");

  char buffer[MAX_LINE_LENGTH];

  i32 lc = 0;
  while (fgets(buffer, MAX_LINE_LENGTH, input)) {
    //printf("%s\n", buffer);

    Draw draw = parse_draw(buffer);
    printf("%s, %d\n", draw.hand, draw.bid);

    char* groups[5];

    for (size_t i = 0; i < 5; i++) {
      
    }



    lc++;
    if (lc == 5) break;
  }

  fclose(input);

  return EXIT_SUCCESS;
}
