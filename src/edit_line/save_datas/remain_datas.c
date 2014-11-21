/*
** remain_datas.c for 42 in /home/thomas_1//Projets/42sh/src
** 
** Made by pierre-yves thomas
** Login   <thomas_1@epitech.net>
** 
** Started on  Thu May 16 10:13:12 2013 pierre-yves thomas
** Last update Fri May 17 17:55:55 2013 pierre-yves thomas
*/

#include <stdlib.h>
#include "edit_line.h"

void                    retain_struct_options(int opt, t_options *options)
{
  static t_options      save_opt;

  if (opt == 1)
    save_opt = (*options);
  else
    (*options) = save_opt;
}

void            retain_cmd(int opt, char **cmd)
{
  static char   *save = NULL;

  if (opt == 1)
    save = (*cmd);
  else if (opt == 2)
    (*cmd) = save;
}

void		retain_reverse_case(int opt, int *rev_c)
{
  static int	save;

  if (opt == 1)
    save = (*rev_c);
  else if (opt == 2)
    (*rev_c) = save;
}
