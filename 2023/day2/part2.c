#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uint32_t u32;

#define MAX_LINE 256

char line[MAX_LINE];

typedef struct {
  char* draws[10];
  size_t n_draws;
} Game;

int get_next_game(FILE* input, Game* game);

int main(int argc, char** argv) {
  FILE* input = fopen("input.txt", "r");

  Game game;

  while ((get_next_game(input, &game))) {
    for (size_t i = 0; i < game.n_draws; i++ ) {
    }
  }
  fclose(input);
  return EXIT_SUCCESS;
}

int get_next_game(FILE* input, Game* game) {
  char data[MAX_LINE];
  char* dp = data;
  char* draws[10];

  char draw;
  char* drawp;

  if (fgets(data, sizeof data, input)) {
    while (*dp++ != ':');
    dp++;







    return 1;
  } else {
    return 0;
  }
}





