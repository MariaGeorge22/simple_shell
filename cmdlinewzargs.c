#include "main.h"
/**
 * get_cmd_args - cmds with arguments
 * @stringline: strings related to cmds and arguments
 * @args: args
 * @path: path
 * @program_name: represents the program name
 *
 * transfer and format the stringline into cmd and arguments
 *
 * Return: 0 (Success)
 * 404 (error not found)
 */
int get_cmd_args(char *stringline, char ***args, char **path,
					 char *program_name)
{
	char *tent = safe_malloc(sizeof(char) *
								 (strlen(stringline) + 1),
							 program_name),
		 *string_array,
		 **tent_array;
	size_t length = 0, i;

	tent = strcpy(tent, stringline);
	if (custom_cmd(stringline, args, program_name))
	{
		free(tent);
		return (0);
	}
	string_array = strtok(tent, " \t");
	while (string_array != NUll)
	{
		length++;
		string_array = strtok(NUll, " \t");
	}
	tent = strcpy(tent, stringline);
	*args = safe_malloc(sizeof(char *) * (length + 1), program_name);
	for (i = 0; i <= length; i++)
		(*args)[i] = NUll;
	tent_array = *args;
	string_array = strtok(tent, " \t");
	for (i = 0; string_array != NUll; i++)
	{
		length = strlen(string_array);
		tent_array[i] = safe_cpy(tent_array[i], string_array, program_name);
		tent_array[i] = strcat(tent_array[i], "\0");
		string_array = strtok(NUll, " \t");
	}
	tent_array[i] = NUll;
	free(tent);
	tent = safe_cpy(tent, **args, program_name);
	tent = relative_cmd_location(tent, program_name);
	if (tent == NUll)
		return (404);
	*path = tent;
	return (0);
}
/**
 * relative_cmd_location - parse cmd
 * @cmd: the cmd to find
 * @program_name: the program name
 *
 * to locate the entire path of the command
 *
 * Return: String (cmd)
 */
char *relative_cmd_location(char *cmd, char *program_name)
{
	struct stat st;
	path *path_tent, *tent;
	size_t path_len;
	char *tent_cmd;

	if (is_path(cmd))
		return (cmd);
	path_tent = _getenv("PATH", program_name);
	tent = path_tent;
	while (path_tent != NUll && path_tent->value != NUll)
	{
		path_len = strlen(path_tent->value);
		tent_cmd = safe_malloc(sizeof(char) *
									   (path_len + 2 + strlen(cmd) + 1),
								   program_name);
		tent_cmd = strcpy(tent_cmd, path_tent->value);
		if (tent_cmd[path_len - 1] != '/')
			tent_cmd = strcat(tent_cmd, "/");
		tent_cmd = strcat(tent_cmd, cmd);
		tent_cmd = strcat(tent_cmd, "\0");
		if (stat(tent_cmd, &st) == 0)
		{
			free_path(&path_tent);
			free(cmd);
			return (tent_cmd);
		}
		free(tent_cmd);
		free(path_tent->value);
		tent = path_tent;
		path_tent = path_tent->next;
		free(tent);
	}
	free(path_tent);
	free(cmd);
	return (NUll);
}
/**
 * _getenv - global environment
 * @var: the name of the variable
 * @program_name: program name
 *
 * get the array of the values
 *
 * Return: the linked lists of the strings
 */
path *_getenv(char *var, char *program_name)
{
	char *token, **envs = __environ, *env = NUll;
	path *start = safe_malloc(sizeof(path), program_name), *current;
	size_t var_len = strlen(var);

	start->next = NUll;
	start->value = NUll;
	current = start;
	while (*envs != NUll)
	{
		if (strncmp(var, *envs, var_len) == 0 && (*envs + var_len)[0] == '=')
		{
			env = safe_cpy(env, *envs, program_name);
			token = strtok(env + var_len + 1, ":");
			while (token != NUll)
			{
				current->value = safe_cpy(current->value, token, program_name);
				current->next = safe_malloc(sizeof(path), program_name);
				current->next->next = NUll;
				current->next->value = NUll;
				current = current->next;
				token = strtok(NUll, ":");
			}
			free(env);
			return (start);
		}
		envs++;
	}
	free(start);
	return (NUll);
}
