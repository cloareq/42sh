/*
** exec_form.c for  in /home/collio_v/rendu_svn/42.sh/42
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Sun May 12 01:40:28 2013 vincent colliot
** Last update Sun May 26 16:47:08 2013 vincent colliot
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include "lexec.h"
#include "xmalloc.h"
#include "status.h"
#include "string.h"
#include "env.h"
#include "father.h"

static int	stop(BOOL s)
{
  static BOOL k = FALSE;

  usleep(5);
  if (s == FALSE && k == TRUE)
    {
      k = FALSE;
      return (TRUE);
    }
  if (s == INIT)
    k = FALSE;
  if (TRUE == s)
    k = TRUE;
  return (k);
}

static STATUS	clean_signal(char *prog, STATUS signal, char **tab)
{
  if (signal == SIGILL || signal == SIGABRT || signal == SIGFPE ||
      signal == SIGSEGV || signal == SIGTERM || signal == SIGINT)
    my_putstr(prog, 2);
  if (signal == SIGILL)
    my_putstr(" : Illegal instruction\n", 2);
  else if (signal == SIGABRT)
    my_putstr(" : Aborted\n", 2);
  else if (signal == SIGFPE)
    my_putstr(" : Floating exeception\n", 2);
  else if (signal == SIGSEGV)
    my_putstr(" : Segmentation fault\n", 2);
  else if (signal == SIGTERM)
    my_putstr(" : Terminated\n", 2);
  else if (signal == SIGINT)
    my_putstr(" : Killed\n", 2);
  free(tab);
  return (signal);
}

void	catch_more(int num)
{
  if (num == SIGINT)
    stop(TRUE);
}

void	init(void)
{
  signal(SIGTTIN, SIG_IGN);
  signal(SIGTTOU, SIG_IGN);
  stop(INIT);
}

STATUS		exec_form(t_words *list, BOOL *sys_fail, int *value)
{
  STATUS	st;
  pid_t		pid;
  char		**tab;

  init();
  if ((tab = to_tab(list, sys_fail)) == NULL)
    return (EXIT_FAILURE + !((*sys_fail) = TRUE));
  if ((pid = fork()) == -1)
    return (EXIT_FAILURE + !((*sys_fail) = TRUE));
  if (pid)
    {
      signal(SIGINT, catch_more);
      while (waitpid(pid, &st, WNOHANG) != -1)
	if (stop(FALSE) == TRUE)
	  kill(pid, SIGINT);
      tcsetpgrp(0, getpgrp());
    }
  else
    {
      setpgrp();
      tcsetpgrp(0, getpgrp());
      if (execve(tab[0], tab, environ) == -1)
	return ((*value = EXIT_FAILURE) + !((*sys_fail) = TRUE) +
		!fprintf(stderr, "%s: Command not found\n", tab[0]));
    }
  return (0 != (*value = WEXITSTATUS(clean_signal(tab[0], st, tab))));
}
