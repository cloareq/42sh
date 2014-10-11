/*
** mod_alias.c for  in /home/collio_v/rendu_svn/42.sh/42/src
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Sat May 18 02:19:51 2013 vincent colliot
** Last update Sun May 26 02:18:54 2013 vincent colliot
*/

#include "alias.h"
#include "string.h"
#include "xmalloc.h"

static int add_after(t_alias *put, t_alias *link)
{
  link->next = put->next;
  if (link->next)
    link->next->prev = link;
  link->prev = put;
  link->prev->next = link;
  return (EXIT_SUCCESS);
}

static int add_link(t_alias *link, char *a, t_alias **alias)
{
  t_alias *put;

  if (my_strcmp((*alias)->name, a) > 0)
    {
      link->next = *alias;
      (*alias)->prev = link;
      *alias = link;
      return (EXIT_SUCCESS);
    }
  put = *alias;
  while (put)
    {
      if (!put->next)
	return (add_after(put, link));
      else if (my_strcmp(put->next->name, a) > 0)
	return (add_after(put, link));
      put = put->next;
    }
  return (EXIT_SUCCESS);
}

int mod_alias(char *a, char *f, t_alias **alias)
{
  t_alias *link;

  if ((link = xmalloc(sizeof(*link))) == NULL)
    return (EXIT_FAILURE);
  if ((link->name = my_strdup(a)) == NULL)
    return (EXIT_FAILURE);
  if ((link->fill = my_strdup(f)) == NULL)
    return (EXIT_FAILURE);
  link->prev = NULL;
  link->next = NULL;
  if (*alias)
    return (add_link(link, a, alias));
  *alias = link;
  return (EXIT_SUCCESS);
}
