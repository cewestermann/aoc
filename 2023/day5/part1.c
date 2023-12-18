#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/stat.h>

typedef uint8_t u8;
typedef uint32_t u32;
typedef uint64_t u64;

typedef struct {
  u64 destination_start;
  u64 source_start;
  u64 range;
} MapEntry;

typedef struct {
  MapEntry* entries;
  u32 len;
} Map;

typedef struct {
  size_t size;
  u8* data;
} Buffer;

static Buffer allocate_buffer(size_t size);
static void free_buffer(Buffer* buffer);
static Buffer read_entire_file(char* filename);

int main(int argc, char** argv) {
  Buffer input = read_entire_file("input.txt");

  printf("%s\n", input.data);

  return EXIT_SUCCESS;
}

static Buffer allocate_buffer(size_t size) {
  Buffer result = {0};
  result.data = malloc(size);
  if (result.data)
    result.size = size;
  else
   fprintf(stderr, "ERROR: Tried to allocate %zu bytes.\n", size);
  return result;
}

static void free_buffer(Buffer* buffer) {
  if (buffer->data)
    free(buffer->data);
  buffer->data = 0;
  buffer->size = 0;
}

static Buffer read_entire_file(char* filename) {
  Buffer result = {0};

  FILE* file = fopen(filename, "r");

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

