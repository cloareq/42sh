/*
** info.h for  in /home/collio_v/rendu_svn/42.sh/42
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Wed May 22 08:40:58 2013 vincent colliot
** Last update Wed May 22 08:44:09 2013 vincent colliot
*/

#ifndef INFO_H_
# define INFO_H_

# define EXEC_H_

# include "status.h"
# include "bool.h"
# include "alias.h"

typedef struct s_info
{
  t_history		*hist;
  struct s_options	termcaps;
  STATUS		st;
  STATUS		value;
  t_alias		*alias;
}			t_info;

#endif
