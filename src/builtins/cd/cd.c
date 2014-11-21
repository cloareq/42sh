/*
** cd.c<2> for  in /home/collio_v/rendu_svn/42.sh/42
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Fri May 17 17:17:12 2013 vincent colliot
** Last update Thu May 23 07:29:47 2013 vincent colliot
*/

#include "env.h"
#include "unistd.h"
#include "built.h"
#include "string.h"
#include "xlib.h"
#include "error.h"

static int	old_new(char **def, char *env)
{
  char	*apwd;

  if ((apwd = getcwd(NULL, 0)) == NULL)
    return (FALSE);
  if (*def)
    free(*def);
  *def = my_stricat(env, apwd, '=');
  free(apwd);
  return (TRUE);
}

static BOOL	set_old(char *env)
{
  char		**tab;
  size_t	i;

  i = 0;
  if (environ)
    while (environ[i])
      {
	if (NMATCH(env, environ[i]))
	  return (old_new(&(environ[i]), env));
	i++;
      }
  tab = environ;
  if ((environ = xmalloc(sizeof(char*) * (i + 2))) == NULL)
    return (FALSE);
  environ[i] = NULL;
  i = (unsigned long)(environ[i + 1] = NULL);
  if (tab)
    while (tab[i])
      {
	environ[i] = tab[i];
	i++;
      }
  free(tab);
  return (old_new(&(environ[i]), env));
}

static char	*new_pwd(t_words *wpwd)
{
  if (!wpwd)
    return (get_env("HOME"));
  if (MATCH(wpwd->word, "-"))
    return (get_env("OLD_PWD"));
  return (wpwd->word);
}

static BOOL	set_new(char *new)
{
  if (chdir(new) == -1)
    {
      print_err(DIR_ERROR);
      print_err(new);
      print_err("\n");
      return (FALSE);
    }
  free(new);
  return (set_old("PWD"));
}

int	built_cd(t_words *cmd, void *null)
{
  char	*new;

  (void)null;
  if ((new = new_pwd(cmd->next)) == NULL)
    {
      print_err(DIR_ERROR);
      if (!cmd->next)
	print_err("HOME");
      else
	print_err("prev");
      print_err("\n");
      return (EXIT_FAILURE);
    }
  new = my_strdup(new);
  if (set_old("OLD_PWD") == FALSE)
    return (EXIT_FAILURE);
  if (set_new(new) == FALSE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
