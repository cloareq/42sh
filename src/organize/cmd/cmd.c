/*
** cmd.c for  in /home/collio_v/rendu_svn/42.sh/42
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Thu May  2 22:05:00 2013 vincent colliot
** Last update Sun May 26 05:04:12 2013 vincent colliot
*/

#include "orga.h"
#include "lexec.h"
#include "bool.h"
#include "string.h"
#include "xmalloc.h"

static t_cmd	*nullify_link(t_cmd *cmd)
{
  free(cmd);
  return (NULL);
}

static t_cmd	*make_cmd(t_get *words, char **bad_sintax)
{
  t_cmd		*link;

  if (!words)
    return (NULL);
  if ((link = xmalloc(sizeof(*link))) == NULL)
    return (NULL);
  link->redir = NULL;
  link->params = NULL;
  link->parents = NULL;
  if (!cmd_part(words, &words, link, bad_sintax))
    {
      nullify_redir(link->redir);
      return (nullify_link(link));
    }
  return (link);
}

static BOOL check_for_dleft(t_redir *redir)
{
  if (!redir)
    return (FALSE);
  if (redir->redir == DLEFT)
    return (TRUE);
  return (check_for_dleft(redir->next));
}

BOOL	get_cmd(t_pipes *pipe, char **bad_sintax, t_pipes *prev, BOOL sub)
{
  if (!pipe)
    return (TRUE);
  if ((pipe->cmd = make_cmd(pipe->tmp, bad_sintax)) == NULL)
    {
      nullify_all_pipes(pipe->next);
      free(pipe);
      return (FALSE);
    }
  if ((sub || prev) && check_for_dleft(pipe->cmd->redir) == TRUE)
    {
      if (sub)
	*bad_sintax = my_strdup("Can't << within ()'s.");
      else
	*bad_sintax = my_strdup("Ambiguous input redirect");
      nullify_all_pipes(pipe);
      return (FALSE);
    }
  if (get_cmd(pipe->next, bad_sintax, pipe, sub) == FALSE)
    return (nullify_all_in_pipes(pipe));
  return (TRUE);
}
