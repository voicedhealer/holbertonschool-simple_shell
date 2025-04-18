#include "shell.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * main - Point d’entrée du shell
 * @ac: nombre d'arguments (non utilisé)
 * @av: tableau d'arguments (non utilisé)
 * @env: tableau des variables d’environnement
 *
 * Return: 0 à la fin
 */

char *PROGRAM_NAME = NULL; /* Pour afficher ./hsh dans les erreurs */

int main(int ac, char **av, char **env)
{
    char *line = NULL;
    char **argv = NULL;

    (void)ac;
    (void)av;
    PROGRAM_NAME = av[0]; /* Garde ./hsh pour les messages d'erreur */

    while (1)
    {
        prompt_display();
        line = read_input(); /* lit ligne */
        if (!line) /* Ctrl+D */
            break;

        line = trim_newline(line); /* supprime \n */

        if (is_line_empty(line))
        {
            free(line);
            continue;
        }

        argv = parse_line(line); /* découpe mots */
        if (!argv || !argv[0])
        {
            free(line);
            free_tokens(argv); /* toujours libérer même si NULL */
            continue;
        }

        /* Vérifier si la commande est 'open_terminal' */
        if (strcmp(argv[0], "open_terminal") == 0)
        {
            /* Lancer un nouveau terminal avec le shell 'hsh' dans cette fenêtre */
            system("xterm -e ./hsh &");
        }
        else if (is_builtin(argv[0]))
        {
            handle_builtin(argv, env);
        }
        else
        {
            execute_command(argv, env);
        }

        free(line);
        free_tokens(argv);
    }

    free(line);
    return (0);
}

/**
 * prompt_display - Affiche le prompt "*** " si shell interactif
 */
void prompt_display(void)
{
    if (isatty(STDIN_FILENO))
        write(STDOUT_FILENO, "*** ", 4); /* 4 car "*** " = 4 caractères */
}
