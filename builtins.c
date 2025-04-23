#include "shell.h"
/**
 * is_builtin - Vérifie si une commande est intégrée (exit ou env)
 * @cmd: Commande à vérifier
 *
 * Return: 1 si c’est un builtin (exit/env), sinon 0
 */
int is_builtin(char *cmd)
{
	if (cmd == NULL)
		return (0);
	if (strcmp(cmd, "exit") == 0 || strcmp(cmd, "env") == 0)
		return (1);
	return (0);
}

/**
 * animated_exit_message - Affiche un message avant de quitter
 */
void animated_exit_message(void)
{
	printf("Hasta la vista, baby! I'll be back...\n");
}

/**
 * handle_builtin - Gère les commandes intégrées (exit, env)
 * @argv: Arguments
 * @env: Environnement
 *
 * Return: 1 si builtin géré, sinon 0
 */
int handle_builtin(char **argv, char **env)
{
	int i;
	int status = 0; /* ✅ Déclaration en début de bloc, conforme C89 */

	if (argv == NULL || argv[0] == NULL)
		return (0);

	if (strcmp(argv[0], "exit") == 0)
	{
		animated_exit_message();

		/* ✅ Stocke la valeur AVANT de free */
		if (argv[1] != NULL)
			status = atoi(argv[1]);

		free_tokens(argv);
		free(line);

		exit(status);
	}
	else if (strcmp(argv[0], "env") == 0)
	{
		for (i = 0; env[i] != NULL; i++)
			printf("%s\n", env[i]);
		return (1);
	}

	return (0);
}
