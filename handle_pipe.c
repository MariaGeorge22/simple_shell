#include "main.h"

/**
 * handle_pipe - the pipe handling - run commands
 * in pipe mode
 * @p: the name of the program
 * @env: environment
 *
 * executing the commands in a pipe
 *
 * Return: 0 (Success)
 * 1 (Error)
 */
int handle_pipe(char *p, char **env)
{
	char **command_args = NULL, *path = NULL,
		 *line = safe_malloc(sizeof(char) * MAX_LINE_LENGTH, p), *one_line,
		 *temp, **save_ptr = safe_malloc(sizeof(char) * MAX_LINE_LENGTH, p);
	ssize_t i, status = 0, len = MAX_LINE_LENGTH;

	i = _getline(&line, &len, stdin, p);
	if (!is_empty(line))
	{
		if (i == EOF)
		{
			perror(p);
			free_args(&command_args);
			exit(139);
		}
		one_line = strtok_r(line, "\n", save_ptr);
		while (one_line != NULL)
		{
			temp = safe_cpy(temp, one_line, p);
			i = get_command_args(temp, &command_args, &path, p);
			free(temp);
			if (i != NOT_FOUND && i != EOF)
			{
				if (strcmp(command_args[0], "exit") == 0)
					free_many(2, line, save_ptr);
				status = execute_cmd(&path, &command_args, p, env);
				if (status != EXIT_SUCCESS)
					break;
			}
			else
			{
				status = 127;
				fprintf(stderr, "%s: 1: %s: not found\n", p, command_args[0]);
				free(path);
				free_args(&command_args);
			}
			one_line = strtok_r(NULL, "\n", save_ptr);
		}
	}
	free_many(2, save_ptr, line);
	return (status);
}
