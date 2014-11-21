/*
** built.c for 42 in /home/lecorr_b//projets/42sh/42.sh/42/include
**
** Made by thomas lecorre
** Login   <lecorr_b@epitech.net>
**
** Started on  Fri May  3 17:56:39 2013 thomas lecorre
** Last update Tue May 21 23:27:00 2013 vincent colliot
*/

#ifndef	BUILT_H__
#define BUILT_H__

# include "alias.h"
# include "lexec.h"

typedef struct s_call
{
  char	*name;
  int	(*ptr)(t_words *, void *);
} t_call;

# define ECHO_N	0b001
# define ECHO_E 0b010

	/* call */
t_call	*builtins(void);

	/* echo */
size_t	print_seq(char*, FLAG, BOOL*);
int	built_echo(t_words *, void *);

	/* alias */
int	built_alias(t_words*, void *);
int	mod_alias(char*, char*, t_alias**);

	/* env */
int	built_env(t_words*, void*);
BOOL	print_help(void);
int	exec_env(t_words*, char**);
char	*seek_cmd(char*, char**);
void	destroy_env(void);
char	**env_copy(void);

	/* setenv */
int	built_setenv(t_words *, void *);
int	switch_env(char**, BOOL);

	/* unsetenv */
int	built_unsetenv(t_words *, void *);

	/* exit */
int	built_exit(t_words *, void *);

	/* cd */
int	built_cd(t_words *, void *);

	/* exit */
int	built_exit(t_words *,void *);

	/* unalias */
int	built_unalias(t_words *,void *);

#endif
