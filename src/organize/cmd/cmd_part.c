/*
** cmd_part.c for  in /home/collio_v/rendu_svn/42.sh/42
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Fri May  3 18:33:37 2013 vincent colliot
** Last update Sun May 26 10:36:45 2013 vincent colliot
*/

#include "orga.h"
#include "lexec.h"
#include "bool.h"
#include "string.h"
#include "xmalloc.h"
#include "error.h"

static BOOL	check_sintax(char **bad_sintax, BOOL null, char *s)
{
  if (null && !*bad_sintax)
    *bad_sintax = my_strdup(s);
  return (FALSE);
}

static BOOL	parents(t_get *word, t_get **words,
			t_cmd *link, char **bad_sintax)
{
  BOOL		no_word;
  t_get	*organize;

  if (lvl_parents(words, bad_sintax) == FALSE)
    return (FALSE);
  if ((organize = word->next))
    word->next->prev = NULL;
  rm_words(word);
  if ((word = (*words)->prev) == NULL)
    return (check_sintax(bad_sintax, 1, ERROR_NEAR_PARENTS));
  if (MATCH(word->word, "("))
    return (check_sintax(bad_sintax, 1, ERROR_NEAR_PARENTS));
  word->next = NULL;
  word = (*words)->next;
  rm_words(*words);
  if ((link->parents = orga(organize, bad_sintax, &no_word, TRUE)) == NULL)
    return (check_sintax(bad_sintax, no_word, ERROR_NEAR_PARENTS));
  while (word)
    if (!add_redir(word, &word, bad_sintax, link))
      return (FALSE);
  return (TRUE);
}

BOOL	cmd_part(t_get *word, t_get **words, t_cmd *link, char **bad_sintax)
{
  word->prev = NULL;
  link->type = PARENTS;
  if (MATCH(word->word, "("))
    return (parents(word, words, link, bad_sintax));
  link->type = OREDIR;
  link->redir = NULL;
  if ((link->params = list_cmd(word, link, NULL, bad_sintax)) == NULL)
    if (link->type != OREDIR || *bad_sintax)
      return (FALSE);
  return (TRUE);
}
