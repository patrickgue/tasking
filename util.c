#include "util.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

void print_license()
{
  printf("Copyright (c) 2019, Patrick Guenthard\n\
All rights reserved.\n\
\n\
Redistribution and use in source and binary forms, with or without\n\
modification, are permitted provided that the following conditions are met:\n\
\n\
1. Redistributions of source code must retain the above copyright notice, this\n\
   list of conditions and the following disclaimer.\n\
2. Redistributions in binary form must reproduce the above copyright notice,\n\
   this list of conditions and the following disclaimer in the documentation\n\
   and/or other materials provided with the distribution.\n\
\n\
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \"AS IS\" AND\n\
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED\n\
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE\n\
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR\n\
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES\n\
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;\n\
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND\n\
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT\n\
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS\n\
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.\n\
\n\
The views and conclusions contained in the software and documentation are those\n\
of the authors and should not be interpreted as representing official policies,\n\
either expressed or implied, of the \"tasking\" project.\n\n");
}


void
print_help()
{
  printf("\n\
Tasking Help\n\
------------\n\n\
\n\
v | view        View exiting task\n\
c | create      Create new task\n\
m | modify      Modify state of existing task\n\
d | delete      Delete exiting task\n\
\n\
h | help        Show this help\n\
l | license     Show license of \"tasking\"\n\
\n\
x | exit        exit \"tasking\"\n\n");
}


bool
is_command(char* input, char *command1, char *command2) {
  return strcmp(input, command1) == 0 || strcmp(input, command2) == 0;
}
