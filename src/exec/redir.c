/*
** redir.c for  in /home/collio_v/rendu_svn/42.sh/42
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Sun May 12 22:15:18 2013 vincent colliot
** Last update Sun May 26 15:20:14 2013 vincent colliot
*/

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "orga.h"
#include "exec.h"
#include "string.h"

BOOL	rleft(t_redir *r, FD w[3], char	**bad_syntax)
{
  FD	file;
  FD	in;

  in = 0;
  if (r->in < 3 && r->in >= 0)
    in = r->in;
  if (w[in] >= 0)
    close(w[in]);
  if ((file = open(r->file, O_RDONLY)) == -1)
    {
      *bad_syntax = my_strcat("(sh): NO such file or directory: ", r->file);
      return (FALSE);
    }
  w[in] = file;
  return (TRUE);
}

void	rright(t_redir *r, FD w[3], FD l[3])
{
  FD	in;

  in = 1;
  if (r->in < 3 && r->in >= 0)
    in = r->in;
  if (w[in] != -1 && (r->type == ON_CANAL))
    close(w[in]);
  if (r->type != ON_CANAL)
    w[in] = open(r->file, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR
		| S_IRGRP | S_IROTH);
  if (r->type == ON_CANAL)
    {
      w[in] = dup(l[r->out]);
      close(l[in]);
    }
}

static void	rdright(t_redir *r, FD w[3])
{
  FD	in;

  in = 1;
  if (r->in < 3 && r->in >= 0)
    in = r->in;
  if (w[in] >= 0)
    close(w[in]);
  if ((w[in] = open(r->file, O_WRONLY | O_APPEND)) == -1)
    w[in] = open(r->file, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR
		 | S_IRGRP | S_IROTH);
}

BOOL	calque_redir(t_redir *r, FD w[3], t_info *i, char **bad_syntax)
{
  if (!r)
    return (TRUE);
  if (r->redir == LEFT)
    {
      if (rleft(r, w, bad_syntax) == FALSE)
	return (FALSE);
    }
  else if (r->redir == DLEFT)
    {
      if (rdleft(r, w, i) == FALSE)
	return (FALSE);
    }
  else if (r->redir == RIGHT)
    rright(r, w, i->wr);
  else if (r->redir == DRIGHT)
    rdright(r, w);
  return (calque_redir(r->next, w, i, bad_syntax));
}
