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
char *sh_read_line(g_data *info)
{
	char *line = NULL;
	static size_t buflen;

	if (_getline(&line, buflen, info->readfd) == -1)
	{
		if (feof(stdin))
		{
			perror("getline");
			exit(EXIT_SUCCESS);
		}
		else
		{
			exit(EXIT_FAILURE);
		}
	}
	return (line);
}

/**
 * process_interactive_commands - for handling interactive cmds
 * @info: global data for state management
 * Return: nothing
 */
void process_interactive_commands(g_data *info)
{
	int ret = 1;

	while (ret == 1)
	{
		write(STDOUT_FILENO, "$ ", 2);
		fflush(stdout);

		strcpy(info->command, sh_read_line(info));
		fflush(stdin);

		_strcspn(info->command);
		if (strlen(info->command) == 0)
		{
			ret = 1;
			continue;
		}
		ret = find_and_exec_cmd(info);

		info->counter += 1;
	}
}


