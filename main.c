#include "main.h"

/**
 * main - entry point
 * @c:  number of cli arguments
 * @av: an array of cli arguments
 * Return: 1
 */
int main(int c, char **av)
{
	g_data info;

	init_g_data(&info, av, c);
	cmd_handler(&info, c);

	return (1);
}

/**
 * sh_read_line - reads inputs from cli
 * @info: global data for state management
 * Return: input from the cli
 */
char *sh_read_line(__attribute((unused))  g_data *info)
{
	/**/
	/* char *line = NULL;*/
	/*size_t buflen = 0;*/
	/**/
	/*if (getline(&line, &buflen, stdin) == -1)*/
	/*{*/
	/*	exit(EXIT_FAILURE);*/
	/*}*/

	return (NULL);
}

/**
 * process_interactive_commands - for handling interactive cmds
 * @info: global data for state management
 * Return: nothing
 */
void process_interactive_commands(g_data *info)
{
	int ret = 1;
	/*char *ptr = NULL;*/
	size_t len = 0;
	int linelen;

	while (1)
	{
		if (is_shell_interactive())
		{
			write(STDOUT_FILENO, "$ ", 2);
			fflush(stdout);
		}
		linelen = getline(&(info->command), &len, stdin);
		fflush(stdin);
		if (linelen != -1)
		{
			rem_trail_spaces(info->command);
			/*_strcpy(info->command, ptr);*/

			_strcspn(info->command);
			if (_strlen(info->command) == 0)
			{
				ret++;
				continue;
			}
			ret = find_and_exec_cmd(info);

			info->counter += 1;
			/*free(ptr);*/
		}
		else
		{
			if (is_shell_interactive())
				_print_one_line("\n");
			free_all(info);
			exit(0);
		}
	}
}

/**
 * process_file_commands - process file inputs
 * @info: global data for state management
 * @fd: file descriptor for inputs
 * Return: 1 or 0
 */
int process_file_commands(g_data *info, int fd)
{
	char *line = NULL;
	size_t len = 0;

	info->readfd = fd;

	if (fd == -1)
	{
		_eprint_one_line(info->file_name);
		_eprint_one_line(": 0: Can't open ");
		_eprint_one_line(info->file);
		exit(127);

		return (EXIT_FAILURE);
	}

	while (_getline(&line, &len, fd))
	{
		_strcpy(info->command, line);
		_strcspn(info->command);
		find_and_exec_cmd(info);
	}

	close(fd);
	return (1);
}

/**
 * process_non_interactive_commands - handles non interactive cmds
 * @info: global data for state management
 * Return: 1 or 0
 */
int process_non_interactive_commands(g_data *info)
{
	int ret = 0;
	char *ptr = NULL;
	size_t line = 0;

	info->readfd = 0;

	if (getline(&ptr, &line, stdin) != -1)
	{
		fflush(stdin);
		rem_trail_spaces(ptr);
		_strcpy(info->command, ptr);
		_strcspn(info->command);
		ret = find_and_exec_cmd(info);
	}
	else
	{
		exit(EXIT_SUCCESS);
	}

	free(ptr);

	return (ret);
}

