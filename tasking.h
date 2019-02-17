#ifndef TASKING_H
#define TASKING_H

#define TASK_PATH ".tasks"

typedef enum e_task_state {
			   new = 0,
			   in_progress = 1,
			   done = 2
} task_state;

typedef struct s_task {
  int id;
  char title[64];
  char description[256];
  task_state state;
} task;

typedef struct s_task_list {
  task* task;
  int task_count;
  int highest_id;
} task_list;

task
create_task(int id, char title[64], char description[256], task_state state);

void
add_task_to_list(task_list* list, task newtask);

void
delete_task_from_list(task_list* list, int id);

task_list
load_task_list();

int
write_task_list(char*,task_list);

task_list
filter_list_by_state(task_list, task_state);

void
print_task(task,bool);

void
print_task_list(task_list,bool);


#endif
