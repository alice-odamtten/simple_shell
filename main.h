#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>

/* forking child process libs */
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <limits.h>
/*stat */
#include <sys/stat.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGUMENTS 128


/**
 * struct node - node for list data structure
 * @data: value for node
 * @sub_data: any other extra data available
 * @next: pointer to next node
 */
typedef struct node
{
	char *data;
	char *sub_data;
	struct node *next;
} l_node;

/**
 * struct global_data - holds globals variables
 * @file_name: name of program file
 * @command: holds input from cli
 * @arguments: tokens from inputs
 * @alias_db: list for aliases
 * @number_of_args: number of tokens
 * @s_arg: hold tokens for inputs with semi colon
 * @counter: a program  counter
 * @file: file inputs
 * @readfd: file descriptors
 * @argc: number of inputs from cli
 * @status: checks the status of cmd
 * @env_db: handles envs of the program
 * Description: global data structure for variables
 */
typedef struct global_data
{
	char *file_name;
	char *command;
	char *arguments[MAX_ARGUMENTS];
	l_node *alias_db;
	int number_of_args;
	char *s_arg[MAX_ARGUMENTS];
	int counter;
	char *file;
	int readfd;
	int argc;
	int status;
	char **env_db;
} g_data;

/**
 * struct builtins - holds list of builtins
 * @name: name of builtin function
 * @handler: function pointer
 */
typedef struct builtins
{
	char *name;
	int (*handler)(g_data *);
} csh_builtin;

/* environ */
extern char **environ;

/* parser.c */
void parse_command(g_data *info);
/*char* find_command_path(const char *command);*/

int is_cmd(char *path);
void cmd_handler(g_data *info, int c);

/* env */
char *_getenv(const char *name, char **_environ);


/* builtins */
int exit_func(g_data *info);
int cd_func(g_data *info);
int alias_func(g_data *info);
int help_func(g_data *info);
int unalias_func(g_data *info);
int builtin_setenv(char *a, char *e);

/* misc.d */
void init_g_data(g_data *info, char **av, int c);
void free_all(g_data *);
ssize_t is_shell_interactive(void);
int parseline(const char *cmdline, char **argv);
int process_commands(g_data *info);
void semi_colon_hanler(char *input, char *tokens, char **fcommand);
void process_interactive_commands(g_data *info);
int find_and_exec_cmd(g_data *info);
int _strncmp(const char *s, const char *t, size_t len);

/*  string helpers */
int _strlen(char *s);
void _memcpy(void *dest, const void *src, unsigned int n);
char *sanitize_string(char *str);
char *sanitize_string2(char *str);
char *surround_with_quotes(char *str);
int contains_quotes(const char *str);

/* aliases.c */
int set_alias(g_data *info);
int is_valid_alias(g_data *info, char *s);
l_node *find_alias(l_node *info, char *idx);
void perform_alias_insert(g_data *info, char **data, char **sd);
void process_alias(g_data *info, char ***k, int *excess_count);
int token_copier(g_data *info, char **token, int *i);

/* add_node.c */
void insert_at_end(l_node **head, char *str, char *sub_data);

/* linkedlist.c */
void print_list(struct node *head);
void freeList(l_node **head);

/*  _puts(char *e);*/
void _puts(const char *s);
void _putchar(char c);
void _eputchar(char c);
void _eputs(const char *s);
void _print_one_line(const char *s);

/* parser.c */
char *find_command_path(const char *command);

/* main */
char *sh_read_line(g_data *info);
int path_finder(g_data *info);
ssize_t handle_builtins(g_data *info);

/* setenv */
int _envp(__attribute__((unused)) g_data *info);
int setenv_func(g_data *info);
int unsetenv_func(g_data *info);

/* strings_helper_ext.c */
int _strcmp(const char *s, const char *t);
char *_strcpy(char *dest, char *src);
char *_strdup(char *s);
int _strlen(char *s);
char *_strncat(char *t, const char *s, int n);
char *_strcat(char *dest, const char *src);
char *_strcat(char *dest, const char *src);

/* error_handler.c */
char *env_err(g_data *info);
int error_handler(g_data *info, int err_val);
char *atoi_rev(int n);
int get_len(int n);
char *path_126_err(g_data *info);
char *not_found_err(g_data *info);
char *get_cd_error(g_data *info);
char *exit_shell_err(g_data *info);
char *strcat_cd(g_data *info, char *msg, char *error, char *ver_str);

/* alias extended */
void print_alias(l_node *tmp);
void file_error(g_data *info);

/* strtok.c */
char *_strpbrk(const char *str, const char *set);
char *_sttrtok(char *p, const char *delim);
int _getline(char **line, size_t *len, int fd);

/* error_ext.c */
int process_file_commands(g_data *info, int fd);
void _eprint_one_line(const char *s);

/* string_helpers_aux.c */
char *_strcspn(char *str);
int _atoi(const char *src);
char *_strchr(const char *r, char c);
char *_strncpy(char *dest, char *src, int n);

char *handle_eof(char *buff, size_t b, size_t *br, int fd, size_t *);
int process_non_interactive_commands(g_data *info);
void rem_trail_spaces(char *str);
void *_realloc(void *ptr, size_t os, size_t nsize);

char *command_failure_err(g_data *info);
void print_exit_err(g_data *info);
void write_digits(size_t number);


void cd_dot(g_data *datash);
void cd_to(g_data *datash);
void cd_previous(g_data *datash);
void cd_to_home(g_data *datash);
void rev_string(char *s);

void set_env(char *name, char *value, g_data *info);
char *copy_info(char *name, char *value);
int _setenv(g_data *info);
int _unsetenv(g_data *info);

int is_executable(g_data *info);
int check_err_cmd(char *dir, g_data *info);

#endif
