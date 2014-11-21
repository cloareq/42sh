/*
** lexec.h for  in /home/collio_v/rendu_svn/42.sh/42
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Thu May  2 19:45:44 2013 vincent colliot
<<<<<<< HEAD
** Last update Sun May 26 10:25:12 2013 vincent colliot
=======
** Last update Thu May  9 14:50:49 2013 thomas lecorre
>>>>>>> dcf51d0022527e0cb17c3773071553b5b76de7e7
*/

#ifndef LEXEC_H_
# define LEXEC_H_

# include "fd.h"
# include "flag.h"
# include "get.h"

struct s_exec;

	/* sigandler */
void    catch_after(int);
# define END 5

# define REF 0b01
# define WORD 0b10
typedef struct s_words
{
  char *word;
  struct s_words *next;
}		t_words;

char	**to_tab(t_words*, BOOL*);
/* redir_type */
# define LEFT	0b0001
# define RIGHT	0b0010
# define DLEFT	0b0100
# define DRIGHT	0b1000

/* where type */
# define ON_CANAL 0b01
# define ON_FILE 0b10
typedef struct s_redir{
  FLAG redir;
  FLAG type;
  FD in;
  FD out;
  char *file;
  struct s_redir *next;
}		t_redir;

	/* type */
# define OREDIR 0b100
# define PARENTS 0b01
# define WORDS	0b10
typedef struct s_cmd{
  struct s_redir *redir;
  FLAG	type;
  struct s_words *params;
  /* or */
  struct s_jobs *parents;
}		t_cmd;

typedef struct s_pipes{
  struct s_pipes *next;
  struct s_get	*tmp;
  struct s_cmd	*cmd;
}		t_pipes;

# define OR 0b001
# define AND 0b010
# define NEXT 0b100
typedef struct s_exec{
  FLAG	type;
  struct s_exec *next;
  struct s_pipes *pipes;
  struct s_get  *tmp;
}		t_exec;

# define NONE 0b01
# define JOBS 0b10
typedef struct s_jobs{
  FLAG type;
  struct s_jobs *next;
  struct s_exec *exec;
  struct s_get  *tmp;
}		t_jobs;

#endif
