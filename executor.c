#include "shell.h"


int execute_command(char **argv, char **env)
{
/*Pour stocker le résultat de fork()*/
pid_t pid;

/* Pour récupérer le code de retour du processus fils*/
int status;

/* Pour stocker le chemin complet de la commande*/
char *cmd_path;

if (argv == NULL || argv[0] == NULL)
return (-1);  /*Pas de commande à exécuter*/

cmd_path = find_command_path(argv[0], env);
if (cmd_path == NULL || !is_executable(cmd_path))
{
	fprintf(stderr, "%s: command not found\n", argv[0]);
	if (cmd_path)
		free(cmd_path);
	return (127);  /*Code d'erreur standard pour commande non trouvée*/
}

pid = fork();
if (pid < 0)
{
	perror("fork");
	free(cmd_path);
return (-1);  /*Erreur lors du fork*/
}

if (pid == 0)
{
	if (execve(cmd_path, argv, env) == -1)
{
		perror("execve");
		free(cmd_path);
		exit(126);  /*Erreur d'exécution*/
}
}
waitpid(pid, &status, 0);

free(cmd_path);
return (0);
}
