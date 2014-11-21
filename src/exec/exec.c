/*
** exec.c for  in /home/collio_v/rendu_svn/42.sh/42
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Fri May 10 16:04:18 2013 vincent colliot
** Last update Sun May 26 15:36:26 2013 vincent colliot
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "orga.h"
#include "fd.h"
#include "bool.h"
#include "exec.h"
#include "father.h"
#include "built.h"
#include "string.h"

static BOOL	set_redir(t_redir *r, FD w[3], char **bad_syntax, t_info *i)
{
  BOOL		ret;
  FD		pi[3];
  FD		in;

  in = 0;
  while (in < 3)
    pi[in++] = -1;
  ret = TRUE;
  if (r)
    ret = calque_redir(r, pi, i, bad_syntax);
  in = 2 * ((i->son & SON) > 0);
  while (in >= 0 && in <= 2)
    {
      if (pi[in] >= 0)
	{
	  close(w[in]);
	  w[in] = pi[in];
	  dup2(pi[in], in);
	}
      else if ((in == W_IN && (i->son & SON)) || (in == W_OUT && (i->son & 2)))
	dup2(w[in], in);
      in += 1 - 2 * ((i->son & SON) > 0);
    }
  return (ret);
}

static BOOL	exec_built_in(t_cmd *cmd, t_info *info)
{
  size_t	i;
  t_call	*call;

  i = 0;
  call = builtins();
  while ((call[i]).name)
    {
      if (MATCH((call[i]).name, cmd->params->word))
	{
	  info->st = (0 !=
		      (info->value =
		       ((call[i]).ptr)(cmd->params, (void*)&(info->alias))));
	  if (MATCH(cmd->params->word, "exit"))
	    return (2);
	  return (TRUE);
	}
      i++;
    }
  free(call);
  return (FALSE);
}

static BOOL	check_bad_sintax(char *s)
{
  if (!s)
    return (FALSE);
  fprintf(stderr, "%s\n", s);
  return (TRUE);
}

static BOOL	call_parents(t_cmd *cmd, t_info *info)
{
  pid_t		pid;
  STATUS	chien;

  if ((pid = fork()) < 0)
    return (TRUE);
  if (!pid)
    {
      pre_exec(cmd->parents, info, TRUE);
      return (TRUE);
    }
  else
    waitpid(pid, &chien, 0);
  info->st = (0 != (info->value = WEXITSTATUS(chien)));
  return (FALSE);
}

BOOL		exec_cmd(t_cmd *cmd, t_info *info, FLAG son, FD w[3])
{
  int		r;
  BOOL		sys_fail;
  char		*bad_sintax;

  bad_sintax = (void*)((unsigned long)(r = (sys_fail = FALSE)));
  if (set_redir(cmd->redir, w, &bad_sintax, info) == FALSE)
    if ((r = check_bad_sintax(bad_sintax)) == FALSE)
      return (FALSE);
  if (cmd->type == PARENTS && !r)
    sys_fail = call_parents(cmd, info);
  if (cmd->type == WORDS && !r)
    if (!(r = exec_built_in(cmd, info)))
      info->st = exec_form(cmd->params, &sys_fail, &(info->value));
  cmd->parents = NULL;
  if (son & FATHER)
    close(w[W_OUT]);
  if ((son & SON) || w[W_IN] != W_IN)
    close(W_IN);
  if ((son & FATHER) || w[W_OUT] != W_OUT)
    close(W_OUT);
  if (w[W_ERR] != W_ERR)
    close(W_ERR);
  if (sys_fail == TRUE)
    return (FALSE);
  return (((son & SON) == FALSE) * (r != 2) * (sys_fail != TRUE));
}
