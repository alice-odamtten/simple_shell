#include "main.h"

/**
 * init_g_data - initialize global data
 * @info: globals from header
 * @av: cli arguments
 * @env: environmental variables
 * @c: number of cli arguments
 * Return: nothing just null
 */
char **init_g_data(g_data *info, char **av, char **env, int c)
{
	int idx;

	info->file_name = av[0];
	info->file = av[1];
	info->number_of_args = 0;
	info->counter = 1;
	info->readfd = 0;
	info->argc = c;
	info->alias_db = NULL;

	for (idx = 0; env[idx]; idx++)
		;

	info->environ = malloc(sizeof(char *) * (idx + 1));
	if (info->environ == NULL)
	{
		_puts("failed to initialize envs");
		exit(0);
	}

	idx = 0;
	while (env[idx] != NULL)
	{
		info->environ[idx] = env[idx];
		idx++;
	}
	info->environ[idx] = NULL;

	return (NULL);
}
