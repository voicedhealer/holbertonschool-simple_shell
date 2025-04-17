#include "shell.h"
/**
 * is_builtin - Vérifie si la commande est une commande intégrée (exit, env).
 * @cmd : Commande à vérifier.
 *
 * Retour : 1 s'il s'agit d'une commande intégrée, 0 sinon.
 */
int is_builtin(char *cmd) {
    if (cmd == NULL)
        return 0;

    if (strcmp(cmd, "exit") == 0 || strcmp(cmd, "env") == 0)
        return 1;

    return 0;
}
/**
 * handle_builtin - Gère les commandes intégrées (exit, env).
 * @argv : Tableau d'arguments.
 * @env : Tableau de variables d'environnement.
 *
 * Retour : 1 si une commande intégrée a été exécutée, 0 sinon.
 */

int handle_builtin(char **argv, char **env) {
    if (argv == NULL || argv[0] == NULL)
        return 1;

    if (strcmp(argv[0], "exit") == 0) {
        if (argv[1] != NULL) {
            int status = atoi(argv[1]);
            exit(status);
        } else {
            exit(0);
        }
    } else if (strcmp(argv[0], "env") == 0) {
        for (int i = 0; env[i] != NULL; i++) {
            printf("%s\n", env[i]);
        }
        return 1;
    }
    return 0;
}


