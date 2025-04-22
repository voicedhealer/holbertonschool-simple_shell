#include "shell.h"
/**
 * parse_line - Découpe une ligne de commande en une liste de mots
 * @line: Chaîne de caractères à analyser (ligne de commande)
 *
 * Cette fonction prend une ligne de commande, la découpe selon les
 * séparateurs d'espaces, tabulations et retours à la ligne, puis retourne un
 * tableau dynamique de chaînes de caractères.
 * Chaque élément du tableau correspond à un mot extrait de la ligne.
 * Le tableau se termine par un pointeur NULL
 *
 * Return: Un tableau de chaînes de caractères (char **)
 * ou NULL en cas d'erreur
 */
char **parse_line(char *line)
{
	char **argv = NULL;

	char *token = NULL;

	size_t argc = 0;
	size_t size = 8; /* Taille initiale pour le tableau */

	if (!line)
		return (NULL);

	/* Allocation initiale du tableau de pointeurs */
	argv = malloc(size * sizeof(char *));
	if (!argv)
		return (NULL);

	/* Découpe la ligne selon les séparateurs */
	token = strtok(line, " \t\r\n");
	while (token)
	{
		argv[argc] = strdup(token); /* Duplique la chaîne pour allocation propre */
		if (!argv[argc])
		{
			free_tokens(argv);
			return (NULL);
		}
		argc++;

		/* Si tableau plein, on double sa taille */
		if (argc >= size)
		{
			size *= 2;
			argv = realloc(argv, size * sizeof(char *));
			if (!argv)
				return (NULL);
		}
		token = strtok(NULL, " \t\r\n");
	}
	argv[argc] = NULL; /* Marque la fin du tableau */
	return (argv);
}


/**
* free_tokens - Libère un tableau de chaînes de caractères
* @tokens: tableau de chaînes terminé par NULL
*/
void free_tokens(char **tokens)
{
	size_t index;

	if (!tokens)
		return;

	for (index = 0; tokens[index] != NULL; index++)
		free(tokens[index]);

	free(tokens);
}
