/*
** read_cmds.c for 42 in /home/thomas_1//Projets/42.sh/42/src/edit_line
**
** Made by pierre-yves thomas
** Login   <thomas_1@epitech.net>
**
** Started on  Wed May 15 17:14:07 2013 pierre-yves thomas
** Last update Sun May 26 16:19:45 2013 vincent colliot
*/

#include <signal.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "edit_line.h"
#include "string.h"
#include "subdivide.h"
#include "orga.h"
#include "lexec.h"
#include "prompt.h"
#include "get_next_line.h"

static void	*built(char *str, char **bad_sintax, t_info *info, char **mod_s)
{
  t_get	*sub;

  if (seed_alias(str, info->alias, &str) == FALSE)
    return (NULL);
  if (grow_var(str, &str, 0, info) == FALSE)
    return (NULL);
  *mod_s = str;
  if ((sub = subdivide(str, NULL, bad_sintax)) == NULL)
    return (NULL);
  if ((sub = comment(sub, NULL)) == NULL)
    return (NULL);
  return (orga(sub, bad_sintax, NULL, FALSE));
}

static BOOL	built_and_exec(char *str, t_info *info, t_history **history)
{
  char		*retain;
  t_jobs	*exec;
  char		*bad_sintax;

  retain = my_strdup(str);
  exec = (void*)(bad_sintax = NULL);
  if (!empty(str))
    if ((exec = built(str, &bad_sintax, info, &str)) == NULL)
      if (!empty(str))
	{
	  if (bad_sintax)
	    {
	      fprintf(stderr, "%s\n", bad_sintax);
	      free(bad_sintax);
	      my_put_in_history(history, retain);
	      free(retain);
	      return (TRUE);
	    }
	  return (!(info->st = EXIT_FAILURE));
	}
  if (!empty(retain) && (!(*history) || !MATCH((*history)->str, retain)))
    my_put_in_history(history, retain);
  free(retain);
  free(str);
  return (pre_exec(exec, info, FALSE));
}

void	catch_after(int num)
{
  (void)num;
}

static char	*get_usr_cmd(BOOL tgetfail, t_history *history,
			     struct s_options t, t_info *info)
{
  char	*r;

  if (tgetfail == FALSE)
    {
      configure_signals();
      my_putstr(info->termcaps.invi_cursor, 1);
      r = usr_cmd(0, history, t);
      my_putstr(info->termcaps.visi_cursor, 1);
    }

  if (tgetfail == TRUE)
    r = get_next_line(0);
  return (r);
}

int	read_cmds(t_info *info, BOOL tgetfail)
{
  BOOL			c;
  char			*str;
  t_history		*history;

  info->term_caps = tgetfail;
  c = TRUE;
  history = NULL;
  while (c && (str = get_usr_cmd(tgetfail, history, info->termcaps, info)))
    {
      signal(SIGINT, catch_after);
      info->hist = history;
      if (str && grow_hist(str, &str, 0, info) > 1)
	if (str)
	  printf("%s\n", str);
      if (str)
	c = built_and_exec(str, info, &history);
    }
  if (c)
    my_putstr("exit", 1);
  free_history(history);
  my_putstr(info->termcaps.visi_cursor, 1);
  return (0);
}
