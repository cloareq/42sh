/*
** history.h for 42 in /home/thomas_1//Projets/42.sh/42/include
** 
** Made by pierre-yves thomas
** Login   <thomas_1@epitech.net>
** 
** Started on  Wed May 15 18:39:38 2013 pierre-yves thomas
** Last update Wed May 15 18:46:54 2013 pierre-yves thomas
*/

#ifndef HISTORY_H
# define HISTORY_H

typedef struct          s_history
{
  char                  *str;
  struct s_history      *prev;
  struct s_history      *next;
}                       t_history;

/*
** s_history.c
*/
void		retain_history(int, t_history **);
void            my_put_in_history(t_history **, char *);
void            my_show_history(t_history *);
int             length_of_history(t_history *);
void            free_history(t_history *);

# endif
