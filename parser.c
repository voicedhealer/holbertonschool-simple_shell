#include "shell.h"

/**
 * parse_line - Découpe une ligne de commande en tokens
 * @line: Chaine d'entrée vers parse (ligne de commande)
 *
* Tokenise la chaîne d'entrée en utilisant des espaces,
 * des tabulations, des retours chariot et des sauts de ligne comme
 * délimiteurs. Renvoie un tableau de chaînes alloué dynamiquement (char **)
 * où chaque élément est un token de l'entrée.
 * Le tableau se termine par NULL.
 *
 * Return:
 * En cas de succès : tableau de tokens alloué dynamiquement.
 * En cas d'échec : NULL (entrée invalide ou erreur d'allocation mémoire).
 * L'appelant doit libérer le résultat avec free_tokens().
 */
char **parse_line(char *line)
{
	/* Déclaration des variables */
	char **argv = NULL;   /* Tableau de pointeurs vers les tokens */
	char *token = NULL;   /* Token courant */
	size_t argc = 0;      /* Compteur de tokens */
	size_t size = 8;      /* Capacité initiale du tableau */

	if (!line) /* Vérification de la validité de l'entrée */
		return (NULL);

	/* Allocation mémoire initiale pour le tableau de tokens */
	argv = malloc(size * sizeof(char *));
	if (!argv)
		return (NULL);

	/* Extraction du premier token */
	token = strtok(line, " \t\r\n");

	while (token) /* Parcours de tous les tokens */
	{
		/* Duplication et stockage du token */
		argv[argc] = strdup(token);
		if (!argv[argc])
		{
			free_tokens(argv);
			return (NULL);
		}
		argc++;

		/* Gestion du redimensionnement du tableau */
		if (argc >= size)
		{
			size *= 2;
			argv = realloc(argv, size * sizeof(char *));
			if (!argv)
				return (NULL);
		}
		token = strtok(NULL, " \t\r\n"); /* Extraction du token suivant */
	}

	argv[argc] = NULL; /* Marquage de la fin du tableau */
	return (argv); /* Retour du tableau de tokens */
}

/**
 * free_tokens - Libère un tableau de chaînes, terminé par NULL
 * @tokens: Tableau de chaînes à libérer
 *
 * Parcourt le tableau, libérant chaque chaîne et libérant finalement
 * le tableau lui-même. Gère les entrées NULL avec élégance.
 */
void free_tokens(char **tokens)
{
	size_t index; /* Compteur de boucle */

if (!tokens) /* Vérification de la validité du pointeur */
return;

/* Parcours et libération de chaque token */
for (index = 0; tokens[index] != NULL; index++)
free(tokens[index]); /* Libération mémoire d'un élément */

free(tokens); /* Libération du tableau principal */
}
