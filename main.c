#include "simpleshell.h"

/**
 * main - simple shell program
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
        char *line = NULL, *args[64];
        int i = 0;
        size_t len = 0;
        pid_t child_pid;

        while (1)
        {
                printf("#cisfun$ ");
                getline(&line, &len, stdin);

                /*      command = strtok(line, " \n");*/

                args[i++] = strtok(line, " \n");
                while (i < 63 && (args[i++] = strtok(NULL, " \n")) != NULL);

                args[i] = NULL;

                child_pid = fork();
                if (child_pid == -1)
                {
                        perror("Error:");
                        exit(EXIT_FAILURE);
                }

                if (child_pid == 0)
                {
                        execve(args[0], args, NULL);
                        perror("execve");
                        exit(EXIT_FAILURE);
                }
                else
                        wait(NULL);

        }



        free(line);

        return (0);
}
