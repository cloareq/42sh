/*
** seek_cmd.c for  in /home/collio_v/rendu_svn/42.sh/42/src
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Sun May 26 10:39:14 2013 vincent colliot
** Last update Sun May 26 15:28:12 2013 vincent colliot
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

static char	*seek(char *path, char *cmd, char **bad_sintax)
{
  char		*dir;

  if (!path)
    return (NULL);
  if (!path[0])
    {
      *bad_sintax = my_strcat(UNKNOW_CMD, cmd);
      return (NULL);
    }
  if ((dir = my_strndup(path, my_strilen(path, ':'))) == NULL)
    return (NULL);
  if (in_directory(dir, cmd))
    return (dir);
  free(dir);
  if (!IN(':', path))
    {
      *bad_sintax = my_strcat(UNKNOW_CMD, cmd);
      return (NULL);
    }
  return (seek(path + my_strilen(path, ':') + IN(':', path), cmd, bad_sintax));
}

char	*seek_cmd(char *cmd, char **bad_sintax)
{
  char *r;
  char *wh;
  char *path;

  (void)bad_sintax;
  if ((path = get_env("PATH")) == NULL)
    *bad_sintax = my_strcat(UNKNOW_CMD, cmd);
  if ((wh = seek(path, cmd, bad_sintax)) == NULL)
    return (my_strdup(cmd));
  r = my_stricat(wh, cmd, '/');
  free(wh);
  return (r);
}
