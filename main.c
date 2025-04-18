#include "shell.h"

/**  
* main - Point d'entrée de notre shell (./hsh)
* @ac: nombre d'arguments (non utilisé ici)
* @av: tableau des arguments (non utilisé ici)
* @env: tableau des variables d'environnement (utilisé pour execve et env)
*
*Return: 0 à la fin du programme
*/
int main(int ac, char **av, char **env)
{
    char *line = NULL;
    char **argv = NULL;

    (void)ac;
    (void)av;
    
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

        if (is_builtin(argv[0]))
            handle_builtin(argv, env);
        else
            execute_command(argv, env);

        free(line);
        free_tokens(argv);
    }

    free(line);
    return (0);
}


/**
 * prompt_display - Affiche le prompt "*** " si le shell est en mode interactif
 *
 * On utilise isatty(STDIN_FILENO) pour savoir si l'utilisateur tape en direct
 * (et pas via un script comme echo "ls" | ./hsh)
 */

void prompt_display(void)
{
    if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "*** ", 2); /*pas de printf car c'est plus lourd en memoire*/

	/* fflush(stdout); force l'affichage immédiat mais que pour prinf() puts() putchar() donc inutile ici*/
}
