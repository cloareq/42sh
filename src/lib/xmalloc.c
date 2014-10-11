/*
** xmalloc.c for  in /home/collio_v/rendu_svn/42.sh/42
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Mon Apr 29 21:43:23 2013 vincent colliot
** Last update Mon Apr 29 22:59:35 2013 vincent colliot
*/

#include <stdlib.h>
#include "string.h"

void	*xmalloc(size_t t)
{
  void	*r;

  if ((r = malloc(t)) == NULL)
    {
      print_err("Sys fail\n");
      return (NULL);
    }
  return (r);
}
