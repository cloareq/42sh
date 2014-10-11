/*
** alias.c for alias.c in /home/cloare_q//test/42.sh/42/src/builtins
**
** Made by quentin cloarec
** Login   <cloare_q@epitech.net>
**
** Started on  Mon May 13 15:24:37 2013 quentin cloarec
** Last update Sat May 18 01:16:49 2013 vincent colliot
*/

#include "alias.h"

void	show_list(t_alias *alias)
{
  t_words *tmp;

  tmp = alias;
  while (tmp != NULL)
    {
      my_putstr(alias->cmd);
      my_putstr(alias->option);
      tmp = tmp->next;
    }
}

void	my_put_end(t_alias **alias, char *cmd, char *option)
{
  t_alias *elem;
  t_alias *tmp;

  elem = xmalloc(sizeof(elem));
  elem->cmd = cmd;
  elem->option = option;
  elem->next = NULL;
  if (*alias == NULL)
    *alias = elem;
  else
    {
      tmp = *alias;
      while (tmp->next != NULL)
	tmp = tmp->next;
      tmp->next = elem;
    }
}

int	nb_alias(t_words *cmd)
{
  t_words *tmp;
  int	i;

  tmp = cmd;
  i = 0;
  while (tmp != NULL)
    {
      i++;
      tmp = tmp->next;
    }
  return (i);
}

int	my_alias(t_words *cmd, t_alias **alias)
{
  char	*c;
  char *o;
  int	nb;

  nb = 0;
  //  verif_alias_loop(alias); no need anymore
  cmd = cmd->next;
  if ((nb = nb_alias(cmd)) == 1)
    show_list(alias);
  else if ((nb = nb_alias(cmd) == 2) || (nb = nb_alias(cmd) > 3))
    {
      print_err("WRONG ARGUMENTS TO ALIAS\n");
      return (EXIT_FAILURE);
    }
  else if ((nb = nb_alias(cmd) == 3))
    {
      if ((c = xmalloc(sizeof(char) * (my_strlen(cmd->word) + 1))) == NULL)
	return (EXIT_FAILURE);
      c = cmd->words;
      cmd = cmd->next;
      if ((o = xmalloc(sizeof(char) * (my_strlen(cmd->word)+ 1))) == NULL)
	return (EXIT_FAILURE);
      o = cmd->words;
      my_put_end(alias, c, o);
    }
}
