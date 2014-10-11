/*
** scan.c for  in /home/collio_v/rendu_svn/42.sh/42
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Thu May 23 14:23:19 2013 vincent colliot
** Last update Sun May 26 15:10:59 2013 thomas lecorre
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "fd.h"
#include "string.h"
#include "get_next_line.h"
#include "exec.h"
#include "env.h"
#include "built.h"

static FD	open_it(void)
{
  FD	file;
  char	*name;

  name = my_strcat(get_env("HOME"), ".Slashrc");
  file = open(name, O_RDONLY);
  free(name);
  return (file);
}

static BOOL fill_it(char *s, char **s1, char **s2, int no)
{
  char	get;

  *s1 = NULL;
  *s2 = NULL;
  if (empty(s))
    return (FALSE);
  if ((*s1 = my_strndup(s, my_sstrlen(s, "= \t"))) == NULL)
    return (TRUE);
  s += my_sstrlen(s, "= \t") + (IN('=', s) || IN(' ', s) || IN('\t', s));
  get = s[0];
  if (IN(s[0], "\"'") && !(IN(s[0], s + 1)))
    printf("error in conf file at line #%d, in %s definition\n", no,  *s1);
  if (IN(s[0], "\"'") && !(IN(s[0], s + 1)))
    return (FALSE);
  if (!IN(s[0], "'\""))
    get = 0;
  *s2 = my_strndup(s + IN(s[0], "'\""), my_strilen(s + IN(s[0], "'\""), get));
  if (IN(s[0], "'\"") && !empty(s + my_strlen(*s2) + 2 * IN(s[0], "'\"")))
    printf("error in conf file at line #%d, in %s definition\n", no,  *s1);
  if (IN(s[0], "'\"") && !empty(s + my_strlen(*s2) + 2 * IN(s[0], "'\"")))
    return (FALSE);
  return (TRUE);
}

static BOOL	export_env(char *s, int no)
{
  char *s1;
  char *s2;

  if (fill_it(s, &s1, &s2, no) == FALSE)
    return (FALSE);
  set_env(s1, s2);
  free(s1);
  free(s2);
  return (TRUE);
}

static BOOL	export_alias(char *s, t_alias **alias, int no)
{
  t_alias	*link;
  BOOL		c;
  char *s1;
  char *s2;

  if (fill_it(s, &s1, &s2, no) == FALSE)
    return (FALSE);
  if (!s1 || !s2)
    printf("error at line %d\n", no);
  if (!s1 || !s2)
    return (FALSE);
  link = *alias + (unsigned int)(c = FALSE);
  while (link && !c)
    if (MATCH(link->name, s1))
      c = TRUE;
    else
      link = link->next;
  if (!c)
    return (!mod_alias(s1, s2, alias));
  free(link->next);
  link->fill = s2;
  free(s1);
  return (FALSE);
}

void	scan_export(t_alias **alias)
{
  int		no;
  BOOL		c;
  char		*s;
  FD		file;

  c = TRUE;
  no = 0;
  if ((file = open_it()) == -1)
    return ;
  while ((s = get_next_line(file)) != NULL && c)
    {
      if (NMATCH("export", s))
	c = export_env(s + my_strlen("export")
		       + hempty(s + my_strlen("export")), no);
      else if (NMATCH("alias", s))
	c = export_alias(s + my_strlen("export")
			 + hempty(s + my_strlen("export")),
			 alias, no);
      else if (!nempty(s, my_strilen(s, '#')))
	return ;
      no++;
    }
}
