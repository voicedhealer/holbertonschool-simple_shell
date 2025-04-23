#include "shell.h"

/**
 * get_path_copy - Extrait une copie de la variable PATH de l'environnement
 * @env: Tableau de variables d'environnement
 *
 * Return: Copie allouée dynamiquement de la variable PATH ou NULL
 */
char *get_path_copy(char **env)
{
	char *path_env = NULL;
	int i;

	for (i = 0; env[i] != NULL; i++)
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
		{
			path_env = strdup(env[i] + 5);
			break;
		}
	}
	return (path_env);
}

/**
 * find_command_path - Cherche le chemin absolu d'une commande
 * @cmd: Commande à localiser
 * @env: Environnement
 *
 * Return: Chemin complet (malloc) ou NULL si non trouvé
 */
char *find_command_path(char *cmd, char **env)
{
	char *path_env = NULL, *path_copy = NULL;
	char *token = NULL, *full_path = NULL;
	struct stat st;

	path_env = get_path_copy(env);
	if (!path_env)
		return (NULL);

	path_copy = strdup(path_env);
	free(path_env);
	if (!path_copy)
		return (NULL);

	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		full_path = malloc(strlen(token) + strlen(cmd) + 2);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}

		sprintf(full_path, "%s/%s", token, cmd);
		if (stat(full_path, &st) == 0 && is_executable(full_path))
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

/**
 * is_executable - Vérifie si un fichier est exécutable
 * @full_path: Chemin à tester
 *
 * Return: 1 si le fichier existe et est exécutable, 0 sinon
 */
int is_executable(char *full_path)
{
	if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
		return (1);
	return (0);
}
