#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "agogo.h"
#include "task.h"
#include "clock.h"

void add_task(char *task_name);
void remove_task(char *task_name);
int task_exists(char *task_name);
void log_time(char *task_name, char *time_spent);

int agogo_task(int argc, char *argv[])
{
  if (argc < 3) {
    list_tasks();
    return EXIT_SUCCESS;
  }

  char *sub_command = argv[2];

  // Create a new task; arg is the task name
  if ((strcmp(sub_command, "--add") == 0) || (strcmp(sub_command, "-a") == 0)) {
    if (argc < 4) {
      printf("Error: Missing task name\n");
      return EXIT_FAILURE;
    }
    add_task(argv[3]);
  }

  // Remove the task; arg is the task name
  else if ((strcmp(sub_command, "--remove") == 0) || (strcmp(sub_command, "-r") == 0)) {
    if (argc < 4) {
      printf("Error: Missing task name\n");
      return EXIT_FAILURE;
    }
    remove_task(argv[3]);
  }

  // Log the time spent on the task; args are task name and time spent
  else if ((strcmp(sub_command, "--log") == 0) || (strcmp(sub_command, "-l") == 0)) {
    if (argc != 5) {
      printf("Error: Pattern is agogo task --log <task_name> <time_spent>\n");
      return EXIT_FAILURE;
    }

    log_time(argv[3], argv[4]);
  }

  // Set the given task as the current task; arg is the task name
  else if ((strcmp(sub_command, "--set") == 0) || (strcmp(sub_command, "-s") == 0)) {
    printf("Not implemented yet\n");
  }

  // Unset the given task as the current task; arg is the task name
  else if ((strcmp(sub_command, "--unset") == 0) || (strcmp(sub_command, "-u") == 0)) {
    printf("Not implemented yet\n");
  }

  // Get a random new task
  else if ((strcmp(sub_command, "--get") == 0) || (strcmp(sub_command, "-g") == 0)) {
    printf("Not implemented yet\n");
  }

  // Move the task to another project; args are task name and project name
  else if ((strcmp(sub_command, "--move") == 0) || (strcmp(sub_command, "-m") == 0)) {
    printf("Not implemented yet\n");
  }

  // Rename the task; args are task name and new task name
  else if ((strcmp(sub_command, "--rename") == 0) || (strcmp(sub_command, "-n") == 0)) {
    printf("Not implemented yet\n");
  }

  // Copy the task; args are the task name and project name
  else if ((strcmp(sub_command, "--copy") == 0) || (strcmp(sub_command, "-c") == 0)) {
    printf("Not implemented yet\n");
  }

  // Set the priority of the task; args are the task name and priority level
  else if ((strcmp(sub_command, "--priority") == 0) || (strcmp(sub_command, "-p") == 0)) {
    printf("Not implemented yet\n");
  }

  // Mark the task as done; arg is the task name
  else if ((strcmp(sub_command, "--done") == 0) || (strcmp(sub_command, "-d") == 0)) {
    printf("Not implemented yet\n");
  }

  else {
    printf("Error: Unknown subcommand %s\n for agogo-task\n", sub_command);
    return EXIT_FAILURE;
  }


  return EXIT_SUCCESS;
}


=======
  return EXIT_SUCCESS;
}

>>>>>>> 81fc04b1aded7f08dcd1c132f0443dddd617e22d
void list_tasks() 
{
  if (is_clocked_on() != 0) {
    printf("Error: Not currently clocked on to any project.\n");
    return;
  }

  int status = system("ls " AGOGO_DIR "/current");

  if (status != 0) {
    printf("Error: Could not list the tasks.\n");
    exit(EXIT_FAILURE);
  }
}


void add_task(char *task_name) 
{
  if (is_clocked_on() != 0) {
    printf("Error: Not currently clocked on to any project.\n");
    return;
  }
  printf("Adding task %s\n", task_name);

  char command[256];
  snprintf(command, sizeof(command), "touch " AGOGO_DIR "/current/%s", task_name);

  int status = system(command);
  if (status != 0) {
    printf("Error: Could not add the task %s.\n", task_name);
    exit(EXIT_FAILURE);
  }
}


void remove_task(char *task_name) 
{
  if (is_clocked_on() != 0) {
    printf("Error: Not currently clocked on to any project.\n");
    return;
  }
  printf("Removing task %s\n", task_name);
  char command[256];
  snprintf(command, sizeof(command), "rm " AGOGO_DIR "/current/%s", task_name);

  int status = system(command);
  if (status != 0) {
    printf("Error: Could not remove the task %s.\n", task_name);
    exit(EXIT_FAILURE);
  }
}


void log_time(char *task_name, char *time_spent)
{
  if (task_exists(task_name) != 0) {
    printf("Error: Task %s does not exist.\n", task_name);
    exit(EXIT_FAILURE);
  }

  char command[256];
  int num_minutes = parse_time(time_spent);

  printf("Logging %d minutes for task %s\n", num_minutes, task_name);
  snprintf(command, sizeof(command), "echo %d >> " AGOGO_DIR "/current/%s", num_minutes, task_name);

  int status = system(command);
  if (status != 0) {
    printf("Error: Could not log the time %s for task %s.\n", time_spent, task_name);
    exit(EXIT_FAILURE);
  }

}


int task_exists(char *task_name)
{
  if (is_clocked_on() != 0) {
    return EXIT_FAILURE;
  }

  char command[256];
  snprintf(command, sizeof(command), "test -f " AGOGO_DIR "/current/%s", task_name);

  int status = system(command);
  if (status != 0) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}


