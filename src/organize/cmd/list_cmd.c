/*
** list_cmd.c for  in /home/collio_v/rendu_svn/42.sh/42/src
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Sun May 26 10:35:07 2013 vincent colliot
** Last update Sun May 26 10:41:45 2013 vincent colliot
*/

#include "orga.h"
#include "lexec.h"
#include "bool.h"
#include "string.h"
#include "xmalloc.h"
#include "error.h"

static t_words	*nullify_link(t_words *link, BOOL f, void *last)
{
  t_words *next;

  if (!link || f || link == last)
    return (NULL);
  next = link->next;
  free(link);
  return (nullify_link(next, f, last));
}

BOOL	add_redir(t_get *word, t_get **words,
			  char **bad_sintax, t_cmd *link)
{
  t_redir *prev;

  prev = link->redir;
  if (prev)
    while (prev->next)
      prev = prev->next;
  if (prev)
    if ((prev->next = redir_part(word, words, bad_sintax)) == NULL)
      return (FALSE);
  if (!prev)
    if ((link->redir = redir_part(word, words, bad_sintax)) == NULL)
      return (FALSE);
  return (TRUE);
}

t_words	*list_cmd(t_get *word, t_cmd *clink,
			  t_words *prev, char **bad_sintax)
{
  BOOL		f;
  t_words	*link;

  if (!word)
    return (prev);
  link = prev;
  f = TRUE;
  if (!((IN('>', word->word) || IN('<', word->word)) && !word->inter))
    {
      clink->type = WORDS;
      if ((clink->type = WORDS) && prev)
	if ((link = interpret_params(word, &word, &prev, bad_sintax)) == NULL)
	  return ((void*)(long)nullify_words(word));
      if ((clink->type = WORDS) && !prev)
	if ((link = interpret_cmd(word, &word, bad_sintax, &prev)) == NULL)
	  return ((void*)(long)nullify_words(word));
    }
  else
    if ((f = add_redir(word, &word, bad_sintax, clink)) == FALSE)
      return (NULL);
    else
      return (list_cmd(word, clink, prev, bad_sintax));
  if (list_cmd(word, clink, prev, bad_sintax) == NULL)
    return (nullify_link(link, f, (prev->next = NULL)));
  return (link);
}
