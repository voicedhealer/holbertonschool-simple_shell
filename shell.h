#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

/* ----------------------------- */
/* 🌍 Accès aux variables d'env   */
/* ----------------------------- */
extern char **environ;
/*
 * Cette variable globale contient toutes les variables d’environnement
 * (ex: PATH, HOME, etc.). Elle est utilisée par execve() et pour afficher env.
 */


/* Prototypes ici */

/* -------- main.c -------- */
int main(int ac, char **av, char **env);   /* Fonction principale */
void prompt_display(void);                 /* Affiche le prompt "$ " */

/* -------- input.c -------- */
char *read_input(void);                    /* Lit une ligne avec getline */
char *trim_newline(char *line);            /* Supprime le \\n final */
int is_line_empty(char *line);             /* Vérifie si la ligne est vide ou blanche */

/* -------- parser.c -------- */
char **parse_line(char *line);             /* Découpe la ligne avec strtok en argv */
void free_tokens(char **tokens);           /* Libère argv[] */

/* -------- builtins.c -------- */
int is_builtin(char *cmd);                 /* Vérifie si c’est un builtin (exit/env) */
int handle_builtin(char **argv, char **env); /* Exécute les built-ins */

/* -------- executor.c -------- */
int execute_command(char **argv, char **env); /* fork + execve + wait */

/* -------- path_utils.c -------- */
char *find_command_path(char *cmd, char **env); /* Cherche le chemin d’une commande dans $PATH */
int is_executable(char *full_path);             /* Vérifie si un fichier est exécutable */

#endif /* SHELL_H */ /* Fin de la protection */
