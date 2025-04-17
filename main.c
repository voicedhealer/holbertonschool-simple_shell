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
	char *line = NULL;     /* ligne tapée par l'utilisateur */
	char **argv = NULL;    /* tableau de mots (commande + arguments) */

	(void)ac; /* On ignore ac/av car on ne les utilise pas dans ce shell */
	(void)av;

	while (1)
    {

        prompt_display();
        line = read_input();    /* Lire une ligne tapée par l'utilisateur */
		if (!line)              /* Si Ctrl+D (getline retourne -1) */
			break;
            line = trim_newline(line);         /* Supprime le \n final */

		if (is_line_empty(line))           /* Si la ligne est vide ou remplie d'espaces */
		{
			free(line);
			continue;                      /* On retourne au prompt sans rien faire */
		}

        argv = parse_line(line);           /* Découpe la ligne en mots */
		if (!argv || !argv[0])             /* Si rien n’a été trouvé */
		{
			free(line);
			free_tokens(argv);
			continue;
		}

        if (is_builtin(argv[0]))           /* Si c’est une commande interne */
			handle_builtin(argv, env);     /* ex: exit, env */
		else
			execute_command(argv, env);    /* Sinon : fork + execve */

		free(line);       /* Libère la ligne allouée par getline */
		free_tokens(argv);/* Libère chaque mot alloué dans argv */

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

	/* fflush(stdout); force l'affichage immédiat */
}
