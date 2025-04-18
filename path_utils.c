#include "shell.h"
/**
 * find_command_path - Cherche le chemin d'une commande dans $PATH.
 * @cmd : Commande à chercher.
 * @env : Tableau de variables d'environnement.
 *
 * Retourne le chemin complet de la commande ou NULL si non trouvé.
 */
char *find_command_path(char *cmd, char **env)
{
    //char *path = NULL;
    char *full_path = NULL;
    char *path_env = NULL;
    char *token = NULL;
    struct stat st;

    /* Cherche la variable PATH dans l'environnement */
    for (int i = 0; env[i] != NULL; i++)
    {
        if (strncmp(env[i], "PATH=", 5) == 0)
        {
            path_env = env[i] + 5; /* Ignore "PATH=" */
            break;
        }
    }

    if (path_env == NULL)
        return (NULL); /* PATH non trouvé */

    /* Découpe le PATH en tokens */
    token = strtok(path_env, ":");
    while (token != NULL)
    {
        /* Construit le chemin complet */
        full_path = malloc(strlen(token) + strlen(cmd) + 2);
        if (full_path == NULL)
            return (NULL); /* Erreur d'allocation mémoire */

        sprintf(full_path, "%s/%s", token, cmd);

        /* Vérifie si le fichier est exécutable */
        if (stat(full_path, &st) == 0 && S_ISREG(st.st_mode) && is_executable(full_path))
            return (full_path); /* Chemin trouvé */

        free(full_path);
        token = strtok(NULL, ":");
    }

    return (NULL); /* Commande non trouvée */
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
