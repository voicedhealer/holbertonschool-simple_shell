<h1 align="center">
  <span style="color:white;"><strong>SIMPLE SHELL</strong></span>
</h1>

  <h2 align="left">
  <span style="color:white;"><strong>Description</strong></span>
</h2>

This project is a simple version of a UNIX command-line interpreter, also called a shell.

- It lets the user type and run commands, just like in the Bash terminal.

- It supports basic features like:

    -> Running commands (like ls, pwd, echo, etc.)

    -> It finds the correct path of the command using the PATH variable

    -> Creates a child process to run the command

    -> Shows the result in the terminal (standard output).



<span style="font-size:18px"><strong><u>It works in a loop 🔁 :</u></strong></span>

1. Show a prompt (like $)

2. Wait for the user to type a command

3. Run the command

4. Go to step 1

---

 <h3 align="blue">
  <span style="color:white;"><strong>Compilation 🛠️</strong></span>
</h3>



<mark>To compile the shell, use this command :</mark>


gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh


---
<h3 align="left">
  <span style="color:white;"><strong>📋 Requirements  </strong></span>
</h3>

<u><strong>This shell was developed and tested with the following configurations :</strong></u>

- <strong><u>System:</u></strong> Ubuntu 20.04 LTS  
- <strong><u>Compilator:</u></strong> <code>gcc</code> version 9 or superior  
- <strong><u>Norms:</u></strong> The code follows the imposed standards, without using prohibited functions, unless stated otherwise
- <strong><u>Git :</u></strong> Version 2.25 or superior recommended 


⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️
- <strong><u>Betty Style</u></strong>
- <strong><u>No more than 5 functions per file</u></strong>
- <strong><u>Valgrind:</u></strong> for memory leaks
- <strong><u>All your header files should be include guarded
</u></strong> 
- <strong><u>Use system calls only when you need to:</u></strong> because system calls are expensive due to context switching, kernel mode execution, data copying, and synchronization overhead.
 
---

<h3 align="left">
  <span style="color:white;"><strong>man page</strong></span>
</h3>

<mark>To display the manpage :<mark/>

 man ./man_1_simple_shell

---

<h3 align="left">
  <span style="color:white;"><strong>How to use the Shell</strong></span>
</h3>

<mark>Direct execution :</mark>

echo "echo Hello" | ./hsh

<mark>To test the script :</mark>

cat test_commands.txt | ./hsh

<mark>For Valgrind :</mark>

valgrind --leak-check=full  ./hsh

---
🗂️ Liste des fichiers

Les fichiers suivants composent l’architecture de notre shell :

    main.c : Point d'entrée du programme

    input.c : Lecture de la ligne de commande depuis l’entrée standard

    parser.c : Découpage (tokenization) de la ligne en commandes + arguments

    executor.c : Exécution des commandes (fork, execve, gestion du PATH)

    builtins.c : Gestion des commandes internes (exit, env, etc.)

    path_utils.c : Recherche de la commande dans les chemins du PATH

    globals.c : Déclaration des variables globales (line, argv, etc.)

    shell.h : Fichier d’en-tête avec les prototypes et macros nécessaires

    README.md : Documentation du projet

    AUTHORS : Liste des auteurs du projet

    man_1_simple_shell : Page de manuel (commande man)


![FlowChartShell drawio](https://github.com/user-attachments/assets/20b5b1dd-3632-4d3b-97ae-d69b28351a32)


✍️ Auteurs

Voir fichier AUTHORS