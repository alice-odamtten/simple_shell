#include "main.h"

/**
 * main - entry point
 * @c:  number of cli arguments
 * @av: an array of cli arguments
 * @env: environment variables
 * Return: 1
 */
int main(int c, char **av, char **env)
{
	g_data info;

	init_g_data(&info, av, env, c);
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
	char *ptr = NULL;
	size_t len = 0;
	int linelen;

	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2);
		fflush(stdout);

		/*ptr = sh_read_line(info);*/
		/*strcpy(info->command, ptr);*/
		linelen = getline(&ptr, &len, stdin);
		fflush(stdin);
		if (linelen != -1)
		{
			_strcpy(info->command, ptr);

			/*_strcspin(info->command);*/
			if (_strlen(info->command) == 0)
			{
				ret = 1;
				continue;
			}
			ret = find_and_exec_cmd(info);

			info->counter += 1;
			ret = 1;
		}
		else
		{
			ret = linelen;
			_print_one_line("\n");
			break;
		}
	}
	free(ptr);
	ret++;
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
		_strcpy(info->command, ptr);
		_strcspn(info->command);
		ret = find_and_exec_cmd(info);
	}


	free(ptr);

	return (ret);
}

