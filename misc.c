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
	int i;

	info->file_name = av[0];
	info->file = av[1];
	info->number_of_args = 0;
	info->counter = 1;
	info->readfd = 0;
	info->argc = c;
	info->alias_db = NULL;
	info->command = NULL;
	info->status = 0;

	for (i = 0; environ[i]; i++)
		;

	/**
	 * info->env_db = malloc(sizeof(char *) * (i + 1));
	 * for (i = 0; environ[i]; i++)
	 * {
	 * info->env_db[i] = environ[i];
	 * }
	 * info->env_db[i] = NULL;
	 */
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

	/*int i = 0;*/


	free(info->command);

	/**
	 * if (info->env_db == NULL)
	 * return;
	 * while (info->env_db[i] != NULL)
	 * {
	 * free(info->env_db[i]);
	 * info->env_db[i] = NULL;
	 * i++;
	 * }
	 * free(info->env_db);
	 */
	/*info->env_db = NULL;*/
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

/**
 * command_failure_err - generic error message for exit in get_exit
 * @info: data relevant (counter, arguments)
 * Return: Error message
 */
char *command_failure_err(g_data *info)
{
	int length;
	char *error;

	length = _strlen(info->file_name);
	length += _strlen(info->arguments[0]) + _strlen(info->arguments[1]) + 23;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		return (NULL);
	}
	_strcpy(error, info->file_name);
	_strcat(error, ": ");
	_strcat(error, " can not access");
	_strcat(error, " \'");
	_strcat(error, info->command);
	_strcat(error, "\'");
	_strcat(error, ": No such file or directory");
	_strcat(error, "\n\0");

	return (error);
}
