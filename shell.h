/* variables*/
#ifndef SHELL_H
#define SHELL_H

/* included libraries ( include guarded) */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* variables for reading and writing buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* variables for command chains */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* variables for converting numbers */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* variables 1 if using system getline */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096


/* environment variables*/
extern char **environ;


/**
* struct liststr - singly linked list
* @num: the number field
* @str: a string
* @next: points to the next node
*/

typedef struct liststr

{
int num;
char *str;
struct liststr *next;
} list_t;

/**
*struct passinfo - contains pseudo-arguements to pass into a function,
*					allowing uniform prototype for function pointer struct
*@arg: a string generated from getline containing arguements
*@argv: an array of strings generated from arg
*@path: a string path for the current command
*@argc: the argument count
*@line_count: the error count
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

typedef struct passinfo
{
char *arg;
char **argv;
char *path;
int argc;
unsigned int line_count;
int err_num;
int linecount_flag;
char *fname;
list_t *env;
list_t *history;
list_t *alias;
char **environ;
int env_changed;
int status;

char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
int cmd_buf_type; /* CMD_type ||, &&, ; */
int readfd;
int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
0, 0, 0}

/**
*struct builtin - this contains builtin strings and the related functions
*@type: the builtin command flag
*@func: the s
*/

typedef struct builtin

{
char *type;
int (*func)(info_t *);
} builtin_table;

/* All the files used in the program, are commented here,
* with all their variables 
*/

/* file_name hsh.c */
int hsh(info_t *, char **);
int find_built_in(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* file_name path.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* file_name loop_hsh.c */
int loop_hsh(char **);

/* file_name err_string_functions.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* file_name string_functions.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* file_name string_functions2.c */
char *_str_cpy(char *, char *);
char *_str_dup(const char *);
void _puts(char *);
int _putchar(char);

/* file_name string_functions3.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* file_name string_functions4.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* file_name memory_functions */
char *_mem_set(char *, char, unsigned int);
void f_free(char **);
void *_re_alloc(void *, unsigned int, unsigned int);

/* file_name memory_functions2.c */
int b_free(void **);

/* file_name more_functions.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* file_name more_functions2.c */
int _conv_str_int(char *);
void print_error(info_t *, char *);
int print_decimal(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* file_name builtin_emulators.c */
int _my_exit(info_t *);
int _my_cd(info_t *);
int _my_help(info_t *);

/* file_name builtin_emulators2.c */
int _my_history(info_t *);
int _my_alias(info_t *);

/* getline.c module */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* file_name info.c module */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* file_name env.c module */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* file_name env2.c module */
char **get_env(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* file_name file_io_functions.c */
char *get_history_files(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* file_name liststr.c module */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* file_name liststr2.c module */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* file_name chain.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
