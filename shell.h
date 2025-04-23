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
/* 🌍 Accès aux variables d'env  */
/* ----------------------------- */
extern char **environ;
extern char *PROGRAM_NAME;
extern char *line;
extern char **argv;

/* -------- main.c -------- */
/**
 * main - Fonction principale du shell
 * @ac: nombre d'arguments
 * @av: tableau d'arguments
 * @env: environnement
 * Return: 0 à la fin
 */
int main(int ac, char **av, char **env);

/**
 * prompt_display - Affiche le prompt si shell interactif
 */
void prompt_display(void);

/**
 * main_loop - Boucle principale d'exécution
 * @env: environnement
 */
void main_loop(char **env);

/* -------- input.c -------- */
/**
 * read_input - Lit une ligne entrée par l'utilisateur
 * Return: pointeur vers la ligne lue
 */
char *read_input(void);

/**
 * trim_newline - Supprime le retour à la ligne
 * @line: chaîne d'entrée
 * Return: chaîne modifiée
 */
char *trim_newline(char *line);

/**
 * is_line_empty - Vérifie si la ligne est vide/blanche
 * @line: ligne à tester
 * Return: 1 si vide, sinon 0
 */
int is_line_empty(char *line);

/* -------- parser.c -------- */
/**
 * parse_line - Découpe la ligne en tokens
 * @line: chaîne à découper
 * Return: tableau de tokens (argv)
 */
char **parse_line(char *line);

/**
 * free_tokens - Libère un tableau de tokens
 * @tokens: tableau à libérer
 */
void free_tokens(char **tokens);

/* -------- builtins.c -------- */
/**
 * is_builtin - Vérifie si une commande est un builtin
 * @cmd: commande à tester
 * Return: 1 si builtin, 0 sinon
 */
int is_builtin(char *cmd);

/**
 * handle_builtin - Exécute les commandes builtin
 * @argv: arguments
 * @env: environnement
 * Return: 1 si builtin exécuté, 0 sinon
 */
int handle_builtin(char **argv, char **env);

/* -------- executor.c -------- */
/**
 * execute_command - Exécute une commande
 * @argv: tableau d'arguments
 * @env: environnement
 * Return: 0 si succès, 127 si erreur
 */
int execute_command(char **argv, char **env);

/* -------- path_utils.c -------- */
/**
 * find_command_path - Cherche une commande dans $PATH
 * @cmd: commande à chercher
 * @env: environnement
 * Return: chemin complet si trouvé, sinon NULL
 */
char *find_command_path(char *cmd, char **env);

/**
 * is_executable - Vérifie si un chemin est exécutable
 * @full_path: chemin à tester
 * Return: 1 si exécutable, 0 sinon
 */
int is_executable(char *full_path);

#endif /* SHELL_H */
