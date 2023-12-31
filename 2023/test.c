#include "aoc_common.h"

int main(int argc, char** argv) {

  char const* literal = "Cookies. are. great";

  String string = string_from_literal(literal);
  printf("%s\n", string.data);

  Strings strings = string_split_on(string, '.');

  for (size_t i = 0; i < strings.len; i++) {
    printf("%s\n", strings.data[i].data);
  }

  strings_free(&strings);

  return EXIT_SUCCESS;
}
