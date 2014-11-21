/*
** s_alloc.c for  in /home/collio_v/rendu_svn/42.sh/42
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Mon Apr 29 19:47:25 2013 vincent colliot
** Last update Sun May 26 03:06:43 2013 vincent colliot
*/

#include "string.h"
#include "xmalloc.h"

char	*my_strdup(const char *s)
{
  char		*r;
  size_t	i;

  i = 0;
  if (!s)
    return (NULL);
  if ((r = malloc(sizeof(*r) * (my_strlen(s) + 1))) == NULL)
    {
      print_err("Sys fail\n");
      return (NULL);
    }
  while (s[i])
    {
      r[i] = s[i];
      i++;
    }
  r[i] = 0;
  return (r);
}

void	*my_strndup(const void	*s, size_t n)
{
  void	*r;
  size_t	i;

  i = 0;
  if (!s || !n)
    return (NULL);
  if ((r = malloc(n + 1)) == NULL)
    {
      print_err("Sys fail\n");
      return (NULL);
    }
  ((char*)r)[n] = 0;
  while (i < n)
    {
      ((char*)r)[i] = ((char*)s)[i];
      i++;
    }
  ((char*)r)[i] = 0;
  return (r);
}

char	*my_strcat(const char *s, const char *c)
{
  size_t i;
  size_t si;
  size_t ci;
  char	*r;

  if (!s)
    return (my_strdup(c));
  si = my_strlen(s);
  ci = my_strlen(c);
  if ((r = xmalloc(sizeof(char) * (si + ci + 2))) == NULL)
    return (NULL);
  r[si + ci] = (i = 0);
  if (s)
    while (i < si)
      {
	r[i] = s[i];
	i++;
      }
  while (i < si + ci)
    {
      r[i] = c[i - si];
      i++;
    }
  r[i + 1] = 0;
  return (r);
}

char	*my_strncat(const char *s, const char *c, size_t n)
{
  size_t i;
  size_t si;
  size_t ci;
  char	*r;

  si = my_strlen(s);
  if ((ci = my_strlen(c)) > n)
    ci = n;
  if ((r = xmalloc(sizeof(char) * (si + ci + 1))) == NULL)
    return (NULL);
  r[si + ci] = 0;
  i = 0;
  if (s)
    while (i < si)
      {
	r[i] = s[i];
	i++;
      }
  while (i < si + ci)
    {
      r[i] = c[i - si];
      i++;
    }
  r[i] = 0;
  return (r);
}

char	*my_stricat(const char *s, const char *c, char k)
{
  char	*pr;
  char	*r;
  char	sk[2];

  if (!k)
    return (my_strcat(s, c));
  sk[0] = k;
  sk[1] = 0;
  pr = my_strcat(s, sk);
  if (!c)
    return (pr);
  r = my_strcat(pr, c);
  free(pr);
  return (r);
}
