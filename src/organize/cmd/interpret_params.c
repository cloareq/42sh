/*
** interpret_params.c for  in /home/collio_v/rendu_svn/42.sh/42
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Mon May  6 20:09:42 2013 vincent colliot
** Last update Sun May 26 03:14:23 2013 vincent colliot
*/

#include "orga.h"
#include "lexec.h"
#include "bool.h"
#include "string.h"
#include "xmalloc.h"
#include "error.h"

static void	*sintax_error(char **bad_sintax)
{
  *bad_sintax = my_strcat(ERROR_NEAR_TOKEN, "(");
  return (NULL);
}

static t_words   *set_up(t_get *word, t_words **last)
{
  t_words	*params;

  if ((params = xmalloc(sizeof(*params))) == NULL)
    return (NULL);
  params->word = my_strdup(word->word);
  params->next = NULL;
  (*last)->next = params;
  *last = params;
  return (params);
}

t_words		*interpret_params(t_get *word, t_get **words,
				  t_words **last, char **bad_sintax)
{
  BOOL		no_match;

  if (MATCH("(", word->word))
    return (sintax_error(bad_sintax));
  no_match = TRUE;
  if (!word->inter && (IN('*', word->word)))
    if (match_them(word->word + last_occur(word->word, '/', '*')
		   + ((word->word)[last_occur(word->word, '/', '*')] == '/'),
		   my_strndup(word->word, last_occur(word->word, '/', '*')
			      + (((word->word)[0]) == '/')),
			      last, &no_match) == FALSE)
      if (no_match == FALSE)
	return (NULL);
  *words = word->next;
  if (no_match == TRUE)
    if (set_up(word, last) == NULL)
      return (NULL);
  free(word->word);
  free(word);
  return (*last);
}
