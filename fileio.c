#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

char *read_file(char *filename) {
  FILE *f = fopen(filename, "rt");
  assert(f);
  fseek(f, 0, SEEK_END);
  long length = ftell(f);
  fseek(f, 0, SEEK_SET);
  char *buffer = (char *) malloc(length + 1);
  buffer[length] = '\0';
  fread(buffer, 1, length, f);
  fclose(f);
  return buffer;
}


int write_text_file(char *filename, char*text) {
  FILE *f = fopen(filename, "w");
  assert(f);
  int len = fwrite(text, sizeof(char), strlen(text) + 1, f);
  fclose(f);
  return len;
}
