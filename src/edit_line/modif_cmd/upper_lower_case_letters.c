/*
** upper_lower_case_letters.c for 42 in /home/thomas_1//Projets/42sh
**
** Made by pierre-yves thomas
** Login   <thomas_1@epitech.net>
**
** Started on  Mon May 13 10:46:31 2013 pierre-yves thomas
** Last update Sun May 26 11:02:17 2013 vincent colliot
*/

#include "edit_line.h"

void    lowercase_letters_found(char value, int *rev_c, char **cmd)
{
  (void)value;
  while ((*cmd)[*rev_c] != '\0' &&
         (*cmd)[*rev_c] != ' ' && (*cmd)[*rev_c] != '\t')
    {
      if ((*cmd)[*rev_c] >= 'A' && (*cmd)[*rev_c] <= 'Z')
        ((*cmd)[*rev_c]) += 32;
      (*rev_c)++;
    }
}

void    uppercase_first_letter_found(char value, int *rev_c, char **cmd)
{
  if ((*cmd)[*rev_c] != '\0')
    {
      if ((*cmd)[*rev_c] >= 'a' && (*cmd)[*rev_c] <= 'z')
        ((*cmd)[*rev_c]) -= 32;
      (*rev_c)++;
      lowercase_letters_found(value, rev_c, cmd);
    }
}
