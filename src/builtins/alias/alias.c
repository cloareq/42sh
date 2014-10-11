/*
** alias.c<2> for  in /home/collio_v/rendu_svn/42.sh/42/src
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Sat May 18 01:19:45 2013 vincent colliot
** Last update Mon May 20 16:52:00 2013 vincent colliot
*/

#include "alias.h"
#include "string.h"
#include "orga.h"
#include "built.h"
#include "error.h"

static int p_one(t_alias *alias)
{
  if (!alias)
    return (EXIT_FAILURE);
  my_putstr("alias ", 1);
  my_putstr(alias->name, 1);
  my_putstr("=\"", 1);
  my_putstr(alias->fill, 1);
  my_putstr("\"\n", 1);
  return (EXIT_SUCCESS);
}

static BOOL valid_str(char *s)
{
  if (s[my_sstrlen(s, " \\\t\"'|;<>()`")] != 0)
    {
      print_err(INVALID_ALIAS);
      print_err(s);
      print_err("\n");
      return (FALSE);
    }
  return (TRUE);
}

static int get_n(t_words *cmd, t_alias *alias, t_alias **mod)
{
  t_alias	*pnew;

  pnew = NULL;
  while (alias)
    {
      if (MATCH(cmd->word, alias->name))
	pnew = alias;
      alias = alias->next;
    }
  if (!cmd->next)
    return (p_one(pnew));
  if (valid_str(cmd->word) == FALSE)
    return (EXIT_FAILURE);
  if (!pnew)
    return (mod_alias(cmd->word, cmd->next->word, mod));
  free(pnew->fill);
  if ((pnew->fill = my_strdup(cmd->next->word)) == NULL)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

static int print(t_alias *alias)
{
  if (!alias)
    return (EXIT_SUCCESS);
  p_one(alias);
  return (print(alias->next));
}

int	built_alias(t_words *cmd, void *alias)
{
  if (!cmd->next)
    return (print(*(t_alias**)alias));
  return (get_n(cmd->next, *(t_alias**)alias, alias));
}
