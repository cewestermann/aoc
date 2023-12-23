#ifndef AOC_COMMON_H
#define AOC_COMMON_H 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int32_t i32;

// Declarations
typedef struct {
  size_t len;
  char const* data;
} String;

String string_allocate(size_t size);
String string_from_literal(char const* literal);

typedef struct {
  size_t len;
  String* data;
} Strings;

Strings string_split_on(String s, char const delim);

// Definitions
String string_allocate(size_t size) {
  String s = {0};
  s.data = (char const*)malloc(size);
  if (s.data) {
    s.len = size;
  } else {
    fprintf(stderr, "Could not allocate String of size: %zu\n", size);
  }
  return s;
}

String string_from_literal(char const* literal) {
  char const* p = literal;

  size_t i = 0;
  while (literal[i++] != '\0');
  i--;

  String s = string_allocate(i);
  memcpy(s.data, literal, i);
  return s;
}

Strings string_split_on(String s, char const delim) {
  // TODO: Handle zero len s case
  
  size_t n_delims = 0;

  for (size_t i = 0; i < s.len; i++) {
    if (s.data[i] == delim) {
      n_delims++;
    }
  }

  Strings buffer;
  buffer.len = n_delims + 1; // Always one substring more than n_delims
  buffer.data = (String*)malloc(buffer.len * sizeof(String));

  size_t start_idx = 0;
  size_t substr_idx = 0;

  for (size_t i = 0; i < s.len; i++) {
    if (i == s.len || s.data[i] == delim) {
      size_t substr_len = i - start_idx;
      buffer.data[substr_idx] = string_allocate(substr_len);
      memcpy(buffer.data[substr_idx].data, s.data + start_idx, substr_len);
      buffer.data[substr_idx].len = substr_len;
      start_idx = i + 1;
      substr_idx++;
    }
  }
  return buffer;
}

void string_free(String* s) {
  if (s) {
    free(s->data);
  }
  s->data = 0;
  s->len = 0;
}

void strings_free(Strings* s) {
  if (s->data) {
    for (size_t i = 0; i < s->len; i++) {
      string_free(s->data[i]);
  }
  free(s->data);
  s->data = 0;
  s->len = 0;
  }
}

#endif
