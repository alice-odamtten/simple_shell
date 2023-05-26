#include "main.h"

/**
 * cmp_env_name - compares env variables names
 * with the name passed.
 * @nenv: name of the environment variable
 * @name: name passed
 *
 * Return: 0 if are not equal. Another value if they are.
 */
int cmp_env_name(const char *nenv, const char *name)
{
	int i;

	for (i = 0; nenv[i] != '='; i++)
	{
		if (nenv[i] != name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}

/**
 * _getenv - get an environment variable
 * @name: name of the environment variable
 * @_environ: environment variable
 *
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *_getenv(const char *name, char **_environ)
{
	char *ptr = NULL;
	int i, found = 0;

	for (i = 0; _environ[i]; i++)
	{
		found = cmp_env_name(_environ[i], name);
		if (found)
		{
			ptr = _environ[i];
			break;
		}
	}

	return (ptr + found);
}

/**
 * _envp -  handles the env command
 * @info: globals
 * Return: 1 or 0
 */
int _envp(__attribute__((unused)) g_data * info)
{

	char **env = environ;

	while (*env)
	{
		write(STDOUT_FILENO, *env, _strlen(*env));
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}
	return (1);
}
