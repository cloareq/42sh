/*
** toto.h for  in /home/collio_v/rendu_svn/42.sh/42
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Sat May 18 19:06:16 2013 vincent colliot
** Last update Sat May 18 19:09:10 2013 vincent colliot
*/

#ifndef LOL_H_
# define LOL_H_


typedef struct s_sphere{
  struct s_sphere *next;
  int	type;
  char	pos[3];
  char R;
}		t_sphere;

typedef struct s_plan{
  struct s_sphere *next;
  int	type;
  char	pos[3];
  char  rot[3];
  char H;
}		t_plan;

typedef struct s_casual{
  struct s_casual *next;
  int type;
}		t_casual;

