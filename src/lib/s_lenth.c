/*
** s_lenth.c for  in /home/collio_v/rendu_svn/42.sh/42
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Mon Apr 29 19:53:38 2013 vincent colliot
** Last update Mon May  6 21:57:06 2013 vincent colliot
*/

#include "string.h"

size_t	my_strlen(const char *s)
{
  size_t	i;

  i = 0;
  if (!s)
    return (0);
  while (s[i])
    i++;
  return (i);
}

size_t  my_strilen(const char *s, char c)
{
  size_t	i;

  i = 0;
  while (s[i] && s[i] != c)
    i++;
  return (i);
}

size_t my_strslen(const char *s, const char *c)
{
  size_t	i;

  i = 0;
  while (s[i] && !NMATCH(c, s + i))
    i++;
  return (i);
}

size_t  my_sstrlen(const char *s, const char *c)
{
  size_t	i;

  i = 0;
  while (s[i] && !IN(s[i], c))
    i++;
  return (i);
}

size_t lenmatch(const char *s, const char *c)
{
  size_t	i;

  i = 0;
  while (s[i] && IN(s[i], c))
    i++;
  return (i);
}
