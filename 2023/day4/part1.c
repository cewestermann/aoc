#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdint.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_LINE 512

typedef uint8_t u8;
typedef uint64_t u64;

typedef struct {
  size_t size;
  u8* data;
} Buffer;

static Buffer read_entire_file(char* filename);
static Buffer* split_on(Buffer* buffer, char delimiter, size_t *count);
static void free_buffers(Buffer* buffers, size_t count);

int main(int argc, char** argv) {
  Buffer buffer = read_entire_file("input.txt");

  size_t count = 0;
  Buffer* buffers = split_on(&buffer, '\n', &count);

  int total_points = 0;

  for (size_t i = 0; i < count - 1; i++) {
    size_t linecount = 0;
    Buffer* linebuffers = split_on(&buffers[i], '|', &linecount);
    u8* winning_numbers = linebuffers[1].data;

    size_t coloncount = 0;
    Buffer* left = split_on(&linebuffers[0], ':', &coloncount);
    u8* hand = left[1].data;

    int winnum[25];
    int handnum[10];

    sscanf((char*)winning_numbers, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
        &winnum[0], &winnum[1], &winnum[2], &winnum[3], &winnum[4],
        &winnum[5], &winnum[6], &winnum[7], &winnum[8], &winnum[9],
        &winnum[10], &winnum[11], &winnum[12], &winnum[13], &winnum[14],
        &winnum[15], &winnum[16], &winnum[17], &winnum[18], &winnum[19],
        &winnum[20], &winnum[21], &winnum[22], &winnum[23], &winnum[24]);

    sscanf((char*)hand, "%d %d %d %d %d %d %d %d %d %d",
        &handnum[0], &handnum[1], &handnum[2], &handnum[3], &handnum[4],
        &handnum[5], &handnum[6], &handnum[7], &handnum[8], &handnum[9]);

    int points = 0;
    for (size_t j = 0; j < 10; j++) {
      for (size_t k = 0; k < 25; k++) {
        if (handnum[j] == winnum[k]) {
          printf("%d, %d\n", handnum[j], winnum[k]);
          if (points == 0) {
            points = 1;
          } else {
            points += points;
          }
        }
      }
    }
    total_points += points;
    free_buffers(linebuffers, linecount);
    free_buffers(left, coloncount);
  }
  printf("%d\n", total_points);
  free_buffers(buffers, count);
  return EXIT_SUCCESS;
}

static Buffer allocate_buffer(size_t size) {
  Buffer result = {0};
  result.data = malloc(size);
  if (result.data)
    result.size = size;
  else
   fprintf(stderr, "ERROR: Unable to allocate %zu bytes.\n", size);
  return result;
}

static void free_buffer(Buffer* buffer) {
  if (buffer->data)
    free(buffer->data);
  buffer->size = 0;
  buffer->data = 0;
}

static Buffer read_entire_file(char* filename) {
  Buffer result = {0};

  FILE* file = fopen(filename, "rb");

#if _WIN32
  struct __stat64 Stat;
  _stat64(filename, &Stat);
#else
  struct stat Stat;
  stat(filename, &Stat);
#endif

  result = allocate_buffer(Stat.st_size);
  if (result.data) {
    if (fread(result.data, result.size, 1, file) != 1) {
      fprintf(stderr, "ERROR: Unable to read \"%s\".\n", filename);
      free_buffer(&result);
    }

  fclose(file);
  } else {
    fprintf(stderr, "ERROR: Unable to open \"%s\".\n", filename);
  }
  return result;
}

static Buffer* split_on(Buffer* buffer, char delimiter, size_t* count) {
  size_t n_lines = 1;
  for (size_t i = 0; i < buffer->size; i++) {
    if (buffer->data[i] == '\n')
      n_lines++;
  }

  // An array of Buffers
  Buffer* lines = malloc(sizeof(Buffer) * n_lines);
  if (!lines) {
    fprintf(stderr, "ERROR: Unable to allocate memory for lines.'\n");
    *count = 0;
  }

  size_t pos = 0;
  size_t lineidx = 0;

  for (size_t i = 0; i < buffer->size; i++) {
    if (buffer->data[i] == delimiter || i == buffer->size - 1) {
      size_t lsize = i - pos;
      if (i == buffer->size - 1 && buffer->data[i] != delimiter) {
        lsize++;
      }
      lines[lineidx] = allocate_buffer(lsize);
      memcpy(lines[lineidx].data, buffer->data + pos, lsize);
      pos = i + 1;
      lineidx++;
    }
  }
  *count = n_lines;
  return lines;
}

static void free_buffers(Buffer* buffers, size_t count) {
  for (size_t i = 0; i < count; i++)
    free_buffer(&buffers[i]);
}


