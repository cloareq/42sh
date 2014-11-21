/*
** match_them_help.c for  in /home/collio_v/rendu_svn/42.sh/42
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Wed May 22 03:06:49 2013 vincent colliot
** Last update Wed May 22 03:07:16 2013 vincent colliot
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include "orga.h"
#include "lexec.h"
#include "bool.h"
#include "string.h"
#include "xmalloc.h"
#include "error.h"

static BOOL	add(char *name, t_words **last, BOOL *no_match)
{
  t_words	*link;

  if (!name)
    return (FALSE);
  *no_match = FALSE;
  if ((link = xmalloc(sizeof(*link))) == NULL)
    return (FALSE);
  link->word = my_strdup(name);
  link->next = NULL;
  (*last)->next = link;
  *last = link;
  return (TRUE);
}

BOOL  add_and_last(char *m, char *dp, t_words **last, BOOL *no_match)
{
  char	*s;

  if (m[0] && (dp) != NULL)
    s = my_stricat(dp, m, '/');
  else if (dp != NULL)
    s = dp;
  else
    s = my_strdup(m);
  if (add(s, last, no_match) == FALSE)
    return (FALSE);
  if (dp)
    free(dp);
  if (m[0])
    free(s);
  return (TRUE);
}

