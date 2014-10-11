/*
** main.c for  in /home/collio_v/rendu_svn/42.sh/42
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Sat Apr 27 09:09:51 2013 vincent colliot
** Last update Sun May 26 14:36:11 2013 vincent colliot
*/

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "get.h"
#include "orga.h"
#include "edit_line.h"
#include "string.h"
#include "alias.h"
#include "env.h"

int main(void)
{
  BOOL			tget_fail;
  t_info		info;
  struct termios	test;

  signal(SIGTSTP, SIG_IGN);
  info.alias = NULL;
  environ = env_copy();
  scan_export(&(info.alias));
  info.st = 0;
  info.value = 0;
  if (!get_env("PS1"))
    set_env("PS1", "\033[0;34m█\033[1;31m\033[0m[\033[1;31m\
%u\033[0m]-[\033[1;34m%d\033[0m]-[\033[1;34m%h\033[0m] ╼ [\
 \033[1;34m%/\033[0m ] (\033[1;31mPrompt (setenv ps1 <prompt>)\033[0m)\n\
\033[1;30m>\033[0m ");
  tget_fail = FALSE;
  if (load_tgets_funcs() == -1 || tcgetattr(0, &test) == -1)
    tget_fail = TRUE;
  attribute_options(&(info.termcaps));
  retain_struct_options(1, &(info.termcaps));
  read_cmds(&info, tget_fail);
  destroy_env();
  return (info.value);
}
