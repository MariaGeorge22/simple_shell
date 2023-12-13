#include "main.h"
#define MAX_READ_BUFFER_SIZE 1024
static char buffer[MAX_READ_BUFFER_SIZE + 1] = {'\0'}, *temp;
static ssize_t read_len = 0, read_status, temp_len;
/**
 * custom_commands_handle - custom commands formatting
 * @sringline: this string is to find arguments
 * @args: the arguments
 * @program_name: program name
 *
 * custom arguments handling
 *
 * Return: true if found,
 * false if generic
 */
bool custom_commands_handle(char *sringline, char ***args, char *program_name)
{
	char *temp = NULL;

	if (strncmp(sringline, "exit", 4) == 0)
	{
		temp = strtok(sringline, " ");
		temp = strtok(NULL, " ");
		if (temp != NULL)
		{
			*args = safe_malloc(sizeof(char *) * 3, program_name);
			(*args)[0] = "exit";
			(*args)[1] = NULL;
			(*args)[1] = safe_malloc(sizeof(char) * (strlen(temp) + 1), program_name);
			(*args)[1] = strcpy((*args)[1], temp);
			(*args)[1] = strcat((*args)[1], "\0");
			(*args)[2] = NULL;
		}
		else
		{
			*args = safe_malloc(sizeof(char *) * 2, program_name);
			(*args)[0] = "exit";
			(*args)[1] = NULL;
		}

		return (true);
	}
	else if (strncmp(sringline, "env", 3) == 0)
	{
		*args = safe_malloc(sizeof(char *) * 2, program_name);
		(*args)[0] = "env";
		(*args)[1] = NULL;
		return (true);
	}
	return (false);
}
/**
 * custom_command_execution - command format execution
 * @cmd: the argument of the command
 * @path: the path of the command
 * @program_name: the program name
 *
 * custom argument handling
 *
 * Return: true if found,
 * false if generic
 */
bool custom_command_execution(char **path, char ***cmd, char *program_name)
{
	long int exit_status = EXIT_SUCCESS;
	size_t i;

	if (strcmp((*cmd)[0], "exit") == 0)
	{
		if ((*cmd)[1] != NULL)
		{
			exit_status = strtol((*cmd)[1], NULL, 10);
			for (i = 0; (*cmd)[1][i] != '\0'; i++)
			{
				if (!isdigit((*cmd)[1][i]))
				{
					fprintf(stderr, "%s: 1: exit: Illegal number: %s\n",
							program_name, (*cmd)[1]);
					free((*cmd)[1]);
					free(*cmd);
					exit(2);
				}
			}
			free((*cmd)[1]);
		}
		free(*cmd);
		exit(exit_status < 0 ? -1 : exit_status);
	}
	else if (strcmp((*cmd)[0], "env") == 0)
	{
		free(*path);
		free(*cmd);
		print_env();
		return (true);
	}
	return (false);
}
/**
 * print_env - environmet printing
 *
 * prints the envrionment
 *
 * Return: void
 */
void print_env(void)
{
	char **envs = __environ;

	while (envs != NULL && *envs != NULL)
	{
		printf("%s\n", *envs);
		(envs)++;
	}
}
/**
 * _getline - custom the getline function
 * @lineptr: the address of buffering to fill
 * @len: the size of buffering
 * @file: the file to be read
 * @program_name: the program name
 *
 * getline at home location
 *
 * Return: the Pointer to the entered line
 */
ssize_t _getline(char **lineptr, ssize_t *len, FILE *file, char *program_name)
{

	fflush(NULL);
	read_status = read(file->_fileno, buffer, MAX_READ_BUFFER_SIZE);
	if (read_status < *len)
	{
		if (read_status == 0)
			return (-1);
		*lineptr = strcpy(*lineptr, buffer);
		return (read_status);
	}
	**lineptr = '\0';
	while (read_status > 0)
	{
		read_status = read(file->_fileno, buffer, MAX_READ_BUFFER_SIZE);
		temp = safe_malloc(sizeof(char) * (strlen(*lineptr) + 1), program_name);
		temp = strcpy(temp, *lineptr);
		read_len = strcspn(buffer, "\n");
		temp_len = strlen(temp) + read_len;
		free(*lineptr);
		*lineptr = safe_malloc(sizeof(char) * (temp_len + 1), program_name);
		*lineptr = strcpy(*lineptr, temp);
		*lineptr = strncat(*lineptr, buffer, read_len);
		*len += read_len;
		if (read_status < MAX_READ_BUFFER_SIZE && buffer[read_status - 1] == '\n')
			break;
		free(temp);
	}
	free(temp);
	return (temp_len);
}
