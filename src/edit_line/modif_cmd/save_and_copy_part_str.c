/*
** save_and_copy_part_str.c for 42 in /home/thomas_1//Projets/42sh/src
** 
** Made by pierre-yves thomas
** Login   <thomas_1@epitech.net>
** 
** Started on  Thu May  9 10:28:59 2013 pierre-yves thomas
** Last update Fri May 17 18:00:18 2013 pierre-yves thomas
*/

#include <stdlib.h>
#include "edit_line.h"
#include "string.h"

void		remind_save_str(int opt, char **str)
{
  static char	*save = NULL;

  if (opt == 1)
    {
      if (save != NULL)
	free(save);
      if (*str != NULL)
	save = my_strdup(*str);
      else
	save = NULL;
    }
  else if (opt == 2)
    (*str) = save;
}

void	del_after_cursor(char value, int *reverse_case, char **cmd)
{
  char	*tmp;
  int	len;

  (void)value;
  tmp = (*cmd) + (*reverse_case);
  remind_save_str(1, &tmp);
  len = (*reverse_case) + 1;
  while (len != (int)my_strlen(*cmd) + 1)
    {
      del_letter_in_str(0, &len, cmd);
      len = (*reverse_case) + 1;
    }
}

void	del_before_cursor(char value, int *reverse_case, char **cmd)
{
  char	*tmp;

  (void)value;
  tmp = my_strndup(*cmd, *reverse_case);
  remind_save_str(1, &tmp);
  free(tmp);
  while (*reverse_case > 0)
    del_letter_in_str(0, reverse_case, cmd);
}

void	copy_part_str(char value, int *reverse_case, char **cmd)
{
  char	*tmp;
  int	len;

  (void)value;
  tmp = NULL;
  remind_save_str(2, &tmp);
  len = -1;
  while (++len < (int)my_strlen(tmp))
    add_letter_in_str(tmp[len], reverse_case, cmd);
}
