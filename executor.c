#include "shell.h"

/*
* Exécute une commande avec ses arguments et l'environnement.
* Retourne le code de sortie du processus enfant, ou -1 en cas d'erreur.
*/
int execute_command(char **argv, char **env) {

	pid_t pid;
	int status;

	/* 1. Vérifie si la commande existe (si le premier argument existe) */
	if (argv == NULL || argv[0] == NULL)
		return (-1); /* Rien à exécuter */

	/* 2. Crée un processus enfant */
	pid = fork();
	if (pid < 0) {
		/* Erreur lors du fork */
		perror("fork");
		return (-1);
	}
	else if (pid == 0) {
		/* 3. Code exécuté par le processus enfant : exécute la commande */
		if (execve(argv[0], argv, env) == -1) {
			perror("execve");
			_exit(1); /* Termine le processus enfant en cas d'erreur */
		}
	}
	else {
		/* 4. Code exécuté par le parent : attend la fin de l'enfant */
		if (waitpid(pid, &status, 0) == -1) {
			perror("waitpid");
			return (-1);
		}
	}

	/* 5. Retourne le code de retour du processus enfant */
	return (WIFEXITED(status) ? WEXITSTATUS(status) : -1);
}
