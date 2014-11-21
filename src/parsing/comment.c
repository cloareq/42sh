/*
** comment.c for  in /home/collio_v/rendu_svn/42.sh/42
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Fri May 10 14:50:23 2013 vincent colliot
** Last update Sun May 26 03:31:00 2013 vincent colliot
*/

#include "get.h"
#include "xmalloc.h"
#include "bool.h"
#include "string.h"
#include "subdivide.h"

static BOOL nullify_next(t_get *w)
{
  t_get	*next;

  if (!w)
    return (FALSE);
  next = w->next;
  free(w->word);
  free(w);
  return (nullify_next(next));
}

static void fill(char **word, char *s)
{
  if (!s)
    *word = my_strdup("");
  else
    *word = s;
}

static void rm_word(t_get *w)
{
  free(w->word);
  free(w);
}

t_get	*comment(t_get *w, t_get *prev)
{
  char  quote;
  char *s;

  if (!w)
    return (prev);
  if ((((quote = (w->word)[0]) == '"' || (w->word)[0] == '\'') && !w->inter))
    {
      if ((s = my_strndup(w->word + 1,
			  my_strilen(w->word + 1, quote))) == NULL)
	if (my_strilen(w->word + 1, quote))
	  {
	    nullify_next(w->next);
	    free(w);
	    return (NULL);
	  }
      free(w->word);
      fill(&(w->word), s);
      w->inter = TRUE;
    }
  if (comment(w->next, w) == NULL)
    {
      rm_word(w);
      return (NULL);
    }
  return (w);
}
