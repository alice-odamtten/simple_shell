#include "main.h"

/**
 * exec_cmd - handles comand exec
 * @info: globals for state management
 * @path: command path
 * Return: 1 or 0
 */
ssize_t exec_cmd(g_data *info, char *path)
{
	const int pid = fork();
	int status;

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(path, info->arguments, environ))
		{
			free_all(info);
		}
		perror(info->file_name);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (waitpid(pid, &(status), WUNTRACED)  == -1)
		{
			perror("wait");
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			info->status = 2;
			return (0);
		}
	}
	info->status = status / 256;
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
	FILE *fd;

	if (c == 1)
	{
		process_interactive_commands(info);
	}
	else if (c == 2)
	{
		fd = fopen(info->file, "r");
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
	if (ret == 0)
	{
		free_all(info);
		exit(info->status);
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
	int ret = 0, isexec;
	char *commandPath;

	isexec = is_executable(info);
	if (isexec == -1)
		return (1);
	/**
	* if (isexec == 0)
	*{
	*	commandPath = find_command_path(info->command);
	*	if (check_err_cmd(commandPath, info) == 1)
	*		return (1);
	*}
	*/
	commandPath = find_command_path(info->command);
	if (commandPath != NULL)
	{
		ret = exec_cmd(info, commandPath);
		free(commandPath);
	}
	else
	{
		if (info->arguments[0])
		{
			if ((info->arguments[0][0] == '/' || info->arguments[0][0] == '.')
					|| is_cmd(info->arguments[0]) == 1 || _getenv("PATH", environ))
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

