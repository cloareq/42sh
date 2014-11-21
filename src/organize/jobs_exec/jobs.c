/*
** jobs.c for  in /home/collio_v/rendu_svn/42.sh/42
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Thu May  2 22:25:44 2013 vincent colliot
** Last update Thu May  9 22:57:01 2013 vincent colliot
*/

#include "orga.h"
#include "lexec.h"
#include "bool.h"
#include "string.h"
#include "xmalloc.h"
#include "error.h"

static FLAG match_these(char *word)
{
  if (MATCH(";", word))
    return (NONE);
  if (MATCH("&", word))
    return (JOBS);
  return (0);
}

static FLAG	match_end(t_get **words, char **bad_sintax)
{
  FLAG	r;
  t_get *link;

  link = *words;
  if (match_these(link->word))
    {
      *bad_sintax = my_strcat(WRONG_SEP_TOKEN, link->word);
      return (FALSE);
    }
  while (link)
    {
      if (lvl_parents(&link, bad_sintax) == FALSE)
	return (FALSE);
      *words = link;
      if (!link)
	return (NONE);
      if ((r = match_these(link->word)))
	return (r);
      link = link->next;
      *words = link;
    }
  return (NONE);
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

static void	*nullify(t_jobs *link)
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

t_jobs *get_jobs(t_get *words, t_jobs *prev, char **bad_sintax)
{
  t_jobs *link;

  if (!words)
    return (prev);
  if ((link = xmalloc(sizeof(*link))) == NULL)
    return (word_nullify(words));
  link->tmp = words;
  if (!(link->type = match_end(&words, bad_sintax)))
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
  if (get_jobs(words->next, link, bad_sintax) == NULL)
    return (nullify(link));
  rm_words(words);
  return (link);
}
