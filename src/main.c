#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 1024
#define MAX_ARGS 100

typedef struct
{
  const char *name;
  const char *description;
} CommandInfo;

CommandInfo commandList[] = {
    {"echo", "echo <input> : echo command"},
    {"clear", "clear : clear terminal"},
    {"bin", "bin <input> : converts input to binary"},
    {"ascii", "ascii <input> : converts binary input to ascii"},
    {"exit", "exit : exit the shell"},
    {"help", "help : show available commands"},
    {"help", "help <command> : show detail about given command"},
};

const char *getCommandDescription(const char *name)
{
  int n = sizeof(commandList) / sizeof(CommandInfo);
  for (int i = 0; i < n; i++)
  {
    if (strcmp(commandList[i].name, name) == 0)
    {
      return commandList[i].description;
    }
  }
  return NULL;
}

void chomp(char *s)
{
  s[strcspn(s, "\n")] = '\0';
}

void tokenize(char *s, char *argv[])
{
  int i = 0;
  char *p;
  p = strtok(s, " ");
  while (p != NULL && i < MAX_ARGS - 1)
  {
    argv[i] = p;
    p = strtok(NULL, " ");
    i++;
  }
  argv[i] = NULL;
}

void echo(char *argv[])
{
  int i = 1;

  if (argv[1] == NULL)
  {
    printf("command 'echo' expects at least (1) argument(s)\n");
    return;
  }

  while (argv[i] != NULL)
  {
    printf("%s", argv[i]);
    if (argv[i + 1] != NULL)
      printf(" ");
    i++;
  }
  printf("\n");
}

void fromBinary(char *argv[])
{
  for (int i = 1; argv[i] != NULL; i++)
  {
    int result = 0;
    for (int j = 0; argv[i][j] != '\0'; j++)
    {
      result <<= 1;
      if (argv[i][j] == '1')
        result |= 1;
    }
    printf("%c", result);
  }
  printf("\n");
}

void printBinary(unsigned char c)
{
  for (int i = 7; i >= 0; i--)
  {
    printf("%d", (c >> i) & 1);
  }
}

void toBinary(char *argv[])
{
  int i = 1;
  while (argv[i] != NULL)
  {
    char *input = argv[i];
    for (int j = 0; input[j] != '\0'; j++)
    {
      printBinary((unsigned char)input[j]);
      if (input[j + 1] != '\0')
        printf(" ");
    }
    if (argv[i + 1] != NULL)
    {
      // spaces
      printf(" 00100000 ");
    }
    i++;
  }
  printf("\n");
}

void printHelpSection()
{
  printf("available commands:\n");
  int n = sizeof(commandList) / sizeof(CommandInfo);
  for (int i = 0; i < n; i++)
  {
    printf("%s\n", commandList[i].description);
  }
}

void help(char *argv[])
{
  if (argv[1] == NULL)
  {
    printHelpSection();
    printf("\n");
    return;
  }
  else
  {
    printf("%s\n", getCommandDescription(argv[1]));
  }
}

void command(char *argv[])
{
  char *com = argv[0];

  if (!strcmp(com, "exit"))
    exit(0);
  else if (!strcmp(com, "echo"))
    echo(argv);
  else if (!strcmp(com, "clear"))
    printf("\e[1;1H\e[2J");
  else if (!strcmp(com, "bin"))
    toBinary(argv);
  else if (!strcmp(com, "ascii"))
    fromBinary(argv);
  else if (!strcmp(com, "help"))
    help(argv);
  else
    printf("%s: command not found\n", com);
}

int repl()
{
  printf("$ ");
  char input[MAX_LINE];
  fgets(input, MAX_LINE, stdin);

  if (input[0] == '\n')
    return 0;

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

int main()
{
  setbuf(stdout, NULL);
  printf("\e[1;1H\e[2J"); // clear terminal
  printf("C sells C shells - A (bad) shell written in C\n\n");

  while (1)
  {
    repl();
  }
}
