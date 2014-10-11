/*
** var.c for  in /home/collio_v/rendu_svn/42.sh/42
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Fri May 10 14:25:20 2013 vincent colliot
** Last update Sun May 26 14:56:47 2013 vincent colliot
*/

#define _GNU_SOURCE
#include <stdio.h>
#include "exec.h"
#include "bool.h"
#include "env.h"
#include "string.h"
#include "xmalloc.h"
#include "subdivide.h"

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

static char	*fill_it(char *s, char *seek, t_info *info)
{
  char	*fill;

  if (s[0] == '$' && !(MATCH("?", seek)))
    fill = my_strdup(get_env(seek));
  else if (MATCH("?", seek))
    asprintf(&fill, "%d", info->value);
  else
    fill = my_strdup(get_env("HOME"));
  return (fill);
}

static BOOL	short_it(char **mod, char **s, size_t n, t_info *info)
{
  char  *tmp2;
  char	*tmp1;

  tmp1 = my_strndup(*mod, n - 1);
  tmp2 = my_strcat(tmp1, *s);
  if (*mod)
    free(*mod);
  *mod = tmp2;
  if (tmp1)
    free(tmp1);
  if (*mod)
    *s = *mod + ((n) += my_sstrlen(*mod + n, "~$"));
  return (grow_var(*s, mod, n, info));
}

BOOL	grow_var(char *s, char **mod, size_t n, t_info *info)
{
  char	*seek;
  char	*fill;

  n += my_sstrlen(s, "~$");
  s += my_sstrlen(s, "~$");
  if (!s[0])
    return (TRUE);
  if ((n && s[-1] == '\\'))
    return (short_it(mod, &s, n, info));
  if ((n && s[-1] == '\\')
      || ((IN(s[1], "/!\\ \t(;|&[]") || !s[1]) && s[0] != '~'))
    return (grow_var(s + 1 +  my_sstrlen(s + 1, "$~"), mod, n +
		     1 +  my_sstrlen(s + 1, "$~"), info));
  seek = NULL;
  if (s[0] == '$' && s[1] != '?')
    seek = my_strndup(s + 1, my_sstrlen(s + 1, "$!/!\\ \"\t(;|&[]"));
  else if (s[1] == '?' && s[0] == '$')
    seek = my_strdup("?");
  fill = fill_it(s, seek, info);
  if (mod_var(s, fill, mod, seek) == FALSE)
    return (FALSE);
  s = *mod + (n += my_strlen(fill));
  free(fill);
  free(seek);
  return (grow_var(s, mod, n, info));
}
