#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE 256
#define MAX_DRAW 64

#define MAX_RED 12
#define MAX_GREEN 13
#define MAX_BLUE 14

static int get_gameid(void);
static int get_draw(void);
static bool is_digit(char c);
static void print_ids(void);
static int sum_ids(void);

static char draw[MAX_DRAW];
static char game[MAX_LINE];
static char* gp = game;
static int possible_ids[100];
int idp = 0;

int main(int argc, char **argv) {
  FILE* input = fopen("input.txt", "r");

  bool impossible = false;

  while (fgets(game, sizeof game, input)) {
    printf("%s\n", game);
    int gameid = get_gameid();
    printf("%d\n", gameid);

    int res;
    int num;
    char type[10];

    while ((res = get_draw()) != 0) {
      int num;
      char type[10];

      sscanf(draw, "%d %s", &num, type);
      gp++;
      printf("%s, %d\n", type, num);

      if ((!strcmp(type, "red") && num > MAX_RED) ||
          (!strcmp(type, "green") && num > MAX_GREEN) ||
          (!strcmp(type, "blue") && num > MAX_BLUE)) {
        impossible = true;
        break;
      }
    }

    if (!impossible) {
      if (!res) {
        sscanf(draw, "%d %s", &num, type);
        gp++;
        if ((!strcmp(type, "red") && num > MAX_RED) ||
            (!strcmp(type, "green") && num > MAX_GREEN) ||
            (!strcmp(type, "blue") && num > MAX_BLUE)) {
          impossible = true;
        }
      }
    }

    if (!impossible) {
      possible_ids[idp++] = gameid;
    }
    gp = game;
    impossible = false;
  }
  int sum = sum_ids();
  printf("%d\n", sum);
  fclose(input);
}

static void print_ids(void) {
  for (int i = 0; i <= idp; i++) {
    printf("%d\n", possible_ids[i]);
  }
}

static int sum_ids(void) {
  int sum = 0;
  for (int i = 0; i < idp; i++) {
    sum += possible_ids[i];
  }
  return sum;
}

static int get_gameid(void) {
  char gameid[4];
  char* gid = gameid;

  while (*gp != ':') {
    if (is_digit(*gp))
      *gid++ = *gp;
      gp++;
      while (is_digit(*gp)) {
        *gid++ = *gp++;
      }
  }
  *gid = '\0';

  gp++; // Move past :
  return atoi(gameid);
}

static int get_draw(void) {
  char *p = draw;

  while (*gp != ',' && *gp != ';' && *gp != '\n') {
    *p++ = *gp++;
  }
  *p = '\0';

  if (*gp == '\n' || *gp == '\0') {
    return 0;
  } else {
    return 1;
  }
}

static bool is_digit(char c) {
  return c >= '0' && c <= '9';
}

