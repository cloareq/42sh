/*
** pipes.c for  in /home/collio_v/rendu_svn/42.sh/42
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Thu May  2 20:52:53 2013 vincent colliot
** Last update Thu May  9 22:57:14 2013 vincent colliot
*/

#include "orga.h"
#include "lexec.h"
#include "bool.h"
#include "string.h"
#include "xmalloc.h"
#include "error.h"
#include "env.h"

static BOOL	match_end(t_get **words, char **bad_sintax)
{
  t_get *link;

  link = *words;
  if (MATCH("|", link->word))
    {
      *bad_sintax = my_strcat(UNMATCHED_TOKEN, link->word);
      return (FALSE);
    }
  while (link)
    {
      if (lvl_parents(&link, bad_sintax) == FALSE)
	return (FALSE);
      *words = link;
      if (!link)
	return (TRUE);
      if (MATCH("|", link->word))
	return (TRUE);
      link = link->next;
      *words = link;
    }
  return (TRUE);
}

static void     *word_nullify(t_get *word)
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
  return (NULL);
}

static void	*nullify(t_pipes *link)
{
  t_get *next;
  t_get	*word;

  word = link->tmp;
  while (word)
    {
      next = word->next;
      free(word->word);
      free(word);
      word = next;
    }
  free(link);
  return (NULL);
}

static t_pipes	*assoc_pipes(t_get *words, t_pipes *prev, char **bad_sintax)
{
  t_pipes	*link;

  if (!words)
    return (prev);
  if ((link = xmalloc(sizeof(*link))) == NULL)
    return (word_nullify(words));
  link->tmp = words;
  link->cmd = NULL;
  if (match_end(&words, bad_sintax) == FALSE)
    return (word_nullify(words));
  if (words)
    if (words->prev)
      words->prev->next = NULL;
  if (words)
    if (words->next)
      words->next->prev = NULL;
  if (prev)
    prev->next = link;
  link->next = NULL;
  if (!words)
    return (link);
  if (assoc_pipes(words->next, link, bad_sintax) == NULL)
    return (nullify(link));
  rm_words(words);
  return (link);
}

BOOL	get_pipe(t_exec *execs, char **bad_sintax)
{
  if (!execs)
    return (TRUE);
  if ((execs->pipes = assoc_pipes(execs->tmp, NULL, bad_sintax)) == NULL)
    return (FALSE);
  return (get_pipe(execs->next, bad_sintax));
}
