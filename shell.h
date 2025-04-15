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

/* main.c */
int main(int ac, char **av, char **env);

#endif /* SHELL_H */