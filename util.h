#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>

void
print_help();

void
print_license();

bool is_command(char* input, char *command1, char *command2);

#endif
