/*
** s_history.c for 42 in /home/thomas_1//Projets/42.sh/42/src/lib
** 
** Made by pierre-yves thomas
** Login   <thomas_1@epitech.net>
** 
** Started on  Wed May 15 18:36:34 2013 pierre-yves thomas
** Last update Fri May 17 17:37:25 2013 pierre-yves thomas
*/

#include <stdlib.h>
#include <stdio.h>
#include "history.h"
#include "string.h"

void			retain_history(int opt, t_history **list)
{
  static t_history	*save = NULL;

  if (opt == 1)
    save = (*list);
  else
    (*list) = save;
}

void            my_put_in_history(t_history **list, char *str)
{
  t_history	*tmp;

  tmp = malloc(sizeof(*tmp));
  if (tmp != NULL)
    {
      tmp->str = my_strdup(str);
      tmp->next = (*list);
      if (*list != NULL)
        (*list)->prev = tmp;
      (*list) = tmp;
    }
}

void            my_show_history(t_history *list)
{
  t_history	*tmp;

  tmp = list;
  while (tmp != NULL)
    {
      printf("%s", tmp->str);
      if (tmp->next != NULL)
        printf(" -> ");
      tmp = tmp->next;
    }
  printf("\n");
}

int             length_of_history(t_history *list)
{
  int           len;
  t_history	*tmp;

  len = 0;
  tmp = list;
  while (tmp != NULL)
    {
      len++;
      tmp = tmp->next;
    }
  return (len);
}

void            free_history(t_history *list)
{
  t_history	*tmp;
  t_history	*after;

  tmp = list;
  after = list;
  while (tmp != NULL)
    {
      after = after->next;
      free(tmp->str);
      free(tmp);
      tmp = after;
    }
}
