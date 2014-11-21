/*
** hist.c for  in /home/collio_v/rendu_svn/42.sh/42
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Wed May 22 07:41:38 2013 vincent colliot
** Last update Sun May 26 06:25:44 2013 vincent colliot
*/

#define _GNU_SOURCE
#include <stdio.h>
#include "exec.h"
#include "bool.h"
#include "env.h"
#include "string.h"
#include "xmalloc.h"

static BOOL mod_var(char *s, char *fill, char **mod, char *seek)
{
  char	*modif[2];

  if ((modif[0] = my_strndup(*mod, s - *mod)) == NULL && (s != *mod))
    return (FALSE);
  if ((modif[1] = my_strdup(s + my_strlen(seek) + 1)) == NULL &&
      my_strlen(s + my_strlen(seek) + 1))
    return (FALSE);
  free(*mod);
  if ((*mod = my_strcat(modif[0], fill)) == NULL && my_strlen(*mod) &&
      my_strlen(fill))
    return (FALSE);
  free(modif[0]);
  s = *mod;
  if ((*mod = my_strcat(*mod, modif[1])) == NULL && my_strlen(*mod) &&
      my_strlen(modif[1]))
    return (FALSE);
  free(s);
  free(modif[1]);
  return (TRUE);
}

static void	seek_seek(t_history *hist, char **fill, char *seek)
{
  if (!hist)
    return ;
  if (NMATCH(seek, hist->str))
    {
      *fill = my_strdup(hist->str);
      return ;
    }
  seek_seek(hist->next, fill, seek);
}

static int	seek_for(t_history *hist, char **fill, int sn, int n)
{
  int nr;

  if (!hist)
    return (0);
  if (sn < 0 && -sn == n)
    *fill = my_strdup(hist->str);
  if (sn < 0 && -sn == n)
    return (0);
  nr = seek_for(hist->next, fill, sn, n + 1) + 1;
  if (nr == sn && !*fill)
    *fill = my_strdup(hist->str);
  return (nr);
}

static char	*fill_it(char *seek, t_info *info, char **mod)
{
  int    sn;
  char	*fill;

  sn = 0;
  if (!seek)
    return (NULL);
  fill = NULL;
  if (IN(seek[0], "0123456789-+"))
    sn = my_getnbr(seek);
  if (!sn)
    seek_seek(info->hist, &fill, seek);
  else
    seek_for(info->hist, &fill, sn, 1);
  if (!fill)
    {
      free(*mod);
      *mod = NULL;
    }
  if (!fill)
    printf("no event found for !%s\n", seek);
  return (fill);
}

BOOL	grow_hist(char *s, char **mod, size_t n, t_info *info)
{
  char	*seek;
  char	*fill;

  n += my_sstrlen(s, "!");
  s += my_sstrlen(s, "!");
  if (!s[0])
    return (TRUE);
  if ((IN(s[1], "/!\\ \t(;|&") || !s[1]) || (n && s[-1] == '\\'))
    return (grow_hist(s + 1 +  my_sstrlen(s + 1, "$~"), mod, n +
		     1 +  my_sstrlen(s + 1, "$~"), info));
  seek = NULL;
  if (s[0] == '!' && !IN(s[1], "-+0123456789"))
    seek = my_strndup(s + 1, my_sstrlen(s + 1, " \"\t(;|&"));
  else
    seek = my_strndup(s + 1, IN(s[1], "+-")
		      + lenmatch(s + 1 + IN(s[1], "+-"), "0123456789"));
  if ((fill = fill_it(seek, info, mod)) == NULL)
    return (FALSE);
  if (mod_var(s, fill, mod, seek) == FALSE)
    return (FALSE);
  s = *mod + n + my_strlen(fill);
  n += my_strlen(fill);
  free(fill);
  free(seek);
  return (1 + grow_hist(s, mod, n, info));
}
