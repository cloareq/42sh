/*
** directory_in.c for  in /home/collio_v/rendu_svn/42.sh/42
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Sun May  5 13:18:32 2013 vincent colliot
** Last update Sun May 26 12:00:54 2013 vincent colliot
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include "string.h"
#include "bool.h"
#include "env.h"

BOOL	in_directory(char *ndir, char *word)
{
  struct dirent	*fchr;
  DIR		*dir;

  if ((dir = opendir(ndir)) == NULL)
    return (FALSE);
  while ((fchr = readdir(dir)) != NULL)
    if (MATCH(fchr->d_name, word))
      {
	closedir(dir);
	return (TRUE);
      }
  closedir(dir);
  return (FALSE);
}
