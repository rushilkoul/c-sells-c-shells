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

int repl() {
  printf("$ ");
  char input[100];
  fgets(input, 100, stdin);

  if (strlen(input) == 0) return 0;

  chomp(input);

  char *argv[MAX_ARGS];

  tokenize(input, argv);

  printf("ARGS TEST:\n");
  int test = 0;

  while(argv[test] != NULL) {
    printf("(%d): %s\n", test, argv[test]);
    test++;
  }

  printf("%s: command not found\n", input);
  return 0;
}
int main() {
  setbuf(stdout, NULL);
  printf("\e[1;1H\e[2J"); // clear terminal

  while (1) {
    repl();
  }
}
