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

 /*Cette fonction reçoit une phrase (line)*/
 /*et retourne un tableau de mots (char **)*/
char **parse_line(char *line)
{
/*Le tableau de mots (ce sera le résultat final)*/
	char **argv = NULL;

/*Chaque mot trouvé, un par un*/
	char *token = NULL;

/*Le nombre de mots déjà trouvés*/
	size_t argc = 0;
	size_t size = 8; /* Taille initiale pour le tableau (8)*/

/*Si on donne une ligne vide (ou NULL)*/
/*la fonction ne fait rien et retourne aussi NULL*/
	if (!line)
		return (NULL);

	/* Allocation initiale du tableau de pointeurs */
	argv = malloc(size * sizeof(char *));
	if (!argv)
		return (NULL);

	/* Découpe la ligne selon les séparateurs */
	token = strtok(line, " \t\r\n");

	/*Pas nul tant qu'il y a encore un mot*/
	while (token)
	{
		argv[argc] = strdup(token); /* Duplique la chaîne pour allocation propre */
		if (!argv[argc])
		{
			free_tokens(argv);
			return (NULL);
		}

		/*Ajoute un mot en plus dans le tableau*/
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

/*Reçoit tableau à libérer*/
void free_tokens(char **tokens)
{
	size_t index;

/*Ne fais rien si on ne lui donne rien*/
	if (!tokens)
		return;

	/*Libère chaque chaine du tableau*/
	for (index = 0; tokens[index] != NULL; index++)
		free(tokens[index]);

	/*Libère le tableau*/
	free(tokens);
}
