/*
** alias.h for  in /home/collio_v/rendu_svn/42.sh/42/src
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Sat May 18 01:17:38 2013 vincent colliot
** Last update Sun May 26 13:33:18 2013 vincent colliot
*/

#ifndef ALIAS_H_
# define ALIAS_H_

#include <stdlib.h>

typedef struct s_alias{
  char	*name;
  char	*fill;
  struct s_alias *next;
  struct s_alias *prev;
  size_t	w;
  size_t	n;
}			t_alias;

#endif
