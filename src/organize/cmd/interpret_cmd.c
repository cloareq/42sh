/*
** interpret.c for  in /home/collio_v/rendu_svn/42.sh/42
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Sat May  4 16:34:47 2013 vincent colliot
** Last update Sun May 26 10:40:58 2013 vincent colliot
*/

#include <sys/types.h>
#include <dirent.h>
#include "orga.h"
#include "lexec.h"
#include "bool.h"
#include "string.h"
#include "xmalloc.h"
#include "error.h"
#include "env.h"
#include "built.h"

static char	*verify(char *cmd, char **bad_sintax)
{
  DIR  *dir;
  char *r;

  if (access(cmd, X_OK))
    {
      *bad_sintax = my_strcat(UNKNOW_CMD, cmd);
      return (NULL);
    }
  if ((dir = opendir(cmd)) != NULL)
    {
      r = my_strcat(IS_DIR_ERROR1, cmd);
      *bad_sintax = my_strcat(r, IS_DIR_ERROR2);
      free(r);
      closedir(dir);
      return (NULL);
    }
  r = my_strdup(cmd);
  return (r);
}

static void	*nullify_link(t_words *link)
{
  free(link);
  return (NULL);
}

static BOOL	not_a_built_in(char *word)
{
  t_call	*built_call;
  size_t	i;

  i = 0;
  built_call = builtins();
  while ((built_call[i]).name)
    {
      if (MATCH((built_call[i]).name, word))
	{
	  free(built_call);
	  return (FALSE);
	}
      i++;
    }
  free(built_call);
  return (TRUE);
}

t_words		*interpret_cmd(t_get *word, t_get **words, char **bad_sintax,
			      t_words **last)
{
  t_words	*link;
  char		*cmd;

  if (MATCH("(", word->word))
    {
      *bad_sintax = my_strcat(ERROR_NEAR_TOKEN, "(");
      return (NULL);
    }
  cmd = word->word;
  if ((*last = (link = xmalloc(sizeof(*link)))) == NULL)
    return (NULL);
  if (cmd[0] == '.' || IN('/', cmd))
    if ((link->word = verify(cmd, bad_sintax)) == NULL)
      return (nullify_link(link));
  if (!(cmd[0] == '.' || IN('/', cmd)) && not_a_built_in(cmd))
    if ((link->word = seek_cmd(cmd, bad_sintax)) == NULL)
      return (nullify_link(link));
  if (!not_a_built_in(cmd))
    if ((link->word = my_strdup(cmd)) == NULL)
      return (nullify_link(link));
  free(cmd);
  *words = word->next;
  free(word);
  link->next = NULL;
  return (link);
}
