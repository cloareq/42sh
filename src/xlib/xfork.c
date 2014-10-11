/*
** xfork.c for  in /home/collio_v/rendu_svn/42.sh/42
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Mon May 13 14:19:39 2013 vincent colliot
** Last update Tue May 14 02:15:53 2013 vincent colliot
*/

#include <unistd.h>
#include "string.h"

pid_t	xfork(void)
{
  pid_t	pid;

  if ((pid = fork()) == -1)
    my_putpath("fork(): fail\n", "/dev/tty");
  return (pid);
}
