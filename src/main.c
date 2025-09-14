#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

void chomp(char *s) {
    s[strcspn(s, "\n")] = '\0';
}

int repl() {
    printf("$ ");
    char input[100];
    fgets(input, 100, stdin);
    chomp(input);
    
    if (strcmp(input, "exit") == 0) exit(0);

    printf("%s: command not found\n", input);
    return 0;
}
int main() {
  setbuf(stdout, NULL); 
  
  while (1) {
    repl();
  }
}
