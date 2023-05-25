#include "main.h"

/**
 * init_g_data - initialize global data
 * @info: globals from header
 * @av: cli arguments
 * @c: number of cli arguments
 * Return: nothing just null
 */
void init_g_data(g_data *info, char **av, int c)
{

	info->file_name = av[0];
	info->file = av[1];
	info->number_of_args = 0;
	info->counter = 1;
	info->readfd = 0;
	info->argc = c;
	info->alias_db = NULL;
}

/**
 * is_shell_interactive - checks if shell is interactive
 * Return: 1 or 0
 */
ssize_t is_shell_interactive(void)
{
	return (isatty(STDIN_FILENO));
}

/**
 * free_all - frees global pointers
 * @info: global variables
 * Return: nothing
 */
void free_all(g_data *info)
{

	/*free(info->environ);*/
	freeList(&(info->alias_db));
}

/**
 * rem_trail_spaces - removes trailing spaces
 * @str: the input string
 */
void rem_trail_spaces(char *str)
{
	int i, j;
	int n = _strlen(str);

	for (i = 0; i < n; i++)
	{
		if (str[i] != ' ')
			break;
	}

	for (j = 0; i < n; i++, j++)
	{
		str[j] = str[i];
	}
	str[j] = '\0';
}
