/*
** change_reverse_place.c for 42 in /home/thomas_1//Projets/42sh
**
** Made by pierre-yves thomas
** Login   <thomas_1@epitech.net>
**
** Started on  Thu May  9 11:30:50 2013 pierre-yves thomas
** Last update Sat May 25 17:34:44 2013 pierre-yves thomas
*/

#include <string.h>
#include <stdlib.h>
#include "string.h"
#include "edit_line.h"

void	delete_first_word_met(char value, int *rev_c, char **cmd)
{
  char	*save;
  int	i;
  int	save_rev_c;
  int	len;

  (void)value;
  len = my_strlen(*cmd) - 1;
  i = (*rev_c);
  while (i < len && ((*cmd)[i] == ' ' || (*cmd)[i] == '\t'))
    i++;
  while (i < len && ((*cmd)[i] != ' ' && (*cmd)[i] != '\t'))
    i++;
  if (i != len)
    i--;
  save_rev_c = (*rev_c) + 1;
  save = my_strndup((*cmd) + save_rev_c - 1, i + 2 - save_rev_c);
  remind_save_str(1, &save);
  free(save);
  while (save_rev_c < i + 2)
    {
      del_letter_in_str(0, &save_rev_c, cmd);
      save_rev_c = (*rev_c) + 1;
      i--;
    }
}

static void	fill_fct_ptr(void (*options[9])(char, int *, char **))
{
  options[0] = move_to_prev_word;
  options[1] = delete_first_word_met;
  options[2] = move_to_next_word;
  options[3] = uppercase_first_letter_found;
  options[4] = lowercase_letters_found;
  options[5] = reverse_to_begin;
  options[6] = reverse_to_end;
  options[7] = del_letter_in_str;
  options[8] = NULL;
}

static void	fill_tab(char opt[8])
{
  opt[0] = 98;
  opt[1] = 100;
  opt[2] = 102;
  opt[3] = 99;
  opt[4] = 108;
  opt[5] = 72;
  opt[6] = 70;
  opt[7] = 51;
}

void		move_reverse_case(char value, int *rev_c, char **cmd)
{
  void		(*options[9])(char, int *, char **);
  char		opt[8];
  int		len;
  int		i;

  i = -1;
  fill_tab(opt);
  len = my_strlen(*cmd);
  fill_fct_ptr(options);
  while (++i < 8 && opt[i] != value);
  if (i != 8)
    {
      if (value == 51)
	{
	  (*rev_c)++;
	  options[i](value, rev_c, cmd);
	}
      else
	options[i](value, rev_c, cmd);
    }
  else if ((value == 68 || value == 2) && (*rev_c) > 0)
    (*rev_c)--;
  else if ((value == 67 || value == 6) && (*rev_c) < len)
    (*rev_c)++;
}
