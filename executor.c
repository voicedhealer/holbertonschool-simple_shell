#include "shell.h"

/**
 * resolve_command_path - Résout le chemin de la commande, absolu ou via PATH
 * @argv: Tableau des arguments de la commande
 * @env: Variables d'environnement pour la recherche dans PATH
 *
 * Return: Chemin complet de la commande (à libérer), ou NULL si non trouvée
 */
char *resolve_command_path(char **argv, char **env)
{
	char *cmd_path = NULL; /* Initialise le chemin à NULL */

	/* Vérifie si la commande contient un '/' (chemin absolu/relatif) */
	if (strchr(argv[0], '/'))
	{
		/* Teste si le fichier existe et est exécutable */
		if (access(argv[0], X_OK) == 0)
			cmd_path = strdup(argv[0]); /* Copie le chemin existant */
		else
			/* Affiche une erreur si le fichier est inaccessible */
			fprintf(stderr, "%s: 1: %s: not found\n", PROGRAM_NAME, argv[0]);
	}
	else
	{
		/* Recherche la commande dans les répertoires du PATH */
		cmd_path = find_command_path(argv[0], env);
		/* Gère le cas où la commande n'est trouvée nulle part */
		if (!cmd_path)
			fprintf(stderr, "%s: 1: %s: not found\n", PROGRAM_NAME, argv[0]);
	}

	return (cmd_path); /* Retourne le chemin ou NULL */
}

/**
 * execute_command - Exécute une commande donnée via fork + execve
 * @argv: Tableau de chaînes (commande + arguments)
 * @env: Variables d'environnement
 *
 * Return: 0 si succès, 127 si erreur/introuvable
 */
int execute_command(char **argv, char **env)
{
	pid_t pid; /* Stocke l'identifiant du processus */
	char *cmd_path = NULL; /* Chemin complet de la commande */

	/* 1. Résolution du chemin de la commande */
	cmd_path = resolve_command_path(argv, env);
	if (!cmd_path)
		return (127); /* Code d'erreur standard pour "command not found" */

	pid = fork(); /* 2. Création du processus fils */
	if (pid == -1) /* Gestion de l'échec du fork */
	{
		perror("fork");
		free(cmd_path);
		return (127);
	}
	else if (pid == 0) /* Processus fils */
	{
		execve(cmd_path, argv, env); /* 3. Exécution de la commande */
		perror(argv[0]); /*Si execve échoue (nous ne devrions jamais arriver ici)*/
		free(cmd_path);
		exit(1); /* Code d'erreur générique */
	}
	else /* Processus parent */
	{
		wait(NULL); /* 4. Attente de la fin du processus fils */
	}

	free(cmd_path); /* 5. Nettoyage final */
	return (0); /* Succès */
