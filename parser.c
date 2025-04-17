#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
* parse_line - Découpe une ligne en arguments séparés par des espaces.
* @line: Ligne de commande à passer (modifiée par strtok).
*
* Description:
* Cette fonction prend une ligne de commande en entrée et la découpe
* en un tableau de chaines, chaque élément correspondant à un argument,
* en utilisant les espaces, tabulations et retours à la ligne comme
* séparateurs.
* Le tableau retournée est terminé par NULL et doit etre libéré par
* l'appelant.
*
* Return: Un tableau de chaines (arguments), terminé par NULL
* ou NULL en cas d'erreur.
*/
char **parse_line(char *line)
{
	char **argv = NULL;

	char *token;

	size_t argc = 0;
	size_t size = 8; /* Taille initiale du tableau */

	if (!line) /* Vérifie si la ligne est NULL */
	return (NULL);

    /* Alloue la mémoire initiale pour le tableau d'arguments */
	argv = malloc(size * sizeof(char *));
	if (!argv)
	return (NULL);

    /* Découpe la ligne en tokens selon les séparateurs */
	token = strtok(line, " \t\r\n");
	while (token)
	{
		argv[argc++] = token;

        /* Si la taille maximale est atteinte, réalloue plus d'espace */
		if (argc >= size)
		{
			size *= 2;
			argv = realloc(argv, size * sizeof(char *));
			if (!argv)
			return (NULL);
		}
		token = strtok(NULL, " \t\r\n");
	}
	argv[argc] = NULL; /* Termine le tableau par NULL */
	return (argv);
}

/**
 * free_tokens -
 * @tokens:
 */
void free_tokens(char **tokens)
{

}
