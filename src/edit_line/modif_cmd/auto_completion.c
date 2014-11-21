/*
** auto_completion.c for 42 in /home/thomas_1//Projets/42.sh/42/src/edit_line/modif_cmd
**
** Made by pierre-yves thomas
** Login   <thomas_1@epitech.net>
**
** Started on  Sun May 26 11:09:19 2013 pierre-yves thomas
** Last update Sun May 26 12:19:32 2013 vincent colliot
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include "string.h"
#include "edit_line.h"
#include "prompt.h"

static void print_complo(char *dir, char *match)
{
  struct dirent *fchr;
  DIR	*d;

  if ((d = opendir(dir)) == NULL)
    return ;
  while ((fchr = readdir(d)) != NULL)
    if (!match || NMATCH(match, fchr->d_name))
      printf("%s\n", fchr->d_name);
  closedir(d);
}

void	auto_completion(char value, int *rev_c, char **cmd)
{
  char  *dir;
  char	*s;

  (void)value;
  s = my_strndup(*cmd + lastoccur_bf(*cmd, ' ', *rev_c) +
		 ((*cmd)[lastoccur_bf(*cmd, ' ', *rev_c)] == ' '), *rev_c -
		 lastoccur_bf(*cmd, ' ', *rev_c));
  if (!s || empty(s))
    dir = (s = NULL);
  else
    dir = my_strndup(s, lastoccur_bf(s, '/', my_strlen(s)) +
		     IN('/', s));
  go_down_of_cmd_high(*cmd);
  printf("\n");
  if (dir)
    print_complo(dir, s + IN('/', s) * (lastoccur_bf(s, '/',
						     my_strlen(s)) + 1));
  else
    print_complo(".", s);
  if (dir)
    free(dir);
  prompt(TRUE);
}

