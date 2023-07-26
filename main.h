#ifndef MAIN_H
#define MAIN_H

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int exit_shell(char **args);
char **split_arg(char *str,  char *delim);
void _execve(char **args);
int check_path(char **args);
void _printenv(char **args);
int compare_string(char *str1, char *str2);
char *_strdup(char *str);
char *_strtok(char *str, const char *delim);
size_t _strlen(const char *str);
#endif
