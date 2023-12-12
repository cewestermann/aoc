#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE 512

typedef uint8_t u8;
typedef uint64_t u64;

typedef struct {
  int winning_numbers[10];
  int hand[25];
  int card_number;
} Card;

typedef struct {
  size_t size;
  char* data;
} Buffer;

typedef struct {
  Buffer source;
  u64 pos;
  bool had_error;
} Parser;

static Buffer allocate_buffer(size_t size) {
  Buffer buffer = {0};
  buffer.data = malloc(size);
  if (buffer.data) 
    buffer.size = size;
  else
    fprintf(stderr, "ERROR: Unable to allocate %zu bytes.\n", size);
  return buffer;
}

static void free_buffer(Buffer* buffer) {
  if (buffer->data) {
    free(buffer->data);
  }
  buffer->data = 0;
  buffer->size = 0;
}


int main(int argc, char** argv) {
  FILE* input = fopen("input.txt", "r");

  Card cards[204];
  size_t cidx = 0;

  Buffer buffer = allocate_buffer(MAX_LINE);

  while (fgets(buffer.data, MAX_LINE, input)) {
    Card card = {0};
    printf("%s\n", buffer.data);
    



    break;
  }
  return EXIT_SUCCESS;
}
