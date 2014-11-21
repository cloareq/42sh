/*
** prompt.c for  in /home/collio_v/rendu_svn/42.sh/42
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Mon May 20 22:23:52 2013 vincent colliot
** Last update Sun May 26 03:36:50 2013 vincent colliot
*/

#include <stdlib.h>
#include <pwd.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include "string.h"
#include "prompt.h"
#include "env.h"
#include "string.h"

static int put_dir()
{
  int   r;
  char	*apwd;

  if ((apwd = getcwd(NULL, 0)) == NULL)
    return (FALSE);
  r = write(1, apwd, my_strlen(apwd));
  return (r);
}

static int date_and_time(BOOL t)
{
  time_t current_time;
  char* c_time_string;

  current_time = time(NULL);
  if (current_time == ((time_t)-1))
    return (0);
  c_time_string = ctime(&current_time);
  if (!c_time_string)
    return (0);
  if (t)
    return (write(1, c_time_string, 10));
  return (write(1, c_time_string + 11, 8));
}

static size_t interpret(char *s, int *add)
{
  register struct passwd *pw;
  register uid_t uid;

  uid = getuid();
  pw = getpwuid(uid);
  if (s[1] == 'd')
    *add = date_and_time(TRUE);
  else if (s[1] == 'h')
    *add = date_and_time(FALSE);
  else if (s[1] == 'u')
    *add = write(1, (pw) ? (pw->pw_name) : ("✗"),
		 my_strlen((pw) ? (pw->pw_name) : ("✗")));
  else if (s[1] == '/')
    *add = put_dir();
  else
    {
      *add = write(1, "%", 1);
      return (1);
    }
  return (2);
}

static size_t inter_prompt(char *s, size_t h, size_t n, int is_color)
{
  int		add;
  BOOL		end;
  size_t	next;

  if ((h && n >= h) || !s[0])
    return (0);
  if ((NMATCH("\\0", s) || s[0] == 27) && my_strilen(s, '[') <
      my_strilen(s, 'm') && my_strilen(s, 'm') < 1 + my_strslen(s + 1, "\\0"))
    is_color = 1;
  if (s[0] == 'm')
    is_color = 0;
  if (is_color == 1 && s[0] == '[')
    add = -((is_color = 2));
  else if (is_color == 2)
    add = 0;
  else
    add = 1;
  end = FALSE;
  if (s[0] == '%')
    next = interpret(s, &add);
  else
    next = print_seq(s, 3, &end);
  if (end)
    return (0);
  return (add + inter_prompt((s + next), h, n + next, is_color));
}

size_t	prompt(BOOL b)
{
  char		*p;

  p = get_env("PS1");
  if (!p)
    p = "------>Prompt test\n[Sla.sh] ";
  if (!b)
    {
      if (last_soccur(p, "\\n") < last_occur(p, '\n', 0))
	p += last_occur(p, '\n', 0) + IN('\n', p);
      else
	p += last_soccur(p, "\\n") + S_IN("\\n", p) * 2;
    }
  if (b && !IN('\n', p) && !S_IN("\\n", p))
    return (0);
  if (last_soccur(p, "\\n") < last_occur(p, '\n', 0))
    return (inter_prompt(p, last_occur(p, '\n', 0) + IN('\n', p), 0, 0));
  else
    return (inter_prompt(p, last_soccur(p, "\\n") + S_IN("\\n", p) * 2, 0, 0));
}
