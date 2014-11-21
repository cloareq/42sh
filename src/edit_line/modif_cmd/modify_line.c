/*
** modify_line.c for 42sh in /home/thomas_1//Projets/42sh/src
**
** Made by pierre-yves thomas
** Login   <thomas_1@epitech.net>
**
** Started on  Mon May  6 17:44:08 2013 pierre-yves thomas
** Last update Sun May 26 11:14:23 2013 pierre-yves thomas
*/

#include <stdlib.h>
#include "string.h"
#include "edit_line.h"
#include "prompt.h"

int    add_letter_in_str(char value, int *reverse_case, char **cmd)
{
  int   len;

  len = my_strlen(*cmd) + 1;
  while (--len > (*reverse_case))
    (*cmd)[len + 1] = (*cmd)[len];
  if (my_strlen(*cmd) + 1 > 1)
    (*cmd)[len + 1] = (*cmd)[len];
  (*cmd)[len] = value;
  (*reverse_case)++;
  if (((*cmd) = my_realloc(*cmd,
			   my_strlen(*cmd), my_strlen(*cmd) + 2)) == NULL)
    return (-1);
  (*cmd)[my_strlen(*cmd) + 1] = '\0';
  return (0);
}

void    del_letter_in_str(char value, int *reverse_case, char **cmd)
{
  int   suppr;

  (void)value;
  suppr = (*reverse_case) - 1;
  if ((*reverse_case) > 0)
    {
      while ((*cmd)[suppr] != '\0')
        {
          (*cmd)[suppr] = (*cmd)[suppr + 1];
          suppr++;
        }
      my_putstr("\r", 1);
      (*reverse_case)--;
    }
}

static void	fill_fct_ptr(void (*options[15])(char, int *, char **))
{
  (options)[0] = move_reverse_case;
  (options)[1] = del_letter_in_str;
  (options)[2] = clean_screen;
  (options)[3] = reverse_to_begin;
  (options)[4] = reverse_to_end;
  (options)[5] = del_after_cursor;
  (options)[6] = copy_part_str;
  (options)[7] = clean_str;
  (options)[8] = move_reverse_case;
  (options)[9] = move_reverse_case;
  (options)[10] = del_before_cursor;
  (options)[11] = swap_chars_on_cmd;
  (options)[12] = del_letter_in_str;
  (options)[13] = auto_completion;
  (options)[14] = NULL;
}

static void fill_tab(char opt[14])
{
  opt[0] = 27;
  opt[1] = 127;
  opt[2] = 12;
  opt[3] = 1;
  opt[4] = 5;
  opt[5] = 11;
  opt[6] = 25;
  opt[7] = 21;
  opt[8] = 2;
  opt[9] = 6;
  opt[10] = 23;
  opt[11] = 20;
  opt[12] = 8;
  opt[13] = 9;
}

int		modif_cmd(char **cmd, char *str, int *reverse_case)
{
  int		i;
  void		(*options[15])(char, int *, char **);
  char		opt[14];

  i = -1;
  fill_tab(opt);
  fill_fct_ptr(options);
  while (++i < 14 && opt[i] != str[0]);
  if (i != 14)
    if (i == 0 && str[2] == 0)
      (options[i])(str[1], reverse_case, cmd);
    else if (i == 8 || i == 9 || i == 13)
      (options[i])(str[0], reverse_case, cmd);
    else
      (options[i])(str[2], reverse_case, cmd);
  else
    {
      i = -1;
      while (++i < 4 && str[i] >= ' ')
	if (add_letter_in_str(str[i], reverse_case, cmd) == -1)
	  return (-1);
    }
  return (0);
}
