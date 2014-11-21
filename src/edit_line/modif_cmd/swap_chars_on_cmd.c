/*
** swap_chars_on_cmd.c for cmd in /home/thomas_1//Projets/42sh/src
** 
** Made by pierre-yves thomas
** Login   <thomas_1@epitech.net>
** 
** Started on  Fri May 10 19:29:30 2013 pierre-yves thomas
** Last update Fri May 17 18:01:03 2013 pierre-yves thomas
*/

#include "string.h"
#include "edit_line.h"

void    swap_chars_on_cmd(char value, int *reverse_case, char **cmd)
{
  char	reserve;
  int	len;
  int	i;

  (void)value;
  i = 0;
  len = my_strlen(*cmd);
  if (*reverse_case == len)
    i--;
  if (*reverse_case > 0)
    {
      reserve = (*cmd)[(*reverse_case) + (i - 1)];
      (*cmd)[(*reverse_case) + (i - 1)] = (*cmd)[(*reverse_case) + i];
      (*cmd)[(*reverse_case) + i] = reserve;
      if (*reverse_case != len)
	(*reverse_case)++;
    }
}
