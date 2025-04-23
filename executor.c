#include "shell.h"
int execute_command(char **argv, char **env)
{
	pid_t pid;
	char *cmd_path = NULL;

	if (strchr(argv[0], '/'))
	{
		if (access(argv[0], X_OK) == 0)
		{
			cmd_path = strdup(argv[0]);
			if (!cmd_path)
				return (127);
		}
		else
		{
			fprintf(stderr, "%s: 1: %s: not found\n", PROGRAM_NAME, argv[0]);
			return (127);
		}
	}
	else
	{
		cmd_path = find_command_path(argv[0], env);
		if (!cmd_path)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", PROGRAM_NAME, argv[0]);
			return (127);
		}
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(cmd_path);
		return (127);
	}
	else if (pid == 0)
	{
		execve(cmd_path, argv, env);
		perror(argv[0]);
		free(cmd_path);
		exit(1);
	}
	else
	{
		wait(NULL);
	}

	free(cmd_path);
	return (0);
}
