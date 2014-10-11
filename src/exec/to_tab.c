/*
** to_tab.c for  in /home/collio_v/rendu_svn/42.sh/42/src
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Sun May 26 10:22:33 2013 vincent colliot
** Last update Sun May 26 10:56:11 2013 vincent colliot
*/

#include "lexec.h"
#include "string.h"
#include "xmalloc.h"

static size_t	size_list(t_words *list)
{
  size_t	i;

  i = 0;
  while (list)
    {
      i++;
      list = list->next;
    }
  return (i);
}

char	**to_tab(t_words *list, BOOL *sys_fail)
{
  char		**tab;
  size_t	i;

  i = size_list(list);
  if ((tab = xmalloc(sizeof(*tab) * (i + 1))) == NULL)
    {
      (*sys_fail) = TRUE;
      return (NULL);
    }
  i = 0;
  while (list)
    {
      tab[i] = list->word;
      list = list->next;
      i++;
    }
  tab[i] = NULL;
  return (tab);
}
