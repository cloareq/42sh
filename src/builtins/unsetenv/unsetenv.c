/*
** unsetenv.c for  in /home/lecorr_b//projets/42sh/42.sh/42/src/builtins
**
** Made by thomas lecorre
** Login   <lecorr_b@epitech.net>
**
** Started on  Fri May 10 17:03:04 2013 thomas lecorre
** Last update Tue May 21 17:52:35 2013 vincent colliot
*/

#include <stdlib.h>
#include "string.h"
#include "env.h"
#include "built.h"
#include "xlib.h"

int  switch_env(char **tab, BOOL destroy)
{
  if (!destroy)
    if (environ)
      free(environ);
  if (destroy && environ)
    destroy_env();
  environ = tab;
  return (EXIT_SUCCESS);
}

static BOOL deset(t_words *cmd, char *env)
{
  if (!cmd)
    return (FALSE);
  if (NMATCH(cmd->word, env)
      && env[my_strlen(cmd->word)] == '=')
    return (TRUE);
  return (deset(cmd->next, env));
}

int	built_unsetenv(t_words *cmd, void *null)
{
  char		**tab;
  size_t	i;
  size_t	n;

  (void)null;
  if (!cmd->next)
    return (my_putstr("(sh): unsetenv: Too few arguments.\n", 2) != 0);
  i = (n = 0);
  if (environ)
    while (environ[i])
      if (deset(cmd->next, environ[i++]))
	n++;
  if (i == n)
    return (switch_env(NULL, TRUE));
  if ((tab = xmalloc(sizeof(char*) * (i - n + 1))) == NULL)
    return (EXIT_FAILURE);
  tab[i - n] = NULL;
  i = (n = 0);
  while (environ[i])
    if (!deset(cmd->next, environ[i]))
      tab[n++] = environ[i++];
    else
      free(environ[i++]);
  tab[n] = NULL;
  return (switch_env(tab, FALSE));
}
