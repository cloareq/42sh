/*
** unalias.c for  in /home/lecorr_b//projets/42sh/42.sh/42/src/builtins/alias
**
** Made by thomas lecorre
** Login   <lecorr_b@epitech.net>
**
** Started on  Mon May 20 16:59:00 2013 thomas lecorre
** Last update Mon May 20 17:39:56 2013 vincent colliot
*/

#include "string.h"
#include "built.h"

int	rm_alias(t_words *cmd, t_alias *link, t_alias **alias)
{
  if (!cmd)
    return (0);
  if (!link)
    return (rm_alias(cmd->next, *alias, alias));
  if (!MATCH(cmd->word, link->name))
    return (rm_alias(cmd, link->next, alias));
  if (link->prev)
    link->prev->next = link->next;
  else
    *alias = link->next;
  if (link->next)
    link->next->prev = link->prev;
  free(link->name);
  free(link->fill);
  free(link);
  return (rm_alias(cmd->next, *alias, alias));
}

int	built_unalias(t_words *cmd, void  *alias)
{
  if (!cmd->next)
    {
      print_err("unalias: too few arguments.\n");
      return (EXIT_FAILURE);
    }
  rm_alias(cmd->next, *(t_alias**)alias, alias);
  return (EXIT_SUCCESS);
}
