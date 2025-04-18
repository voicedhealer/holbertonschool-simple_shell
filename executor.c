#include "shell.h"


int execute_command(char **argv, char **env)
{
    pid_t pid;
    char *cmd_path = NULL;

    /* Si c’est une commande avec un chemin absolu ou relatif */
    if (strchr(argv[0], '/'))
    {
        if (access(argv[0], X_OK) == 0)
        {
            cmd_path = strdup(argv[0]);
            if (!cmd_path)
                return (127); /* erreur malloc */
        }
        else
        {
            perror(argv[0]);
            return (127);
        }
    }
    else
    {
        /* Sinon on cherche dans le PATH */
        cmd_path = find_command_path(argv[0], env);
        if (!cmd_path)
        {
            fprintf(stderr, "%s: command not found\n", argv[0]);
            /* ✅ Pas besoin de free ici car cmd_path = NULL */
            return (127);
        }
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        free(cmd_path); /* ✅ on libère si fork échoue */
        return (127);
    }
    else if (pid == 0)
    {
        execve(cmd_path, argv, env);
        perror(argv[0]);
        free(cmd_path); /* ✅ libère dans le fils si execve échoue */
        exit(1);
    }
    else
    {
        wait(NULL);
    }

    free(cmd_path); /* ✅ libère dans le parent après exécution */
    return (0);
}
