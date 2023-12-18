#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdint.h>
#include <assert.h>
#include <sys/stat.h>
#include <sys/types.h>

#define ERROR_ALLOCATE(msg) fprintf(stderr, "ERROR: Unable to allocate %s.\n", msg)

typedef uint8_t u8;
typedef uint64_t u64;

typedef struct {
  size_t size;
  u8* data;
} Buffer;

typedef Buffer Cards;

static Buffer read_entire_file(char* filename);
static Buffer* split_on(Buffer* buffer, char delimiter, size_t *count);
static void free_buffers(Buffer* buffers, size_t count);

static int get_wins(Buffer card);
static u64 process_cards(Buffer* cards);
static u64 process_cards2(Buffer* cards, u64 n_cards);

int main(int argc, char** argv) {
  Buffer buffer = read_entire_file("input.txt");

  size_t count = 0;
  Buffer* buffers = split_on(&buffer, '\n', &count);

  int wins = get_wins(buffers[0]);

  printf("Wins: %d\n", wins);

  return EXIT_SUCCESS;
}

static u64 process_cards(Buffer* cards) {
  /* The number of original cards */
  u64 n_cards = (u64)cards->size;
  assert(n_cards > 0);
  for (size_t i = 0; i < cards->size; i++) {
  }
}

static u64 process_cards2(Buffer* cards, u64 n_cards) {
  if (!n_cards) return 0;

}

static int get_wins(Buffer card) {
  size_t lc = 0;
  Buffer* linebuffers = split_on(&card, '|', &lc);
  u8* winning_numbers = linebuffers[1].data;

  size_t cc = 0;
  Buffer* left = split_on(&linebuffers[0], ':', &cc);
  u8* hand = left[1].data;

  int win_array[25];
  int hand_array[10];

  sscanf((char*)winning_numbers, 
      "%d %d %d %d %d "
      "%d %d %d %d %d "
      "%d %d %d %d %d "
      "%d %d %d %d %d "
      "%d %d %d %d %d",

      &win_array[0], &win_array[1], &win_array[2], &win_array[3], &win_array[4],
      &win_array[5], &win_array[6], &win_array[7], &win_array[8], &win_array[9],
      &win_array[10], &win_array[11], &win_array[12], &win_array[13], &win_array[14],
      &win_array[15], &win_array[16], &win_array[17], &win_array[18], &win_array[19],
      &win_array[20], &win_array[21], &win_array[22], &win_array[23], &win_array[24]);

  sscanf((char*)hand, "%d %d %d %d %d %d %d %d %d %d",
      &hand_array[0], &hand_array[1], &hand_array[2], &hand_array[3], &hand_array[4],
      &hand_array[5], &hand_array[6], &hand_array[7], &hand_array[8], &hand_array[9]);

  int wins = 0;

  for (size_t i = 0; i < 10; i++)
    for (size_t j = 0; j < 25; j++)
      if (hand_array[i] == win_array[j])
        wins += 1;

  return wins;
}

static Buffer allocate_buffer(size_t size) {
  Buffer result = {0};
  result.data = malloc(size);
  if (result.data)
    result.size = size;
  else
    ERROR_ALLOCATE("%zu bytes");
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


