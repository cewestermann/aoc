#include "aoc_common.h"

int main(int argc, char** argv) {

  char const* literal = "Cookies. are. great";

  String string = string_from_literal(literal);
  printf("%s\n", string.data);

  Strings strings = string_split_on(string, '.');

  printf("%zu\n", strings.len);

  return EXIT_SUCCESS;
}
