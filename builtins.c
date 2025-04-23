#include "shell.h"
/**
 * is_builtin - Vérifie si une commande est intégrée (exit ou env)
 * @cmd: Pointeur vers la chaîne de caractères
 * représentant la commande à vérifier
 *
 * Return: 1 si la commande est un builtin ("exit" ou "env"), sinon 0
 */
int is_builtin(char *cmd)
{
	if (cmd == NULL) /* Vérifie si le pointeur cmd est NULL */
		return (0);
	/* Compare la commande à "exit" ou "env" */
	if (strcmp(cmd, "exit") == 0 || strcmp(cmd, "env") == 0)
		return (1);
	/* Retourne 0 si la commande n'est pas un builtin */
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
 * @argv: Tableau de pointeurs vers les arguments de la commande
 * @env: Tableau de pointeurs vers les variables d'environnement
 *
 * Return: 1 si une commande builtin a été gérée, sinon 0
 */
int handle_builtin(char **argv, char **env)
{
	int i; /* Déclare l'index pour la boucle */
	/* Initialise le code de sortie à 0 */
	int status = 0; /* ✅ Déclaration en début de bloc, conforme C89 */

	/* Vérifie si argv ou argv[0] est NULL */
	if (argv == NULL || argv[0] == NULL)
		return (0);

	if (strcmp(argv[0], "exit") == 0) /* Vérifie si la commande est "exit" */
	{
		animated_exit_message(); /* Affiche un message de sortie animé */

		/* ✅ Stocke la valeur AVANT de free */
		/* Si un argument est fourni après "exit", le convertir en entier */
		if (argv[1] != NULL)
			status = atoi(argv[1]);

		free_tokens(argv); /* Libère la mémoire allouée pour les arguments */
		free(line); /* Libère la mémoire allouée pour la ligne de commande */

		exit(status); /* Quitte le programme avec le code de sortie approprié */
	}
	else if (strcmp(argv[0], "env") == 0) /* Vérifie si la commande est "env" */
	{
		/* Parcourt et affiche toutes les variables d'environnement */
		for (i = 0; env[i] != NULL; i++)
			printf("%s\n", env[i]);
		return (1); /* Indique qu'un builtin a été géré */
	}

	return (0); /* Retourne 0 si aucune commande builtin n'a été gérée */
}
