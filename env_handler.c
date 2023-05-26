#include "main.h"

/**
 * copy_info - copies info to create
 * a new env or alias
 * @name: name (env or alias)
 * @value: value (env or alias)
 *
 * Return: new env or alias.
 */
char *copy_info(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = _strlen(name);
	len_value = _strlen(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}

/**
 * set_env - sets an environment variable
 *
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @info: data structure (environ)
 * Return: no return
 */
void set_env(char *name, char *value, g_data *info)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; info->env_db[i]; i++)
	{
		var_env = _strdup(info->env_db[i]);
		name_env = _sttrtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(info->env_db[i]);
			info->env_db[i] = copy_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	info->env_db = _realloc(info->env_db, i, sizeof(char *) * (i + 2));
	info->env_db[i] = copy_info(name, value);
	info->env_db[i + 1] = NULL;
}

/**
 * _setenv - compares env variables names
 * with the name passed.
 * @info: data relevant (env name and env value)
 *
 * Return: 1 on success.
 */
int _setenv(g_data *info)
{

	if (info->arguments[1] == NULL || info->arguments[2] == NULL)
	{
		error_handler(info, -1);
		return (1);
	}

	set_env(info->arguments[1], info->arguments[2], info);

	return (1);
}

/**
 * _unsetenv - deletes a environment variable
 *
 * @info: data relevant (env name)
 *
 * Return: 1 on success.
 */
int _unsetenv(g_data *info)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int i, j, k;

	if (info->arguments[1] == NULL)
	{
		error_handler(info, -1);
		return (1);
	}
	k = -1;
	for (i = 0; info->env_db[i]; i++)
	{
		var_env = _strdup(info->env_db[i]);
		name_env = _sttrtok(var_env, "=");
		if (_strcmp(name_env, info->arguments[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		error_handler(info, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; info->env_db[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = info->env_db[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(info->env_db[k]);
	free(info->env_db);
	info->env_db = realloc_environ;
	return (1);
}

