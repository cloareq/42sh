/*
** load_term_settings.c for 42 in /home/thomas_1//Projets/42sh
**
** Made by pierre-yves thomas
** Login   <thomas_1@epitech.net>
**
** Started on  Fri Apr 26 14:32:24 2013 pierre-yves thomas
** Last update Sun May 26 13:38:15 2013 vincent colliot
*/

#include <stdlib.h>
#include "edit_line.h"
#include "string.h"
#include "env.h"

void    attribute_options(t_options *options)
{
  options->clear = tgetstr("cl", NULL);
  options->clean_end = tgetstr("cd", NULL);
  options->reverse = tgetstr("mr", NULL);
  options->forward = tgetstr("me", NULL);
  options->cursor = tgetstr("cm", NULL);
  options->invi_cursor = tgetstr("vi", NULL);
  options->visi_cursor = tgetstr("ve", NULL);
  options->up_cursor = tgetstr("up", NULL);
  options->down_cursor = tgetstr("do", NULL);
  retain_struct_options(1, options);
}

int     modify_terminal(struct termios *opt)
{
  opt->c_lflag &= ~ICANON;
  opt->c_lflag &= ~ECHO;
  if (tcsetattr(0, TCSANOW, opt) == -1)
    return (1);
  return (0);
}

int	init_termios(struct termios *set, struct termios *unset)
{
  if (tcgetattr(0, set) == -1 ||
      tcgetattr(0, unset) == -1)
    return (-1);
  if (modify_terminal(set) == -1)
    return (-1);
  return (0);
}

char	*unset_termios(struct termios *unset)
{
  tcsetattr(0, TCSANOW, unset);
  return (NULL);
}

int	load_tgets_funcs()
{
  if (tgetent(NULL, "xterm") != 1)
    {
      if (tgetent(NULL, get_env("TERM")) != 1)
	{
	  my_putstr("Fail on tgetent", 2);
	  return (-1);
	}
    }
  set_env("TERM", "xterm");
  return (0);
}
