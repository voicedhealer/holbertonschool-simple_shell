#include "shell.h"

/*Fonction qui vérifie si le fichier est exécutable*/
int is_executable(char *full_path)
{
/**On utilise la fonction access() pour vérifier si le fichier existe ET si on peut l'exécuter.
* access(full_path, F_OK) -> vérifie si le fichier existe, F_OK vérifie la présence du fichier.
* access(full_path, X_OK) -> vérifie si le fichier est exécutable, X_OK vérifie les permissions d'exécution.
*/

	/*Si les deux conditions sont vraies (fichier existe ET est exécutable)*/
	if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
	{
	/*Si c'est le cas, on retourne 1 (indiquant que le fichier est exécutable)*/
		return (1);
	}
	else
	{
	/*Sinon, on retourne 0*/
		return (0);
	}
}
