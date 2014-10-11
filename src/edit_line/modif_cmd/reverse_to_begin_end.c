/*
** reverse_to_begin_end.c for 42 in /home/thomas_1//Projets/42.sh/42/src/edit_line/modif_cmd
**
** Made by pierre-yves thomas
** Login   <thomas_1@epitech.net>
**
** Started on  Tue May 21 22:09:55 2013 pierre-yves thomas
** Last update Sun May 26 11:02:07 2013 vincent colliot
*/

#include "edit_line.h"
#include "string.h"

void            reverse_to_begin(char value, int *reverse_case, char **cmd)
{
  (void)value;
  (void)cmd;
  (*reverse_case) = 0;
}

void            reverse_to_end(char value, int *reverse_case, char **cmd)
{
  (void)value;
  (*reverse_case) = my_strlen(*cmd);
}
