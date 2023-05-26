#include "main.h"

/**
 * file_error - handles file error
 * @info: globals
 * Return: nothing
 */
void file_error(g_data *info)
{
	_eprint_one_line("Usage: ");
	_eprint_one_line(info->file_name);
	_eprint_one_line(" [batch_file]\n");
}

/**
 * print_alias - prints aliases
 * @tmp: a pointer to the head
 * Return: nothing
 */
void print_alias(l_node *tmp)
{
	_print_one_line(tmp->data);
	_print_one_line("=");
	_print_one_line(tmp->sub_data);
	_putchar('\n');
}

/**
 * check_err_cmd - verifies if user has permissions to access
 *
 * @dir: destination directory
 * @info: data structure
 * Return: 1 if there is an error, 0 if not
 */
int check_err_cmd(char *dir, g_data *info)
{
	if (dir == NULL)
	{
		error_handler(info, 127);
		return (1);
	}

	if (_strcmp(info->arguments[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			error_handler(info, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(info->arguments[0], X_OK) == -1)
		{
			error_handler(info, 126);
			return (1);
		}
	}

	return (0);
}


