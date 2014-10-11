/*
** subdiv.c for  in /home/collio_v/rendu_svn/42.sh/42
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Mon Apr 29 21:20:47 2013 vincent colliot
** Last update Sun May 26 10:51:55 2013 vincent colliot
*/

#include "string.h"
#include "xmalloc.h"
#include "get.h"
#include "error.h"
#include "subdivide.h"

static size_t work_on_quote(char *s, char **bad_sintax)
{
  char	quote[3];

  quote[0] = s[0];
  quote[1] = '\'';
  quote[2] = 0;
  if (!IN(quote[0], s + 1))
    *bad_sintax = my_strcat(UNMATCHED_TOKEN, quote);
  return (my_strilen(s + 1, quote[0]) + 2);
}

static size_t redir_lenth(char *s)
{
  size_t	n;

  n = IN(s[0], "012");
  n += 1;
  if (s[n] != '&' || s[n - 1] == '<')
    return (n + IN(s[n], "<>"));
  n += 1;
  if (IN(s[n], "012"))
    {
      if (IN(s[n + 1], " \t\"'|&;()`") || !s[n + 1])
	return (n + 1);
      else
	return (n - 1);
    }
  return (n - 1);
}

size_t subdiv(char *s, char **bad_sintax)
{
  if (NMATCH("||", s) || NMATCH("&&", s) || NMATCH("<<", s) || NMATCH(">>", s))
    return (2);
  if (my_sstrlen(s, "<>") < my_sstrlen(s, " \\\t\"'|&;()`") &&
      (my_sstrlen(s, "<>") == 1 || !my_sstrlen(s, "<>")))
    return (redir_lenth(s));
  if (s[0] == '"' || s[0] == '\'')
    return (work_on_quote(s, bad_sintax));
  if (IN(s[0], ";|&<>()`"))
    return (1);
  if (NMATCH(s + my_strilen(s, '&'), "&&") && my_strilen(s, '&')
      < my_sstrlen(s, " \\\t\"'|;<>()`"))
    return (my_strilen(s, '&'));
  return (my_sstrlen(s, " \\\t\"'|&;<>()`"));
}

static void	*nullify_link(t_get *link, BOOL l, BOOL f)
{
  if (!f)
    return (NULL);
  if (l)
    free(link->word);
  free(link);
  return (NULL);
}

t_get	*subdivide(char *s, t_get *prev, char **bad_sintax)
{
  size_t l;
  t_get *link;

  if (empty(s))
    return (prev);
  if (s[0] == '\\' && prev)
    if ((!S_IN(prev->word, "\"'|;<>()`")))
      return (echappment(s, prev, bad_sintax, 0));
  if ((link = xmalloc(sizeof(*prev))) == NULL)
    return (NULL);
  link->word = (void*)(link->next = NULL);
  link->prev = prev;
  if (prev)
    prev->next = link;
  s += hempty(s);
  if (s[(link->inter = 0)] == '\\')
    return (echappment(s, link, bad_sintax, 1));
  l = subdiv(s, bad_sintax);
  if (*bad_sintax)
    return (nullify_link(link, 0, 1));
  if ((link->word = my_strndup(s, l)) == NULL)
    return (nullify_link(link, 0, 1));
  if (subdivide(s + my_strlen(link->word), link, bad_sintax) == NULL)
    return (nullify_link(link, 1, 1));
  return (link);
}
