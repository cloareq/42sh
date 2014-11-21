/*
** null2.c for  in /home/collio_v/rendu_svn/42.sh/42
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Thu May  9 21:50:54 2013 vincent colliot
** Last update Sun May 26 10:46:21 2013 vincent colliot
*/

#include <stdlib.h>
#include "orga.h"
#include "lexec.h"
#include "bool.h"

void *nullify_all_jobs(t_jobs *jobs)
{
  t_jobs	*next;

  if (!jobs)
    return (NULL);
  if (jobs->exec)
    nullify_all_exec(jobs->exec);
  else
    nullify_words(jobs->tmp);
  next = jobs->next;
  free(jobs);
  nullify_all_jobs(next);
  return (NULL);
}

BOOL nullify_jobs(t_jobs *jobs, BOOL ex)
{
  if (jobs->exec && !ex)
    nullify_all_exec(jobs->exec);
  else if (!ex)
    nullify_words(jobs->tmp);
  if (ex)
    nullify_exec(jobs->exec);
  free(jobs);
  return (FALSE);
}

void nullify_cmd_words(t_words *s)
{
  t_words *n;

  if (!s)
    return ;
  n = s->next;
  if (s->word)
    free(s->word);
  free(s);
  nullify_cmd_words(n);
}

BOOL nullify_redir(t_redir *r)
{
  t_redir *n;

  if (!r)
    return (FALSE);
  n = r->next;
  if (r->file)
    free(r->file);
  free(r);
  nullify_redir(n);
  return (FALSE);
}

BOOL nullify_cmd(t_cmd *cmd)
{
  if (!cmd)
    return (FALSE);
  if (cmd->params)
    nullify_cmd_words(cmd->params);
  else if (cmd->parents)
    nullify_all_jobs(cmd->parents);
  if (cmd->redir)
    nullify_redir(cmd->redir);
  free(cmd);
  return (FALSE);
}

