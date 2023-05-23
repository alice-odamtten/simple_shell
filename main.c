#include "main.h"

/**
 * main - entry point
 * @c:  number of cli arguments
 * @av: an array of cli arguments
 * @emv: environment variables
 * Return: 1
 */
int main(int c, char **av, char **env)
{
	g_data info;

	init_g_data(&info, av, env, c);
	cmd_handler(&info, c);

	return (1);
}
