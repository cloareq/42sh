/*
** orga.c for  in /home/collio_v/rendu_svn/42.sh/42
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Thu May  2 19:44:26 2013 vincent colliot
** Last update Sun May 26 04:58:01 2013 vincent colliot
*/

#include "orga.h"
#include "lexec.h"
#include "bool.h"
#include "string.h"
#include "xmalloc.h"
#include "error.h"

static BOOL	dlaunch_cmd(t_exec *exec, char **bad_sintax, BOOL sub)
{
  if (!exec)
    return (TRUE);
  if (!get_cmd(exec->pipes, bad_sintax, NULL, sub))
    return (FALSE);
  if (dlaunch_cmd(exec->next, bad_sintax, sub) == FALSE)
    return (nullify_all_pipes(exec->pipes));
  return (TRUE);
}

static BOOL	launch_cmd(t_jobs *exec, char **bad_sintax, BOOL sub)
{
  if (!exec)
    return (TRUE);
  if (!dlaunch_cmd(exec->exec, bad_sintax, sub))
    {
      nullify_all_jobs(exec->next);
      return (nullify_jobs(exec, 1));
    }
  if (launch_cmd(exec->next, bad_sintax, sub) == FALSE)
    return (nullify_jobs(exec, 0));
  return (TRUE);
}

static BOOL	launch_pipe(t_jobs *exec, char **bad_sintax)
{
  if (!exec)
    return (TRUE);
  if (!get_pipe(exec->exec, bad_sintax))
    {
      nullify_all_jobs(exec->next);
      return (nullify_jobs(exec, 1));
    }
  if ((launch_pipe(exec->next, bad_sintax)) == FALSE)
    return (nullify_jobs(exec, 0));
  return (TRUE);
}

static BOOL	launch_exec(t_jobs *exec, char **bad_sintax)
{
  if (!exec)
    return (TRUE);
  if ((exec->exec = get_exec(exec->tmp, NULL, bad_sintax)) == NULL)
    return (FALSE);
  if (launch_exec(exec->next, bad_sintax) == FALSE)
    return (nullify_jobs(exec, 0));
  return (TRUE);
}

t_jobs	*orga(t_get *words, char **bad_sintax, BOOL *null, BOOL sub)
{
  t_jobs *exec;

  if (null)
    if ((*null = (!words)))
      return (NULL);
  if (!null && !words)
    return (NULL);
  if ((exec = get_jobs(words, NULL, bad_sintax)) == NULL)
    return (NULL);
  if (!launch_exec(exec, bad_sintax))
    return (NULL);
  if (!launch_pipe(exec, bad_sintax))
    return (NULL);
  if (!launch_cmd(exec, bad_sintax, sub))
    return (NULL);
  return (exec);
}
