#ifndef MAIN_H
#define MAIN_H

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <fcntl.h>
#include <errno.h>

#define BUFFER_SIZE 1024
#define FLUSH_BUF -1

/* for chaining COMMANDS*/
#define _NORM	0
#define _OR		1
#define _AND	2
#define _CHAIN	3

extern char **environ;
/* number conversion */
#define TO_LOWERCASE	1
#define TO_UNSIGNED	2

/* switch using system getline() function */
#define WITH_GETLINE 0
#define WITH_STRTOK 0

#define HISTORY	".simple_shell_history"
#define HISTORY_MAX_LEN	4096




/**
 * struct string_list - singly linked list
 * @num: the number field
 * @str: is an input string
 * @next: points to the next node
 */
typedef struct string_list
{
	int num;
	char *str;
	struct string_list *next;
} list_t;

/**
 *struct info_perser - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_counter: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct info_perser
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_counter;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int onchanged_env;
	int status;
	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfdes;
	int historycounter;
} info_t;

#define INPUT_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_list;


/* looper.c */
int shell(info_t *, char **);
int check_for_builtin(info_t *);
void check_cmd(info_t *);
void custom_fork(info_t *);

/* cmd_parse.c */
int if_iscmd(info_t *, char *);
char *chr_dup(char *, int, int);
char *check_path(info_t *, char *, char *);

/* handle_errors.c */
void puts_err(char *);
int putchar_err(char);
int put_fdesc(char ch, int desc);
int puts_file_desc(char *str, int desc);

/* str_funct.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *begins_with(const char *, const char *);
char *_strcat(char *, char *);

/* str_funct1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* exits_shell.c */
char *_strchr(char *, char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);


/* split_args.c */
char **_strtok(char *, char *);
char **_strtok2(char *, char);

/* _realloc.c */
char *set_mem(char *, char, unsigned int);
void free_mem(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* free_mem.c */
int custom_free(void **);

/* custom_atoi.c */
int is_interactive(info_t *);
int if_delim(char, char *);
int check_alpha(int);
int custom_atoi(char *);

/* handle_error1.c */
int atoi_error(char *);
void print_er(info_t *, char *);
int print_decimal(int, int);
char *str_to_digit(long int, int, int);
void handle_comments(char *);

/* builtin_cmd.c */
int exit_shell(info_t *);
int btn_cd(info_t *);
int btn_help(info_t *);

/* builtin_cmd1.c */
int btn_history(info_t *);
int btn_alias(info_t *);

/*_getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* _getinput.c */
void clear_input(info_t *);
void set_input(info_t *, char **);
void free_input(info_t *, int);

/* environment.c */
char *_getenv(info_t *, const char *);
int custom_env(info_t *);
int _createnv(info_t *);
int _removeenv(info_t *);
int display_env_list(info_t *);

/* _getenv.c */
char **get_environment(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* _history.c */
char *get_hist_file(info_t *info);
int print_hist(info_t *info);
int read_hist(info_t *info);
int create_history_list(info_t *info, char *buf, int linecount);
int update_history_num(info_t *info);

/* cmd_lists.c */
list_t *add_to_node(list_t **, const char *, int);
list_t *add_to_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int remove_node_at_index(list_t **, unsigned int);
void free_list_node(list_t **);

/* cmd_lists1.c */
size_t len_of_list(const list_t *);
char **convert_list_to_str(list_t *);
size_t print_list(const list_t *);
list_t *node_begins_with(list_t *, char *, char);
ssize_t get_index_of_node(list_t *, list_t *);

/* vars_args.c */
int if_chain(info_t *, char *, size_t *);
void check_is_chain(info_t *, char *, size_t *, size_t, size_t);
int update_alias(info_t *);
int update_vars(info_t *);
int update_string(char **, char *);

/**
ssize_t custom_getline(char **lineptr, size_t *n);
char *check_line(int hasInput, char *line, int lineLength);
char *_getline();
int exit_shell(char **args);
char **split_arg(char *str,  char *delim);
void _execve(char **args);
int check_path(char **args);
void _printenv(char **args);
int compare_string(char *str1, char *str2);
char *_strdup(char *str);
char *_strtok(char *str, const char *delim);
size_t _strlen(const char *str);
*/
#endif
