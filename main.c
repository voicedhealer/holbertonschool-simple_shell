#include "shell.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *PROGRAM_NAME = NULL;
char *line = NULL;        /* 👉 rendu global */
char **argv = NULL;       /* 👉 rendu global */

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	PROGRAM_NAME = av[0];

	while (1)
	{
		prompt_display();
		line = read_input();
		if (!line)
			break;

		line = trim_newline(line);

		if (is_line_empty(line))
		{
			free(line);
			continue;
		}

		argv = parse_line(line);
		if (!argv || !argv[0])
		{
			free(line);
			free_tokens(argv);
			continue;
		}

		if (is_builtin(argv[0]))
		{
			handle_builtin(argv, env);
		}
		else
		{
			execute_command(argv, env);
		}

		free(line);
		free_tokens(argv);
	}

	free(line);
	return (0);
}

/**
 * prompt_display - Affiche le prompt "*** " si shell interactif
 */
void prompt_display(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "*** ", 4);
}
