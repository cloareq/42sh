/*
** get_env.c for  in /home/collio_v/rendu_svn/42.sh/42
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Sun May  5 12:30:49 2013 vincent colliot
** Last update Wed May 22 02:53:55 2013 vincent colliot
*/

#include "built.h"
#include "string.h"
#include "bool.h"
#include "env.h"
#include "xmalloc.h"

static BOOL move_env(char *s, size_t i)
{
  if (NMATCH(s, environ[i]) && (environ[i][my_strlen(s)] == '='))
    return (TRUE);
  return (FALSE);
}

static BOOL fill_env(char *s, char *s2, int i)
{
  free(environ[i]);
  if ((environ[i] = my_stricat(s, s2, '=')) == NULL)
    return (FALSE);
  return (TRUE);
}

BOOL	set_env(char *s, char *s2)
{
  char	**tab;
  size_t	i;

  i = 0;
  if (environ)
    while (environ[i])
      if (move_env(s, i++))
	return (fill_env(s, s2, i - 1));
  if ((tab = xmalloc(sizeof(*tab) * (i + 3))) == NULL)
    return (FALSE);
  i = 0;
  if (environ)
    while (environ[i++])
      tab[i - 1] = environ[i - 1];
  tab[i - 1] = my_stricat(s, s2, '=');
  tab[i] = NULL;
  return (switch_env(tab, FALSE));
}

char	*get_env(char *s)
{
  size_t	i;

  i = 0;
  if (!environ)
    return (NULL);
  while (environ[i])
    {
      if (NMATCH(s, environ[i]))
	return (environ[i] + my_strilen(environ[i], '=') + 1);
      i++;
    }
  return (NULL);
}

char	*get_full_env(char *s)
{
  size_t	i;

  i = 0;
  if (!environ)
    return (NULL);
  while (environ[i])
    {
      if (NMATCH(s, environ[i]))
	return (environ[i]);
      i++;
    }
  return (NULL);
}
