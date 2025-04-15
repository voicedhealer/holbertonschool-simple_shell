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

	
}