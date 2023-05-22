#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
/**
 * struct pass - contient aregment to pass into function
 * @readf: the fd from which to read line input
 */
typedef struct pass
{
	int readf;
} pass_t;

/**
 * struct list_s - singly linked list
 * @str: string - (malloc'ed string)
 * @len: length of the string
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct list_s
{
	char *str;
	unsigned int len;
	struct list_s *next;
} list_t;
int _atoi(char *s);
int alpha(int s);
int _delim(char ch, char *d);
int shell_interactive(pass_t *f);
int err_atoi(char *c);
