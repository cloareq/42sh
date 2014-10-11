/*
** take_cmd_from_history.c for 42 in /home/thomas_1//Projets/42sh/src
** 
** Made by pierre-yves thomas
** Login   <thomas_1@epitech.net>
** 
** Started on  Fri May 10 14:24:48 2013 pierre-yves thomas
** Last update Tue May 21 12:16:42 2013 pierre-yves thomas
*/

#include <stdlib.h>
#include "string.h"
#include "edit_line.h"

int	take_cmd_from_history(int history_pl, int *rev_c,
			      char **cmd, t_history *history)
{
  int	i;

  i = 0;
  if (history_pl == 0)
    (*cmd) = my_memset(*cmd, 0, my_strlen(*cmd));
  else
    {
      while (++i < history_pl)
	history = history->next;
      free(*cmd);
      if (((*cmd) =
	   my_strndup(history->str, my_strlen(history->str) + 1)) == NULL)
	return (-1);
    }
  (*rev_c) = my_strlen(*cmd);
  return (0);
}
