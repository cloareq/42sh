/*
** null1.c for  in /home/collio_v/rendu_svn/42.sh/42
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Thu May  9 21:48:50 2013 vincent colliot
** Last update Sun May 26 10:45:59 2013 vincent colliot
*/

#include <stdlib.h>
#include "orga.h"
#include "lexec.h"
#include "bool.h"

BOOL	nullify_exec(t_exec *exec)
{
  t_exec	*next;

  if (!exec)
    return (FALSE);
  next = exec->next;
  free(exec);
  nullify_exec(next);
  return (FALSE);
}

BOOL	nullify_pipes(t_pipes *pipes)
{
  free(pipes);
  return (FALSE);
}

BOOL     nullify_words(t_get *word)
{
  t_get *next;

  next = word;
  while (next)
    {
      next = word->next;
      free(word->word);
      free(word);
      word = next;
    }
  return (FALSE);
}

BOOL	nullify_all_pipes(t_pipes *pipes)
{
  t_pipes	*next;

  if (!pipes)
    return (FALSE);
  if (pipes->cmd)
    nullify_cmd(pipes->cmd);
  else
    nullify_words(pipes->tmp);
  next = pipes->next;
  free(pipes);
  nullify_all_pipes(next);
  return (FALSE);
}

BOOL	nullify_all_in_pipes(t_pipes *pipes)
{
  if (pipes->cmd)
    nullify_cmd(pipes->cmd);
  else
    nullify_words(pipes->tmp);
  free(pipes);
  return (FALSE);
}
