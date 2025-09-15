#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024
#define MAX_ARGS 100

void chomp(char *s) {
  s[strcspn(s, "\n")] = '\0';
}

void tokenize(char *s, char *argv[]) {
  int i = 0;
  char *p;
  p = strtok(s, " ");
  while(p != NULL && i < MAX_ARGS - 1) {
    argv[i] = p;
    p = strtok(NULL, " ");
    i++;
  }
  argv[i] = NULL;
}

void echo(char *argv[]) {
  int i = 1;

  if (argv[1] == NULL) {
    printf("command 'echo' expects at least (1) argument(s)\n");
    return;
  }

  while(argv[i] != NULL) {
      printf("%s", argv[i]);
      if(argv[i + 1] != NULL)
          printf(" ");
      i++;
  }
  printf("\n");
}

void command(char *argv[]) {
  char *com = argv[0];
  
  if(!strcmp(com, "exit")) 
    exit(0);
  else if(!strcmp(com, "echo"))
    echo(argv);

  else
    printf("%s: command not found\n", com);
}

int repl() {
  printf("$ ");
  char input[MAX_LINE];
  fgets(input, MAX_LINE, stdin);

  if (input[0] == '\n') return 0;

  chomp(input);

  char *argv[MAX_ARGS];
  tokenize(input, argv);
  /*
  STRUCTURE:
  args[0] contains the command name
  args[1,2,3....] will contain the arguments 
  at the respective positions 1, 2, 3...
  */

  command(argv);
  return 0;
}
int main() {
  setbuf(stdout, NULL);
  printf("\e[1;1H\e[2J"); // clear terminal
  printf("C sells C shells - A (bad) shell written in C\n\n");

  while (1) {
    repl();
  }
}
