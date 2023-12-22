#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/stat.h>
#include <string.h>

typedef uint8_t u8;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int32_t i32;

typedef struct {
  size_t size;
  u8* data;
} Buffer;

typedef Buffer String;

typedef struct {
  size_t count;
  u8** tokens;
} TokenBuffer;

typedef struct {
  String destination_start;
  String source_start;
  String range;
} MapEntry;

typedef struct {
  MapEntry* entries;
  u32 len;
} Map;

static Buffer allocate_buffer(size_t size);
static void free_buffer(Buffer* buffer);
static Buffer read_entire_file(char* filename);
static Buffer* buffer_get_lines(Buffer* buffer);
static void buffer_print(Buffer* buffer);
static TokenBuffer tokenize(char* buffer, size_t maxlen, char* delim);
static void populate_map(Map* map, Buffer* linebuffers, int start_idx);

int main(int argc, char** argv) {
  Buffer input = read_entire_file("input.txt");

  //printf("%s\n", input.data);

  Buffer* line_buffers = buffer_get_lines(&input);

  char* delim = strchr((char*)line_buffers[0].data, ':');
  delim++;

  TokenBuffer seeds = tokenize(delim, 50, " ");
  printf("%zu\n", seeds.count);

  for (size_t i = 0; i < seeds.count; i++) {
    printf("%s\n", seeds.tokens[i]);
  }

  Map seeds2soil = {0};
  populate_map(&seeds2soil, line_buffers, 3);

  //buffer_print(line_buffers);

  for (size_t i = 0; i < line_buffers->size; i++) {
    free_buffer(&line_buffers[i]);
  }

  free_buffer(&input);

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

static Buffer* buffer_get_lines(Buffer* buffer) {
  u32 n_lines = 0; 

  for (size_t i = 0; i < buffer->size; i++) {
    if (buffer->data[i] == '\n')
      n_lines++;
  }

  Buffer* linebuffers = malloc(n_lines * sizeof(Buffer));

  size_t start = 0;
  size_t line_idx = 0;

  for (size_t i = 0; i < buffer->size; i++) {
    if (buffer->data[i] == '\n' || i == (buffer->size - 1)) {
      size_t linelength = i - start;
      linebuffers[line_idx] = allocate_buffer(linelength);

      memcpy(linebuffers[line_idx].data, &buffer->data[start], linelength);

      start = i + 1;
      line_idx++;
    }
  }
  return linebuffers;
}

static void buffer_print(Buffer* buffer) {
  for (size_t i = 0; i < buffer->size; i++) {
    printf("%s\n", buffer[i].data);
  }
}

static TokenBuffer tokenize(char* str, size_t maxlen, char* delim) {
  TokenBuffer tb = {0};
  u8** tokens = malloc(maxlen * sizeof(u8*));
  int count = 0;

  u8* token;
  
  token = (u8*)strtok((char*)str, delim);

  while (token != NULL) {
    tokens[count++] = token;
    token = (u8*)strtok(NULL, delim);
  }
  tb.count = count;
  tb.tokens = tokens;

  return tb;
}

static void populate_map(Map* map, Buffer* linebuffers, int start_idx) {
  size_t n_entries = 0;
  size_t end_point;
  for (size_t i = start_idx; i < linebuffers->size; i++) {
    if (linebuffers[i].data[0] == '\0') {
      end_point = i;
      break;
    }
    n_entries++;
  }

  MapEntry* entries = malloc(n_entries * sizeof(MapEntry));
  TokenBuffer tokens;

  for (size_t i = start_idx; i < end_point; i++) {
    tokens = tokenize(&linebuffers->data[i], 4, " ");
  }

  for (size_t i = 0; i < tokens.count; i++) {
    printf("%s\n", tokens.tokens[i]);
  }
}
