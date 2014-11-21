/*
** show_cmd.c for 42 in /home/thomas_1//Projets/42sh
**
** Made by pierre-yves thomas
** Login   <thomas_1@epitech.net>
**
** Started on  Mon May  6 17:57:14 2013 pierre-yves thomas
** Last update Sat May 25 16:51:26 2013 pierre-yves thomas
*/

#include <sys/ioctl.h>
#include "string.h"
#include "edit_line.h"
#include "prompt.h"

void                    go_up_of_cmd_high(char *cmd, int len, t_options opt)
{
  int                   high;
  struct winsize        ws;

  ioctl(0, TIOCGWINSZ, &ws);
  high = (my_strlen(cmd) + len) / ws.ws_col;
  while (--high >= 0)
    my_putstr(opt.up_cursor, 1);
}

static void		aff_str_cmd(int fd, char *str)
{
  if (fd == 0)
    my_putstr(str, 1);
  else
    my_putstr(str, fd);
}

static void		aff_char_cmd(int fd, char chr)
{
  if (fd == 0)
    my_putchar(chr, 1);
  else
    my_putchar(chr, fd);
}

void			show_cmd(char key, int fd, char *cmd, int reverse_case)
{
  int			i;
  t_options		options;
  int			len;

  i = -1;
  len = prompt(FALSE);
  retain_struct_options(2, &options);
  while (cmd[++i] != '\0')
    {
      if (key != 10 && i == reverse_case && cmd[i] != '\t')
	aff_str_cmd(fd, options.reverse);
      aff_char_cmd(fd, cmd[i]);
	aff_str_cmd(fd, options.forward);
    }
  if (key != 10 && i == reverse_case)
    aff_str_cmd(fd, options.reverse);
  aff_char_cmd(fd, ' ');
  aff_str_cmd(fd, options.forward);
  if (key != 10)
    {
      aff_str_cmd(fd, options.clean_end);
      go_up_of_cmd_high(cmd, len, options);
    }
  aff_str_cmd(fd, "\r");
}
