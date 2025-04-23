#include "shell.h"

/**
 * parse_line - Splits a command line into tokens
 * @line: The input string to parse (command line)
 *
 * Tokenizes the input string using spaces
 * tabs, carriage returns, and newlines
 * as delimiters. Returns a dynamically allocated array of strings (char **),
 * where each element is a token from the input. The array is NULL-terminated.
 *
 * Return: On success - dynamically allocated array of tokens.
 *         On failure - NULL (invalid input or memory allocation error).
 *         Caller must free the result with free_tokens().
 */
char **parse_line(char *line)
{
	char **argv = NULL;   /* Array to store tokens */
	char *token = NULL;   /* Individual token */
	size_t argc = 0;      /* Token counter */
	size_t size = 8;      /* Initial array capacity */

	if (!line)
		return (NULL);

	/* Allocate initial token array */
	argv = malloc(size * sizeof(char *));
	if (!argv)
		return (NULL);

	/* Extract first token */
	token = strtok(line, " \t\r\n");

	while (token)
	{
		/* Store duplicated token */
		argv[argc] = strdup(token);
		if (!argv[argc])
		{
			free_tokens(argv);
			return (NULL);
		}
		argc++;

		/* Double array size if full */
		if (argc >= size)
		{
			size *= 2;
			argv = realloc(argv, size * sizeof(char *));
			if (!argv)
				return (NULL);
		}
		token = strtok(NULL, " \t\r\n");
	}

argv[argc] = NULL;
return (argv);
}

/**
 * free_tokens - Frees a NULL-terminated array of strings
 * @tokens: Array of strings to free
 *
 * Iterates through the array, freeing each string and finally
 * freeing the array itself. Handles NULL input gracefully.
 */
void free_tokens(char **tokens)
{
	size_t index;

if (!tokens)
return;

for (index = 0; tokens[index] != NULL; index++)
free(tokens[index]);

free(tokens);
}
