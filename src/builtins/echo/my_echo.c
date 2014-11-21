/*
** my_echo.c for  in /home/lecorr_b//projets/42sh/42.sh/42/src/builtins
**
** Made by thomas lecorre
** Login   <lecorr_b@epitech.net>
**
** Started on  Tue May 14 18:25:48 2013 thomas lecorre
** Last update Wed May 22 22:19:28 2013 vincent colliot
*/

#include "built.h"
#include "flag.h"
#include "string.h"

static BOOL print(FLAG echo, t_words *link)
{
  BOOL		end;
  size_t	i;

  if (!link)
    return (TRUE);
  end = FALSE;
  i = 0;
  while ((link->word)[i] && !end)
    {
      i += print_seq(link->word + i, echo, &end);
      if (end)
	return (FALSE);
    }
  if (link->next)
    my_putchar(' ', 1);
  return (print(echo, link->next));
}

static BOOL only_option(char *s)
{
  size_t	i;

  i = 0;
  if (!s[i])
    return (FALSE);
  while (s[i])
    {
      if (!IN(s[i], "Een"))
	return (FALSE);
      i++;
    }
  return (TRUE);
}

static void move_flag(t_words *link, t_words **move, FLAG *echo)
{
  char	*catch;

  *move = link;
  if (!link)
    return ;
  catch = link->word;
  if (catch[0] != '-')
    return ;
  else if (catch[1] && only_option(catch + 1))
    {
      while (catch[1] && (catch += 1))
	if (catch[0] == 'e')
	  *echo |= ECHO_E;
	else if (catch[0] == 'E')
	  *echo &= ~ECHO_E;
	else if (catch[0] == 'n')
	  *echo |= ECHO_N;
      move_flag(link->next, move, echo);
    }
}

int	built_echo(t_words *cmd, void *null)
{
  FLAG  echo;

  echo = 0;
  (void)null;
  move_flag(cmd->next, &cmd, &echo);
  if (print(echo, cmd) == FALSE)
    return (EXIT_SUCCESS);
  if (!(echo & ECHO_N))
    my_putstr("\n", 1);
  return (EXIT_SUCCESS);
}
