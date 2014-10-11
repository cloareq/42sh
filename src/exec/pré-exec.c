/*
** pré-exec.c for  in /home/collio_v/rendu_svn/42.sh/42
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Fri May 10 14:58:16 2013 vincent colliot
** Last update Sun May 26 13:58:49 2013 vincent colliot
*/

#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include "orga.h"
#include "exec.h"
#include "xlib.h"
#include "father.h"

static void	init_pipe(FD w[2], FD pi[3], FD h)
{
  close(pi[h]);
  pi[h] = w[h];
  close(w[!h]);
}

static void	my_wait(pid_t son, STATUS *st)
{
  STATUS stat;
  pid_t	pid;

  while ((pid = waitpid(-1, &stat, WNOHANG)) >= 0)
    {
      if (pid == son)
  	*st = stat;
    }
}

static BOOL	get_status(t_info *info, STATUS st)
{
  if (info->st != EXIT_FAILURE)
    info->st = (0 != (WEXITSTATUS(st)));
  info->value = WEXITSTATUS(st);
  return (TRUE);
}

BOOL	exec_pipes(t_pipes *p, t_info *info, FLAG son, FD pi[3])
{
  STATUS	status_quo;
  pid_t		pid;
  FD		w[2];

  if (!(pid = -(!((unsigned long)(p->next != NULL)))))
    {
      if (pipe(w) == -1)
	return (FALSE);
      if ((pid = xfork()) < 0)
	return (FALSE);
    }
  if (!pid)
    {
      init_pipe(w, pi, W_IN);
      exec_pipes(p->next, info, SON, pi);
      return (FALSE);
    }
  if (p->next)
    init_pipe(w, pi, W_OUT);
  if (exec_cmd(p->cmd, info, info->son = (son | (2 * (pid > 0))), pi) == FALSE)
    return (FALSE);
  my_wait(pid, &status_quo);
  if (pid < 0)
    return (TRUE);
  return (get_status(info, status_quo));
}
