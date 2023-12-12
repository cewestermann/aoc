#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 256

char line[MAX_LINE];

typedef struct {
  char draws[10][100];
  size_t n_draws;
} Game;

int get_next_game(FILE* input, Game* game);
void game_print(Game game);
int calculate_power(int colors[]);

int main(int argc, char** argv) {
  FILE* input = fopen("input.txt", "r");

  Game game;

  int power_sum = 0;
  while ((get_next_game(input, &game))) {
    game_print(game);

    int power;
    
    int max_red = 0;
    int max_blue = 0;
    int max_green = 0;

    for (size_t i = 0; i < game.n_draws; i++) {
      char* draw = game.draws[i];
      int number;
      char color[10];

      char* dp = draw;

      while (*dp) {
        while (isspace(*dp)) dp++;

        if (sscanf(dp, "%d", &number) == 1) {

          while (isdigit(*dp) || isspace(*dp)) dp++;

          sscanf(dp, "%[^,]", color);

          while (isalpha(*dp)) dp++;
        }

        if (!strcmp(color, "red") && number > max_red) max_red = number;
        if (!strcmp(color, "blue") && number > max_blue) max_blue = number;
        if (!strcmp(color, "green") && number > max_green) max_green = number;

        printf("Color: %s, Number: %d\n", color, number);

      while (isspace(*dp) || *dp == ',') dp++;
      }

    }

    int colors[] = {max_red, max_green, max_blue};

    printf("Red: %d, Green: %d, Blue: %d\n", max_red, max_green, max_blue);

    power = calculate_power(colors);
    printf("Power: %d\n", power);
    power_sum += power;
  }

  printf("Power sum: %d\n", power_sum);
  fclose(input);
  return EXIT_SUCCESS;
}

int calculate_power(int colors[]) {
  int power = 1;

  for (int i = 0; i < 3; i++) {
    int c = colors[i];
    if (c)
      power *= c;
  }
  return power;
}

int get_next_game(FILE* input, Game* game) {
  char data[MAX_LINE];
  char* dp;

  if (fgets(data, sizeof data, input)) {
    dp = strchr(data, ':');
    if (!dp) return 0;
    dp++;

    game->n_draws = 0;
    char* start = dp;
    int draw_len = 0;

    for (; *dp != '\0' && game->n_draws < 10; dp++) {
      if (*dp == ';' || *dp == '\n') {
        if (draw_len > 0) {
          strncpy(game->draws[game->n_draws], start, draw_len);
          game->draws[game->n_draws][draw_len] = '\0';
          game->n_draws++;
        }
        draw_len = 0;
        start = dp + 1;
      } else {
        draw_len++;
      }
    }
    return 1;
    }
  return 0;
}

void game_print(Game game) {
  printf("Number of draws: %zu\n", game.n_draws);
  for (size_t i = 0; i < game.n_draws; i++) {
    printf("%s\n", game.draws[i]);
  }
}

