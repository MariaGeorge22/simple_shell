#include "simpleshell.h"

#define MAX_INPUT_SIZE 100

void display_prompt(void);
char *read_command(void);
void execute_command(char *command, char *program_name);

int main(void)
{
	char *command;

	while (1) {
		display_prompt();
		command = read_command();

		if (command == NULL)
		{
			/* Handle Ctrl+D (end of file) */
			printf("\n");
			break;
		}

		execute_command(command, "./hsh");
		free(command);
	}

	return 0;
}

void display_prompt(void)
{
	printf("#cisfun$ ");
	/* Flush output buffer to ensure the prompt is displayed immediately */
	fflush(stdout);
}

char *read_command(void)
{
	char *buffer = NULL;
	size_t bufsize = 0;
	ssize_t characters;

	characters = getline(&buffer, &bufsize, stdin);

	if (characters == -1)
	{
		free(buffer);
		/* Return NULL on Ctrl+D (end of file) */
		return NULL;
	}

	if (characters > 0 && buffer[characters - 1] == '\n')
	{
		/* Remove the newline character */
		buffer[characters - 1] = '\0';
	}

	return buffer;
}

void execute_command(char *command, char *program_name)
{
	pid_t pid;
	int status;
	char *argv[2];
	char *envp[1];

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		/* Child process */
		argv[0] = command;
		argv[1] =  NULL;
		/*envp[] = {NULL};*/

		if (execve(command, argv, envp) == -1)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", program_name,
				command);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process */
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}
