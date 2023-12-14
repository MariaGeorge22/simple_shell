#include "main.h"

/**
 * main - simple shell
 * @argc: the number of the arguments
 * @argv: the arguments
 * @env: the environment
 *
 * simulating how the shell works
 *
 * Return: 0 (Success)
 * or 1 (Fail)
 */
int main(int argc, char *argv[], char **env)
{
	int read_status, write_status;
	char **command_args = NULL, *path = NULL,
		 *p = argv[0];

	(void)argc;

	if (isatty(STDIN_FILENO) == IS_PART_OF_PIPE)
	{
		return (handle_pipe(p, env));
	}
	if (isatty(STDIN_FILENO) != IS_PART_OF_PIPE)
	{
		write(STDOUT_FILENO, "($) ", 4);
		read_status = read_cmd(&path, &command_args, p);
		while (read_status != EOF)
		{
			if (read_status != IS_NEW_LINE)
			{
				if (read_status != NOT_FOUND && read_status != EOF)
				{
					write_status = execute_cmd(&path, &command_args, p, env);
				}
				else
				{
					fprintf(stderr, "%s: 1: %s: not found\n", p, command_args[0]);
					free_args(&command_args);
				}
			}
			write(STDOUT_FILENO, "($) ", 4);
			read_status = read_cmd(&path, &command_args, p);
		}
		write(STDOUT_FILENO, "\n", 1);
	}
	return (write_status);
}
