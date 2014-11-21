/*
** env_exec.c for  in /home/collio_v/rendu_svn/42.sh/42
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Sun May 19 04:50:12 2013 vincent colliot
** Last update Wed May 22 19:46:00 2013 vincent colliot
*/

#include "string.h"
#include "built.h"
#include "env.h"
#include "exec.h"

BOOL	print_help(void)
{
  my_putstr("Uasge: env [options]\n", 1);
  my_putstr("env built-in loads a temporary environment, wich is setted by:\n",
	    1);
  my_putstr("    -i      : unset all\n", 1);
  my_putstr("    -u {p}  : unset {p}\n", 1);
  my_putstr("    -s {v,p}: set {v} with {p}\n", 1);
  return (FALSE);
}

void	destroy_env(void)
{
  size_t	i;

  i = 0;
  if (!environ)
    return ;
  while (environ[i])
    free(environ[i++]);
  free(environ);
}

static int print_env()
{
  size_t	i;

  if (!environ)
    return (EXIT_FAILURE);
  i = 0;
  while (environ[i])
    {
      my_putstr(environ[i++], 1);
      my_putstr("\n", 1);
    }
  return (EXIT_SUCCESS);
}

static int seek_fail(char *r)
{
  if (!r)
    return (EXIT_FAILURE);
  print_err(r);
  print_err("\n");
  free(r);
  return (EXIT_FAILURE);
}

int	exec_env(t_words *word, char **save)
{
  STATUS	st;
  BOOL	ef;
  char	*r;
  char	*f;
  char **safe;

  if (!word)
    return (print_env());
  f = word->word;
  r = NULL;
  safe = environ;
  environ = save;
  if (!((word->word)[0] == '.' || IN('/', (word->word))))
    if ((word->word = seek_cmd(word->word, &r)) == NULL)
      {
	environ = safe;
	return (seek_fail(r));
      }
  environ = safe;
  if (!MATCH(f, word->word))
    free(f);
  exec_form(word, &ef, &st);
  return (st);
}
