/*
** move_to_word_fct.c for 42 in /home/thomas_1//Projets/42sh/src
**
** Made by pierre-yves thomas
** Login   <thomas_1@epitech.net>
**
** Started on  Fri May 10 13:07:12 2013 pierre-yves thomas
** Last update Sun May 26 11:01:47 2013 vincent colliot
*/

#include "edit_line.h"
#include "string.h"

void	move_to_prev_word(char c, int *rev_c, char **cmd)
{
  (void)c;
  if (*rev_c != 0 && (*cmd)[*rev_c] != ' ' && (*cmd)[*rev_c] != '\t')
    (*rev_c)--;
  while (*rev_c != 0 && ((*cmd)[*rev_c] == ' ' || (*cmd)[*rev_c] == '\t'))
    (*rev_c)--;
  while (*rev_c != 0 && (*cmd)[*rev_c] != ' ' && (*cmd)[*rev_c] != '\t')
    (*rev_c)--;
  if ((*rev_c) != 0)
    (*rev_c)++;
}

void	move_to_next_word(char c, int *rev_c, char **cmd)
{
  int	len;

  (void)c;
  len = my_strlen(*cmd);
  if (*rev_c < len && (*cmd)[*rev_c] != ' ' && (*cmd)[*rev_c] != '\t')
    (*rev_c)++;
  while (*rev_c < len && ((*cmd)[*rev_c] == ' ' || (*cmd)[*rev_c] == '\t'))
    (*rev_c)++;
  while (*rev_c < len && (*cmd)[*rev_c] != ' ' && (*cmd)[*rev_c] != '\t')
    (*rev_c)++;
}
