/*
** orga.h for  in /home/collio_v/rendu_svn/42.sh/42
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Wed May  8 23:28:36 2013 vincent colliot
** Last update Sun May 26 10:42:13 2013 vincent colliot
*/

#ifndef ORGA_H_
# define ORGA_H_

# include "lexec.h"

/* prim'orga */
t_jobs  *orga(t_get*, char**, BOOL*, BOOL);

/* jobs */
t_jobs *get_jobs(t_get*, t_jobs*, char**);

/* exec */
t_exec *get_exec(t_get*, t_exec*, char**);

/* pipe */
BOOL	get_pipe(t_exec*, char**);

/* cmd */
BOOL	get_cmd(t_pipes*, char**, t_pipes*, BOOL);
BOOL	cmd_part(t_get*, t_get**, t_cmd*, char**);
t_words	*interpret_cmd(t_get*, t_get**, char**, t_words**);
t_words	*interpret_params(t_get*, t_get**, t_words**, char**);
t_words	*list_cmd(t_get *, t_cmd *, t_words *, char **);
BOOL	add_redir(t_get *, t_get **, char **, t_cmd *);

/* redir */
t_redir	*redir_part(t_get*, t_get**, char**);

/* help */
BOOL    lvl_parents(t_get**, char**);
BOOL	match_parents(t_get**, char**);
BOOL	match_them(char*, char*, t_words**, BOOL*);
BOOL	add_and_last(char*, char*, t_words**, BOOL*);

/* nullify */
BOOL    nullify_cmd(t_cmd *);
BOOL	nullify_exec(t_exec*);
BOOL	nullify_pipes(t_pipes*);
BOOL    nullify_words(t_get*);
BOOL	nullify_redir(t_redir*);
void nullify_cmd_words(t_words*);
BOOL    nullify_jobs(t_jobs*, BOOL);
BOOL	nullify_all_pipes(t_pipes*);
BOOL	nullify_all_in_pipes(t_pipes*);
BOOL	nullify_all_exec(t_exec*);
void	*nullify_all_jobs(t_jobs*);
void	rm_words(t_get*);

#endif
