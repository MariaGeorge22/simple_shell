#include "main.h"

/**
 * read_cmd - the commands that will be read
 * @path: the path of the command
 * @command_args: the command arguments
 * @p: command arguments
 *
 * commands formatting
 *
 * Return: the status of the getline
 */
int read_cmd(char **path, char ***command_args, char *p)
{
	int status;
	char *line = safe_malloc(sizeof(char) * MAX_LINE_LENGTH, p);
	ssize_t len = MAX_LINE_LENGTH;

	status = _getline(&line, &len, stdin, p);
	if (status != EOF)
	{
		if (strlen(line) == 1 && line[0] == '\n')
		{
			free(line);
			return (IS_NEW_LINE);
		}
		if ((line)[strlen(line) - 1] == '\n')
			(line)[strlen(line) - 1] = '\0';
		status = get_command_args(line, command_args, path, p);
	}
	free(line);
	return (status);
}