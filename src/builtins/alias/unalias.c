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
