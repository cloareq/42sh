/*
** echappment.c for  in /home/collio_v/rendu_svn/42.sh/42/src
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Sun May 26 10:48:15 2013 vincent colliot
** Last update Sun May 26 10:51:29 2013 vincent colliot
*/

#include "string.h"
#include "xmalloc.h"
#include "get.h"
#include "error.h"
#include "subdivide.h"

static void	*nullify_link(t_get *link, BOOL l, BOOL f)
{
  if (!f)
    return (NULL);
  if (l)
    free(link->word);
  free(link);
  return (NULL);
}

t_get *echappment(char *s, t_get *link, char **bad_sintax, BOOL freud)
{
  char	*word;

  link->inter = 1;
  while (s[0] == '\\' && s[1])
    {
      word = link->word;
      s += 1;
      if ((link->word = my_strncat(word, s, subdiv(s + 1, bad_sintax)
				   * (!IN(s[1], " \\\t\"'|;<>()`")) + 1))
	  == NULL)
	return (nullify_link(link, (link->word) != NULL, freud));
      if (!IN(s[1], " \\\t\"'|;<>()`"))
	  *bad_sintax = NULL;
      if (word)
	free(word);
      s += 1 + subdiv(s + 1, bad_sintax) * (!IN(s[1], " \\\t\"'|;<>()`"));
    }
  if (!s[1] && s[0] == '\\')
    {
      *bad_sintax = my_strdup(ERROR_AFTER_ECHAP_CHAR);
      return (nullify_link(link, (link->word) != NULL, freud));
    }
  if (subdivide(s, link, bad_sintax) == NULL)
    return (nullify_link(link, 1, freud));
  return (link);
}
