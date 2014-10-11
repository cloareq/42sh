/*
** finish_usr_cmd.c for 42 in /home/thomas_1//Projets/42.sh/42/src/edit_line/modif_cmd
** 
** Made by pierre-yves thomas
** Login   <thomas_1@epitech.net>
** 
** Started on  Sat May 25 18:08:34 2013 pierre-yves thomas
** Last update Sat May 25 18:21:44 2013 pierre-yves thomas
*/

#include <stdlib.h>
#include "string.h"
#include "edit_line.h"

char     *free_str_edit_lines(char *s1, char *s2)
{
  if (s1 != NULL)
    free(s1);
  if (s2 != NULL)
    free(s2);
  s1 = NULL;
  remind_save_str(1, &s1);
  return (NULL);
}

char    *finish_usr_cmd(char *cmd, char *str, struct termios unset)
{
  my_putstr("\n", 1);
  unset_termios(&unset);
  free_str_edit_lines(str, NULL);
  return (cmd);
}
