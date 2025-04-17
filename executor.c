#include "shell.h"
/**
 * execute_command - Exécute une commande en utilisant fork et execve.
 * @argv : Tableau d'arguments.
 * @env : Tableau de variables d'environnement.
 * @return : Retourne le statut de l'exécution de la commande.
 */
int execute_command(char **argv, char **env)
{
    pid_t pid;
    int status;

    if (argv == NULL || argv[0] == NULL)
        return 1;

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // Enfant
        if (execve(argv[0], argv, env) == -1) {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent
        waitpid(pid, &status, 0);
    }

    return WEXITSTATUS(status);
}