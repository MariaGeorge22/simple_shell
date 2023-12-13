#include "main.h"

#define MAX_INPUT_SIZE 100

void display_prompt(void);
char *read_command(void);
void execute_command(const char *command);

int main(void)
{
	char *command;

	while (1) {
		display_prompt();
		command = read_command();

		if (command == NULL) {
			printf("\n");  // Handle Ctrl+D (end of file)
			break;
		}

		execute_command(command);
		free(command);
	}

	return 0;
}

void display_prompt(void)
{
	printf("$ ");
	fflush(stdout);  // Flush the output buffer to ensure the prompt is displayed immediately
}

char *read_command(void)
{
	char *buffer = NULL;
	size_t bufsize = 0;
	ssize_t characters;

	characters = getline(&buffer, &bufsize, stdin);

	if (characters == -1) {
		free(buffer);
		return NULL;  // Return NULL on Ctrl+D (end of file)
	}

	if (characters > 0 && buffer[characters - 1] == '\n') {
		buffer[characters - 1] = '\0';  // Remove the newline character
	}

	return buffer;
}

void execute_command(const char *command)
{
	pid_t pid;
	int status;

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		// Child process
		if (execlp(command, command, (char *)NULL) == -1) {
			perror("execlp");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		// Parent process
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}
