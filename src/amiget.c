#include <stdio.h>
#include <stdlib.h>

int wget(char *url) {
  char command[1024];
  int ret;

  sprintf(command, "wget -q -O ram:lol %s", url);
  // avoid popup request for inserting united_states.country: drive
  system("assign united_states.country: ram:");
  ret = system(command);
  system("assign united_states.country: dismount");

  if (ret) {
    printf("You need wget in your path, for instance in C:.\n");
  }

  return ret;
}

int main(int argc, char **argv) {
  wget("repo.amiget.org");
  return 0;
}

