#include "shell.h"
/**
 * find_command_path - Cherche le chemin d'une commande dans $PATH
 * @cmd: Commande à chercher
 * @env: Tableau de variables d'environnement
 *
 * Return: Chemin complet de la commande ou NULL
 */
char *find_command_path(char *cmd, char **env)
{
    char *path_env = NULL, *path_copy = NULL;
    char *token = NULL, *full_path = NULL;
    struct stat st;
    int i;
    /* Trouver la variable PATH dans l'environnement */
    for (i = 0; env[i] != NULL; i++)
    {
        if (strncmp(env[i], "PATH=", 5) == 0)
        {
            path_env = env[i] + 5;
            break;
        }
    }
    if (path_env == NULL)
        return (NULL);
    path_copy = strdup(path_env);
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

/*Fonction qui vérifie si le fichier est exécutable*/
int is_executable(char *full_path)
{
/**On utilise la fonction access() pour vérifier si le fichier existe ET si on peut l'exécuter.
* access(full_path, F_OK) -> vérifie si le fichier existe, F_OK vérifie la présence du fichier.
* access(full_path, X_OK) -> vérifie si le fichier est exécutable, X_OK vérifie les permissions d'exécution.
*/

	/*Si les deux conditions sont vraies (fichier existe ET est exécutable)*/
	if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
	{
	/*Si c'est le cas, on retourne 1 (indiquant que le fichier est exécutable)*/
		return (1);
	}
	else
	{
	/*Sinon, on retourne 0*/
		return (0);
	}
}
