#ifndef AOC_COMMON_H
#define AOC_COMMON_H 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// Declarations
typedef struct {
  size_t len;
  char const* data;
} String;

String string_allocate(size_t size);
String string_from_literal(char const* literal);
String read_entire_file(char const* filename);
void string_free(String* s);

typedef struct {
  size_t len;
  String* data;
} Strings;

Strings string_split_on(String s, char const delim);
void strings_free(Strings* s);

// Definitions
String string_allocate(size_t size) {
  String s = {0};
  s.data = malloc(size);
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
    if (s.data[i] == delim) {
      size_t substr_len = i - start_idx;
      buffer.data[substr_idx] = string_allocate(substr_len);
      memcpy(buffer.data[substr_idx].data, s.data + start_idx, substr_len);
      buffer.data[substr_idx].len = substr_len;
      start_idx = i + 1;
      substr_idx++;
    }
  }
  // Last substring
  size_t substr_len = s.len - start_idx;
  buffer.data[substr_idx] = string_allocate(substr_len);
  memcpy(buffer.data[substr_idx].data, s.data + start_idx, substr_len);
  return buffer;
}

String read_entire_file(char const* filename) {
  String s = {0};
  FILE* file = fopen(filename, "r");
#if _WIN32
  struct __stat64 Stat;
  _stat64(filename, &Stat);
#else
  struct stat Stat;
  stat(filename, &Stat);
#endif
  s = string_allocate(Stat.st_size);
  if (s.data) {
    if (fread(s.data, s.len, 1, file) != 1) {
      fprintf(stderr, "ERROR: Unable to read \"%s\".\n", filename);
      string_free(&s);
    }
    fclose(file);
  } else {
    fprintf(stderr, "ERROR: Unable to open \"%s\".\n", filename);
  }
  return s;
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
      string_free(&s->data[i]);
  }
  free(s->data);
  s->data = 0;
  s->len = 0;
  }
}

#endif
