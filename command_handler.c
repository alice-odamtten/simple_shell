#include "main.h"

/**
 * exec_cmd - handles comand exec
 * @info: globals for state management
 * @path: command path
 * Return: 1 or 0
 */
ssize_t exec_cmd(g_data *info, char *path)
{
	int status;
	const int pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execve(path, info->arguments, info->environ);
		perror(info->file_name);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (waitpid(pid, &status, WUNTRACED)  == -1)
		{
			perror("wait");
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			exit(EXIT_FAILURE);
		}
	}

	return (1);
}

/**
 * cmd_handler - handles input commnads
 * @info: globals and state managements
 * @c: number of command line arguments
 * Return: nothing
 */
void cmd_handler(g_data *info, int c)
{
	int fd = 0;

	if (c == 1)
	{
		process_interactive_commands(info);
	}
	else if (c == 2)
	{
		fd = open(info->file, O_RDONLY);
		process_file_commands(info, fd);
	}
	else
	{
		if (process_non_interactive_commands(info) == 0)
		{
			file_error(info);
			exit(EXIT_FAILURE);
		}
	}

	free_all(info);
}

/**
 * find_and_exec_cmd - finds and exec a command
 * @info: globals for state management
 * Return: 1 or 0
 */
int find_and_exec_cmd(g_data *info)
{
	int ret = 0;

	parse_command(info);
	ret = handle_builtins(info);
	if (ret == -1)
	{
		ret = path_finder(info);
	}
	return (ret);
}

/**
 * is_cmd - determines if a file is an executable command
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(char *path)
{
	struct stat st;

	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * path_finder - finds command paths
 * @info: globals for state managements
 * Return: 1 or 0
 */
int path_finder(g_data *info)
{
	int ret = 0;
	char *commandPath = find_command_path(info, info->command);

	if (commandPath != NULL)
	{
		ret = exec_cmd(info, commandPath);
		free(commandPath);
	}
	else
	{
		if (info->arguments[0])
		{
			if (info->arguments[0][0] == '/' && is_cmd(info->arguments[0]) == 1)
			{
				ret = exec_cmd(info, info->arguments[0]);
				free(commandPath);
			}
			else
			{
				/* check if is an alias and execute here */
				error_handler(info, 127);
				ret = 1;
			}
		}
	}
	return (ret);
}

