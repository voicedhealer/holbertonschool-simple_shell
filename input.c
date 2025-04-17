#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
/**
* read_input - Affiche un prompt et lit une ligne de l'utilisateur.
*
* Description:
* cette fonction affiche le prompt "$ " à l'écran, puis attend que
* l'utilisateur saissise une ligne de texte sur l'entrée standard (stdin).
* Elle utilise getline pour allouer dynamiquement la mémoire néccessaire
* à la chaine lue, quelle que soit sa longueur. si l'utilisateur envoie
* un signal de fin de fichier (Ctrl+D), la fonction libère la mémoire
* allouée et retourne NULL pour indiquer la fin de l'entrée.
*
* Return: Un pointeur vers la ligne lue (à libérer par l'appelant),
* ou NULL en cas d'erreur ou de fin de fichier.
*/

char *read_input(void)
{
	char *line = NULL;

	size_t buffer_size = 0;

	/* Affiche le prompt et force l'affichage immédiat */
	printf("$ ");
	fflush(stdout);

	/* Lit une ligne depuis l'entrée standard */
	if (getline(&line, &buffer_size, stdin) == -1)
	{
	free(line);
	return (NULL);
	}
	return (line);
}

#include <string.h>
/**
* trim_newline - suprime le caractère de nouvelle ligne d'une chaine.
* @line: chaine a nettoyer.
*
* Description:
* Cette fonction recherche le caractère de retour à la ligne ('\n')
* à la fin de la chaine passée en argument et s'il est présent,
* le remplace par le caractère de fin de chaine ('\0')
*
* Return: la chaine modifiée (même pointeur) ou NULL si l'entrée est NULL.
*/

char *trim_newline(char *line)
{
	size_t len;

    /* Vérifie si la chaîne est NULL */
	if (!line)
	return (NULL);

     /* Calcule la longueur de la chaîne */
	len = strlen(line);

     /* Si la chaîne n'est pas vide et se termine par '\n', le retire */
	if (len > 0 && line[len - 1] == '\n')
	line[len - 1] = '\0';

	return (line);
}
