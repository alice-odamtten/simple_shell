#include "main.h"

/**
 * cd_dot - changes to the parent directory
 *
 * @info: data relevant (environ)
 *
 * Return: no return
 */
void cd_dot(g_data *info)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	setenv("OLDPWD", cp_pwd, 1);
	dir = info->arguments[1];
	if (_strcmp(".", dir) == 0)
	{
		setenv("PWD", cp_pwd, 1);
		free(cp_pwd);
		return;
	}
	if (_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	rev_string(cp_strtok_pwd);
	cp_strtok_pwd = _sttrtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _sttrtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			rev_string(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		setenv("PWD", cp_strtok_pwd, 1);
	}
	else
	{
		chdir("/");
		setenv("PWD", "/", 1);
	}
	info->status = 0;
	free(cp_pwd);
}

/**
 * cd_to - changes to a directory given
 * by the user
 *
 * @info: data relevant (directories)
 * Return: no return
 */
void cd_to(g_data *info)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = info->arguments[1];
	if (chdir(dir) == -1)
	{
		error_handler(info, 3);
		return;
	}

	cp_pwd = _strdup(pwd);
	setenv("OLDPWD", cp_pwd, 1);

	cp_dir = _strdup(dir);
	setenv("PWD", cp_dir, 1);

	free(cp_pwd);
	free(cp_dir);

	info->status = 0;

	chdir(dir);
}

/**
 * cd_previous - changes to the previous directory
 *
 * @info: data relevant (environ)
 * Return: no return
 */
void cd_previous(g_data *info)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	p_oldpwd = _getenv("OLDPWD", environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);

	setenv("OLDPWD", cp_pwd, 1);

	if (chdir(cp_oldpwd) == -1)
		setenv("PWD", cp_pwd, 1);
	else
		setenv("PWD", cp_oldpwd, 1);

	p_pwd = _getenv("PWD", environ);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	info->status = 0;

	chdir(p_pwd);
}

/**
 * cd_to_home - changes to home directory
 *
 * @info: data relevant (environ)
 * Return: no return
 */
void cd_to_home(g_data *info)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	home = _getenv("HOME", environ);

	if (home == NULL)
	{
		setenv("OLDPWD", p_pwd, 1);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		error_handler(info, 3);
		free(p_pwd);
		return;
	}

	setenv("OLDPWD", p_pwd, 1);
	setenv("PWD", home, 1);
	free(p_pwd);
	info->status = 0;
}

/**
 * rev_string - reverses a string.
 * @s: input string.
 * Return: no return.
 */
void rev_string(char *s)
{
	int count = 0, i, j;
	char *str, temp;

	while (count >= 0)
	{
		if (s[count] == '\0')
			break;
		count++;
	}
	str = s;

	for (i = 0; i < (count - 1); i++)
	{
		for (j = i + 1; j > 0; j--)
		{
			temp = *(str + j);
			*(str + j) = *(str + (j - 1));
			*(str + (j - 1)) = temp;
		}
	}
}
