#include "shell.h"

/**
* get_path_copy - Extrait une copie de la variable PATH de l'environnement
* @env: Tableau de variables d'environnement
*
* Return: Copie allouée dynamiquement de la variable PATH ou NULL
*/

char *get_path_copy(char **env) /*Cherche et copie PATH*/
{
char *path_env = NULL; /*Contient chemin trouvé*/

int i; /*Compteur de boucle*/

for (i = 0; env[i] != NULL; i++) /*Parcours tableau env*/
{
if (strncmp(env[i], "PATH=", 5) == 0) /*Si "PATH", copie*/
{
path_env = strdup(env[i] + 5);
break;
}
}
return (path_env); /*Retourne copie*/
}

/**
* find_command_path - Cherche le chemin absolu d'une commande
* @cmd: Commande à localiser
* @env: Environnement
*
* Return: Chemin complet (malloc) ou NULL si non trouvé
*/

char *find_command_path(char *cmd, char **env) /*Cherche chemin cmd dans path*/
{
char *path_env = NULL, *path_copy = NULL; /*Stock copie path*/

	/*Chemin parcouru*/
	char *token = NULL, *full_path = NULL; /*Chaque dossier de path*/

	/*Vérifie fichier*/
	struct stat st;

	/*Libère*/
	path_env = get_path_copy(env);
	if (!path_env)
		return (NULL);

	path_copy = strdup(path_env);
	free(path_env);
	if (!path_copy)
		return (NULL);

	/*Dossier séparés*/
	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		/*Créer de la place*/
		full_path = malloc(strlen(token) + strlen(cmd) + 2);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}

		/*Chemin complet*/
		sprintf(full_path, "%s/%s", token, cmd);

		/*Si fichier existe*/
		/*Si fichier executable*/
		if (stat(full_path, &st) == 0 && is_executable(full_path))
		{
			/*Oui = Retourne chemin*/
			free(path_copy);
			return (full_path);
		}
		/*Non = retourne NULL*/
		free(full_path);
		token = strtok(NULL, ":");
	}

	/*Retourne NULL si aucun chemin ne marche*/
	free(path_copy);
	return (NULL);
}

/**
* is_executable - Vérifie si un fichier est exécutable
* @full_path: Chemin à tester
*
* Return: 1 si le fichier existe et est exécutable, 0 sinon
*/

/*Verifie si peut etre exécuté*/
int is_executable(char *full_path)
{
	/*Si fichier existe F_OK*/
	/*Si fichier executable X_OK*/
	if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
		/*Vrai*/
		return (1);
	/*Faux*/
	return (0);
}

