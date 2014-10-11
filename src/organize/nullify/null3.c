/*
** null3.c for  in /home/collio_v/rendu_svn/42.sh/42/src
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Sun May 26 10:45:49 2013 vincent colliot
** Last update Sun May 26 10:46:27 2013 vincent colliot
*/

#include <stdlib.h>
#include "orga.h"
#include "lexec.h"
#include "bool.h"

BOOL	nullify_all_exec(t_exec *exec)
{
  t_exec	*next;

  if (!exec)
    return (FALSE);
  next = exec->next;
  if (exec->pipes)
    nullify_all_pipes(exec->pipes);
  else
    nullify_words(exec->tmp);
  free(exec);
  nullify_all_exec(next);
  return (FALSE);
}

void	rm_words(t_get *w)
{
  free(w->word);
  free(w);
}
