/*
** clear_screen.c for 42 in /home/thomas_1//Projets/42sh
** 
** Made by pierre-yves thomas
** Login   <thomas_1@epitech.net>
** 
** Started on  Thu May  9 11:20:06 2013 pierre-yves thomas
** Last update Tue May 21 21:30:19 2013 pierre-yves thomas
*/

#include "edit_line.h"
#include "string.h"
#include "prompt.h"

void    clean_screen(char value, int *reverse_case, char **cmd)
{
  t_options	tmp;

  retain_struct_options(2, &tmp);
  (void)value;
  (void)reverse_case;
  (void)cmd;
  my_putstr(tmp.clear, 1);
  prompt(TRUE);
}

void	clean_str(char value, int *reverse_case, char **cmd)
{
  (void)value;
  my_putstr("\r", 1);
  (*reverse_case) = 0;
  remind_save_str(1, cmd);
  (*cmd) = my_memset(*cmd, 0, my_strlen(*cmd));
}
