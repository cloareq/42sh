/*
** redir.c for  in /home/collio_v/rendu_svn/42.sh/42
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Fri May 10 12:08:51 2013 vincent colliot
** Last update Sun May 26 10:44:58 2013 vincent colliot
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include "bool.h"
#include "xmalloc.h"
#include "orga.h"
#include "string.h"
#include "error.h"

static FLAG redir_type(char *s)
{
  return ((NMATCH("<<", s)) ? (DLEFT) :
		 (NMATCH(">>", s)) ? (DRIGHT) :
		 (NMATCH("<", s)) ? (LEFT) :
		 (NMATCH(">", s)) ? (RIGHT) :
		 (0));
}

static BOOL	test_file_redir(char *file, char **bad_sintax)
{
  char		*pre;
  struct stat st;

  if (stat(file, &st) == -1)
    return (TRUE);
  if ((st.st_mode & S_IFMT) == S_IFDIR)
      {
	pre = my_strcat(IS_DIR_ERROR1, file);
	*bad_sintax = my_strcat(pre, IS_DIR_ERROR2);
	free(pre);
	return (FALSE);
      }
  return (TRUE);
}

static BOOL	get_file_part(t_get **words, t_get *word,
			      t_redir *link, char **bad_sintax)
{
  if (!word)
    *bad_sintax = my_strdup(ERROR_IN_REDIR);
  if (!word)
    return (FALSE);
  *words = word->next;
  link->file = word->word;
  free(word);
  if (link->redir != DLEFT)
    if (test_file_redir(link->file, bad_sintax) == FALSE)
      return (FALSE);
  return (TRUE);
}

static BOOL	link_redir(t_get *word, t_get **words,
			   t_redir *link, char **bad_sintax)
{
  size_t	i;

  i = (!((word->word)[0] == '<') && !((word->word)[0] == '>'));
  if ((!IN('<', word->word) && !IN('>', word->word)) || word->inter == TRUE)
    {
      *bad_sintax = my_strdup(WRONG_REDIR);
      return (FALSE);
    }
  if (i)
    link->in = ((word->word)[0]) - '0';
  if (((word->word)[i + 1]) == '&')
    {
      link->type = ON_CANAL;
      link->out = ((word->word)[i + 2]) - '0';
    }
  link->redir = redir_type(word->word + i);
  *words = word->next;
  rm_words(word);
  if (!link->type)
    if (get_file_part(words, *words, link, bad_sintax) == FALSE)
      return (FALSE);
  return (TRUE);
}

t_redir	*redir_part(t_get *words, t_get **word, char **bad_sintax)
{
  t_redir	*link;

  if ((link = xmalloc(sizeof(*link))) == NULL)
    return ((void*)(long)nullify_words(words));
  link->next = NULL;
  link->file = NULL;
  link->type = 0;
  link->in = IN('>', words->word);
  if (link_redir(words, &words, link, bad_sintax) == FALSE)
    {
      nullify_words(words);
      if (link->file)
	free(link->file);
      free(link);
      return (NULL);
    }
  if (link->type != ON_CANAL)
    link->type = ON_FILE;
  *word = words;
  return (link);
}

