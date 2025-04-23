#include "shell.h"
/**
 * is_builtin - Vérifie si une commande est intégrée (exit ou env)
 * @cmd: Commande à vérifier
 *
 * Retourne : 1 si intégrée, 0 sinon
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
 * animated_exit_message - Affiche un message avant la sortie
 */
void animated_exit_message(void)
{
	printf("Hasta la vista, baby! I'll be back...\n");
}

/**
 * handle_builtin - Exécute les commandes intégrées (exit, env)
 * @argv: Tableau d'arguments
 * @env: Variables d'environnement
 *
 * Renvoie : 1 si une commande intégrée a été gérée, 0 sinon
 */
int handle_builtin(char **argv, char **env)
{
	int i;

	if (argv == NULL || argv[0] == NULL)
		return (0);

	if (strcmp(argv[0], "exit") == 0)
	{
		animated_exit_message();
		if (argv[1] != NULL)
		{
			int status = atoi(argv[1]);
			exit(status);
		}
		else
		{
			exit(0);
		}
	}
	else if (strcmp(argv[0], "env") == 0)
	{
		for (i = 0; env[i] != NULL; i++)
			printf("%s\n", env[i]);
		return (1);
	}
	return (0);
}
