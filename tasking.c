#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "tasking.h"
#include "fileio.h"
#include "util.h"


int
main(int argc, char** argv)
{
  printf(" **********************\n\
 * Welcome to Tasking *\n\
 *                    *\n\
 *      (c) 2019      *\n\
 * Patrick Guenthard  *\n\
 *                    *\n\
 *      h = help      *\n\
 *    l = license     *\n\
 **********************\n\n");

  task_list list;
  if(argc > 1) {
    list = load_task_list(argv[1]);
  } else {
    list = load_task_list(NULL);
  }
  
  printf("Loaded %i tasks\nHighest ID is %i\n\n", list.task_count, list.highest_id);

  bool loop = true;

  char* input = malloc(128 * sizeof(char));
  
  while(loop) {
    printf("> ");
    scanf("%s", input);
    if(is_command(input, "x", "exit")) {
      loop = false;
      if(argc > 1) {
	write_task_list(argv[1], list);
      } else {
	write_task_list(NULL, list);
      }
    } else if(is_command(input, "l", "license")) {
      print_license();
    } else if(is_command(input, "h", "help")) {
      print_help();
    } else if(is_command(input, "v", "view")) {
      printf("List...\na | all\nn | new \np | progress\nd | done\n> ");
      scanf("%s", input);
      if(is_command(input, "a", "all")) {
	print_task_list(list,true);
      } else if(is_command(input, "n", "new")) {
	print_task_list(filter_list_by_state(list, new), false);
      } else if(is_command(input, "p", "progress")) {
	print_task_list(filter_list_by_state(list, in_progress), false);
      } else if(is_command(input, "d", "done")) {
	print_task_list(filter_list_by_state(list, done), false);
      }
    } else if(is_command(input, "c", "create")) {
      char title[TITLE_SIZE], description[DESCRIPTION_SIZE];
      printf("Title: ");
      getchar();
      scanf("%[^\n]s", title);
      getchar();
      printf("Description: ");
      scanf("%[^\n]s", description);
      getchar();
      int id = ++list.highest_id;
      add_task_to_list(&list, create_task(id, title, description, new));
    } else if(is_command(input, "d", "delete")) {
      int del_id;
      printf("Delete task with following id: ");
      scanf("%d", &del_id);
      delete_task_from_list(&list, del_id);
    } else if(is_command(input, "m", "modify")) {
      int mod_id, new_state, index;
      printf("Change state of task with following id: ");
      scanf("%d", &mod_id);
      printf("1 New\n2 In Progress\n3 Done\n> ");
      scanf("%d", &new_state);
      for(index = 0; index < list.task_count; index++) {
	if(list.task[index].id == mod_id && new_state >= 1 && new_state <= 3) {
	  list.task[index].state = new_state - 1;
	}
      }
    }
  }
  
  return 0;
}


task_list
load_task_list(char *path)
{
   if(path == NULL) {
    path = malloc(128 * sizeof(char));
    sprintf(path, "%s/%s", getenv("HOME"), TASK_PATH);
  }
  task_list list = {NULL, 0, 0};

  char* file_text = read_file(path);

  char *line, *word, *brkt, *brkt2;
  const char *linesep = "\n", *wordsep = ":";

  for(line = strtok_r(file_text, linesep, &brkt); line; line = strtok_r(NULL, linesep, &brkt)) {
    int id;
    char title[TITLE_SIZE];
    char description[DESCRIPTION_SIZE];
    task_state state;
    
    word = strtok_r(line, wordsep, &brkt2);
    id = atoi(word);

    word = strtok_r(NULL, wordsep, &brkt2);
    strcpy(title, word);

    word = strtok_r(NULL, wordsep, &brkt2);
    strcpy(description, word);

    word = strtok_r(NULL, wordsep, &brkt2);
    state = atoi(word);

    add_task_to_list(&list, create_task(id, title, description, state));


  }

  return list;
}

int
write_task_list(char* path, task_list list)
{
  if(path == NULL) {
    path = malloc(128 * sizeof(char));
    sprintf(path, "%s/%s", getenv("HOME"), TASK_PATH);
  }
  
  int index;
  char* output_text = malloc(sizeof(char) * list.task_count * (1 + TITLE_SIZE + DESCRIPTION_SIZE + 1));
  strcpy(output_text, "");
  for(index = 0; index < list.task_count; index++) {
    sprintf(output_text,
	    "%s\n%i:%s:%s:%i",
	    output_text,
	    list.task[index].id,
	    list.task[index].title,
	    list.task[index].description,
	    list.task[index].state);
  }

  write_text_file(path, output_text);
  
  free(output_text);
  return 0;
}

task
create_task(int id, char title[TITLE_SIZE], char description[DESCRIPTION_SIZE], task_state state)
{
  task *newtask = malloc(sizeof(task));
  newtask->id = id;
  strcpy(newtask->title, title);
  strcpy(newtask->description, description);
  newtask->state = state;
  return *newtask;
}

void
add_task_to_list(task_list* list, task newtask)
{
  list->task = realloc(list->task, sizeof(task) * (list->task_count + 1));
  list->task[list->task_count] = newtask;
  list->task_count++;
  if(newtask.id > list->highest_id)
    list->highest_id = newtask.id;
}

void
delete_task_from_list(task_list* list, int id) {
  int index;
  task_list new_list = {NULL,0,0};
  for(index = 0; index < list->task_count; index++) {
    if(list->task[index].id != id)
      add_task_to_list(&new_list, list->task[index]);
  }
  *list = new_list;
}

task_list
filter_list_by_state(task_list list, task_state state)
{
  task_list filtered_list = {NULL,0,0};
  int index;
  for(index = 0; index < list.task_count; index++) {
    if(list.task[index].state == state)
      add_task_to_list(&filtered_list, list.task[index]);
  }

  return filtered_list;
}


void print_task(task tsk, bool prnt_state) {
  int index = 0;
  char spaces[10] = "|   ";

  for(index = 0; index < floor(log10(tsk.id)); index++) {
    sprintf(spaces, "%s ", spaces);
  }
  
  printf("\n(%i) %s\n\n%s%s\n", tsk.id, tsk.title, spaces, tsk.description);
  if(prnt_state) {
    switch(tsk.state) {
    case new:
      printf("\n%sState: New\n", spaces); break;
    case in_progress:
      printf("\n%sState: In Progress\n", spaces); break;
    case done:
      printf("\n%sState: Done\n", spaces); break;
    }
  }
}

void
print_task_list(task_list list, bool prnt_state)
{
  int index;
  for(index = 0; index < list.task_count; index++) {
    print_task(list.task[index], prnt_state);
    if(index != list.task_count -1) {
      printf("\n--------------------------------\n");
    }
    else {
      printf("\n");
    }
  }
}
