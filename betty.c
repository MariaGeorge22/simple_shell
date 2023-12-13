#include "main.h"
/**
 * is_empty - test if the string is empty
 * @stringline: str to check
 *
 * tests the empty strings
 *
 * Return: bool
 */
bool is_empty(char *stringline)
{
	while (*stringline != '\0')
	{
		if (!isspace(*stringline))
		{
			return (false);
		}
		stringline++;
	}
	return (true);
}
/**
 * safe_cpy - copy the stringline
 * @dest: the destination of the stringline
 * @src: the destination source
 * @program_name: destination
 *
 * copy the stringline
 *
 * Return: char *
 */
char *safe_cpy(char *dest, char *src, char *program_name)
{
	int len = strlen(src);

	dest = safe_malloc(sizeof(char) * (len + 1), program_name);
	dest = strcpy(dest, src);
	dest[len] = '\0';
	return (dest);
}
/**
 * is_path - test the path
 * @cmd: the command
 *
 * tests if the command has a path
 *
 * Return: bool
 */
bool is_path(char *cmd)
{
	bool is_path = cmd[0] == '/' || strncmp(cmd, "./", 2) == 0 ||
				   strncmp(cmd, "../", 3) == 0;

	return (is_path);
}
