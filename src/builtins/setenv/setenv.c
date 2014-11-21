/*
** setenv.c for  in /home/lecorr_b//projets/42sh/42.sh/42/src/builtins
**
** Made by thomas lecorre
** Login   <lecorr_b@epitech.net>
**
** Started on  Fri May 10 15:05:03 2013 thomas lecorre
** Last update Sun May 26 02:21:41 2013 vincent colliot
*/

#include <stdlib.h>
#include "bool.h"
#include "string.h"
#include "env.h"
#include "built.h"
#include "xlib.h"

static int fill_env(char **tab, t_words *cmd, char *s)
{
  size_t	i;
  BOOL		n;

  i = (n = FALSE);
  while (environ[i])
    {
      if (!(NMATCH(cmd->word, environ[i])
	    && environ[i][my_strlen(cmd->word)] == '='))
	tab[i] = environ[i];
      else
	{
	  n = TRUE;
	  free(environ[i]);
	  tab[i] = my_stricat(cmd->word, s, '=');
	}
      i++;
    }
  if (n == FALSE)
    tab[i++] = my_stricat(cmd->word, s, '=');
  tab[i] = NULL;
  free(environ);
  environ = tab;
  return (EXIT_SUCCESS);
}

int	built_setenv(t_words *cmd, void *bool)
{
  size_t	n;
  size_t	i;
  char		**tab;

  (void)bool;
  if (cmd->next == ((void*)(n = (i = 0))))
    return (built_env(cmd, bool));
  if (IN('=', cmd->word))
    return (FALSE);
  if ((cmd = cmd->next) && cmd->next)
    if (cmd->next->next)
      return (my_putstr("(sh): setenv : Too many arguments.\n", 2) != 0);
  if (environ)
    while (environ[i])
      {
	if (NMATCH(cmd->word, environ[i])
	    && environ[i][my_strlen(cmd->word)] == '=')
	  n = 1;
	i++;
      }
  if ((tab = xmalloc(sizeof(char *) * (i + !n + 1))) == NULL)
    return (EXIT_FAILURE);
  if (cmd->next)
    return (fill_env(tab, cmd, cmd->next->word));
  return (fill_env(tab, cmd, NULL));
}
