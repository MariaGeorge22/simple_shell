#include "main.h"

/**
 * execute_cmd - run the commands
 * @path: the path of the command
 * @argv: the arguments of the command
 * @p: the name of the program
 * @env: the environment
 *
 * executing the commands
 *
 * Return: 0 (Success)
 */
int execute_cmd(char **path, char **argv[],
					char *p, char **env)
{
	pid_t pid;
	int child_status, exit_status = 0;

	if (!execute_custom_command(path, argv, p))
	{
		pid = fork();
		if (pid == EXEC_ERROR)
		{
			perror(p);
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			if (execve(*path, (*argv), env) == EXEC_ERROR)
			{
				free(*path);
				free_args(argv);
				perror(p);
				exit(EXIT_FAILURE);
			}
			exit(EXIT_SUCCESS);
		}
		else
		{
			wait(&child_status);
			exit_status = WEXITSTATUS(child_status);
			free(*path);
			free_args(argv);
		}
	}
	return (exit_status);
}