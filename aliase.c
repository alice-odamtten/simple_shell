#include "main.h"

/**
 * unalias_func - removes and alias from memory
 * @info: global data struction for application state
 * Return: 1 after every call
 */
int unalias_func(g_data *info)
{
	l_node *tmp, *prev;
	int idx = 1;

	if (info->arguments[1])
	{
		tmp = info->alias_db;

		while (info->arguments[idx] != NULL)
		{
			while (tmp != NULL)
			{
				prev = tmp;
				if (_strcmp(info->arguments[idx], tmp->data) == 0)
				{
					prev->next = tmp->next;
					free(tmp->data);
					free(tmp->sub_data);
					break;
				}
				tmp = tmp->next;
			}
			idx++;
		}
	}
	else
	{
		_puts("unalias: usage: unalias [-a] name [name ...]");
	}
	return (1);
}

/**
 * set_alias - sets an alias
 * @info: global data struction for application state
 * Return: 1 after every call
 */
int set_alias(g_data *info)
{
	int idx = 1, excess_count = 0;
	char *token, *ensure_full_alias[100];
	char **ptr;

	while (idx <= info->number_of_args && info->arguments[idx] != NULL)
	{
		if (contains_quotes(_strdup(info->arguments[idx])))
		{
			token_copier(info, &token, &idx);
		}
		else
		{
			if (is_valid_alias(info, info->arguments[idx]))
				token =  _sttrtok(info->arguments[idx], "=");
			else
			{
				idx++;
				continue;
			}
		}

		while (token != NULL)
		{
			ensure_full_alias[excess_count] = token;
			excess_count++;
			token = _sttrtok(NULL, " \t\n");
		}
		ensure_full_alias[excess_count] = NULL;
		ptr = ensure_full_alias;
		process_alias(info, &ptr, &excess_count);
		excess_count = 0;
		idx++;
	}
	return (1);
}

/**
 * process_alias - process as part of the set alias method
 * @info: global data struction for application state
 * @aliases: an array of aliases
 * @excess_count: a counter
 * Returns: nothing
 */
void process_alias(g_data *info, char ***aliases, int *excess_count)
{
	int j;
	char *alias, *temp, *cmd;

	temp = malloc(sizeof(char *) * 32);
	if (temp == NULL)
	{
		free(temp);
		return;
	}
	cmd = temp;
	for (j = 0; j < *excess_count - 1; j++)
	{
		alias = _strdup((*aliases)[j]);
		j++;
		if (_strlen((*aliases)[j]) > 0 && contains_quotes((*aliases)[j]))
		{
			_strcpy(cmd, _strdup((*aliases)[j]));
			j++;
			while (j < *excess_count)
			{
				_strcat(cmd, " ");
				_strcat(cmd, _strdup((*aliases)[j]));
				j++;
			}
			cmd = surround_with_quotes(sanitize_string2(cmd));
		}
		else
		{
			cmd = _strlen((*aliases)[j]) > 0 ?
			surround_with_quotes(_strdup((*aliases)[j])) : NULL;
		}
	}
	if (!cmd)
		perform_alias_insert(info, &alias, NULL);
	else
		perform_alias_insert(info, &alias, &(cmd));
	free(cmd);
	free(temp);
}

/**
 * free_alias - checks and frees an alias
 * @str: an alias string
 * Return: 1 if success or 0 for failure
 */
int free_alias(const char *str)
{
	char *temp;
	int result;

	temp = _strchr(str, '=');

	if (!temp)
		return (1);

	ptr = *temp;
	*temp = 0;

	return (result);
}


