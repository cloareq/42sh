/*
** subdivide.h for  in /home/collio_v/rendu_svn/42.sh/42
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Mon May  6 21:50:16 2013 vincent colliot
** Last update Sun May 26 10:52:17 2013 vincent colliot
*/

#ifndef SUBDIVIDE_H_
# define SUBDIBIDE_H_

#include "alias.h"
#include "exec.h"

t_get	*subdivide(char*, t_get*, char**);
size_t subdiv(char*, char**);
t_get	*comment(t_get *, t_get *);
BOOL	seed_alias(char*, t_alias*, char**);
BOOL	grow_hist(char*, char**, size_t, t_info*);
BOOL	grow_var(char *, char **, size_t, t_info*);
t_get *echappment(char *, t_get *, char **, BOOL);

#endif
