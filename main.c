#include "shell.h"

/**
 * main - Point d’entrée du shell, initialise et lance la boucle principale
 * @ac: nombre d'arguments (non utilisé)
 * @av: tableau d'arguments
 * @env: tableau des variables d’environnement
 *
 * Return: 0 à la fin
 */
int main(int ac, char **av, char **env)
{
	(void)ac;
	PROGRAM_NAME = av[0];
	main_loop(env);
	return (0);
}

/**
 * main_loop - Boucle principale du shell : prompt + traitement commande
 * @env: tableau des variables d’environnement
 */
void main_loop(char **env)
{
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
			handle_builtin(argv, env);
		else
			execute_command(argv, env);

		free(line);
		free_tokens(argv);
	}
}

/**
 * prompt_display - Affiche le prompt "*** " si shell interactif
 */
void prompt_display(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "*** ", 4);
}
