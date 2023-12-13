#include "main.h"
/**
 * is_empty - test if str is empty
 * @stringline: str to test
 *
 * test empty strs
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
 * safe_cpy - to copy stringline
 * @dest: destination
 * @src: destination
 * @program_name: destination
 *
 * copies stringline
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
 * @cmd: command
 *
 * test the command
 * a "path"ed one
 *
 * Return: bool
 */
bool is_path(char *cmd)
{
	bool is_path = cmd[0] == '/' || strncmp(cmd, "./", 2) == 0 ||
				   strncmp(cmd, "../", 3) == 0;

	return (is_path);
}
