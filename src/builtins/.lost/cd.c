/*
** cd.c for cd in /home/cloare_q//42.sh/42/src/builtins
**
** Made by quentin cloarec
** Login   <cloare_q@epitech.net>
**
** Started on  Mon May 13 11:58:06 2013 quentin cloarec
** Last update Fri May 17 17:16:20 2013 vincent colliot
*/

#include <unistd.h>
#include "stdlib.h"
#include "env.h"
#include "built.h"
#include "string.h"

char	*put_pwd(char *s)
{
  char *pwd;
  int	i;
  int	j;

  j = 0;
  if ((pwd = xmalloc(sizeof(char) * (my_strlen(s) + 5))) == NULL)
    return (NULL);
  pwd[0] = 'O';
  pwd[1] = 'L';
  pwd[2] = 'D';
  pwd[3] = '_';
  pwd[4] = 'P';
  pwd[5] = 'W';
  pwd[6] = 'D';
  pwd[7] = ' ';
  i = 8;
  while (s[j])
    pwd[i++] = s[j++];
  return (pwd);
}

int	just_cd(t_words *cmd)
{
  if ((chdir(get_env("HOME"))) == -1)
    {
      print_err("CHDIR ERROR\n");
      return (EXIT_FAILURE);
    }
}

int	len_chain(t_words *cmd)
{
  t_words *tmp;
  int	i;

  i = 0;
  while (tmp != NULL)
    {
      i++;
      tmp = tmp->next;
    }
  return (i);
}

void	add_old_env(t_words *cmd, char *pwd)
{
  cmd->word = "setenv";
  cmd->next->word = "OLD_PWD";
  cmd->next->next->word = pwd;
  cmd->next->next->next = NULL;
  setenv(cmd);
}

void	add_new_env(t_words *cmd, char *pwd)
{
  cmd->word = "setenv";
  cmd->next->word = "PWD";
  cmd->next->next->word = pwd;
  cmd->next->next->next = NULL;
  setenv(cmd);
}

int	cd(t_words *cmd, void *alias)
{
  int	i;
  char	*pwd;

  cmd = cmd->next;
  if ((MATCH(cmd->word, "cd") == 1) && (len_chain(cmd) == 1))
    {
      just_cd(cmd);
      pwd = get_env("HOME");
      add_old_env(pwd);
      add_new_env(pwd)
    }
  else if (MATCH(cmd->word, "cd") == 1 && (len_chain(cmd) == 2))
    {
      cmd = cmd->next;
      if (MATCH(cmd->word, "-") == 1)
	{
	  if((get_env("OLD_PWD")) != NULL)
	    {
	      if ((chdir(get_env("OLD_PWD"))) == -1)
		{
		  print_err("CHDIR ERROR\n");
		  return (EXIT_FAILURE);
		}
	      pwd = get_env("PWD");
	      add_new_env(pwd);
	      add_old_env(pwd);
	    }
	}
      else
	{
	  cmd = cmd->next;
	  if ((chdir(cmd->word)) == -1)
	    {
	      print_err("CHDIR ERROR\n");
	      return (EXIT_FAILURE);
	    }
	  pwd = cmd->word;
	  add_new_env(pwd);
	  add_old_env(pwd);
	}
    }
}
