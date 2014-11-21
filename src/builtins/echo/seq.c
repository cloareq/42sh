/*
** seq.c for  in /home/collio_v/rendu_svn/42.sh/42/src/builtins/env
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Sat May 18 22:56:01 2013 vincent colliot
** Last update Wed May 22 23:01:51 2013 vincent colliot
*/

#include "built.h"
#include "flag.h"
#include "string.h"

static size_t plus_seq(char *seq, int mult, size_t l)
{
  unsigned char	n;
  size_t	i;

  n = 0;
  i = 0;
  if (mult == 8)
    while (i < l && (seq[i] >= '0' && seq[i] < '8'))
      n = n * mult + seq[i++] - '0';
  if (mult == 16)
    while (i < l && ((seq[i] >= '0' && seq[i] <= '9') ||
		     (seq[i] >= 'a' && seq[i] <= 'f') ||
		     (seq[i] >= 'A' && seq[i] <= 'F')))
      if (seq[i] >= '0' && seq[i] <= '9')
	n = n * mult + seq[i++] - '0';
      else if (seq[i] >= 'A' && seq[i] <= 'F')
	n = n * mult + seq[i++] - 'A' + 10;
      else
	n = n * mult + seq[i++] - 'a' + 10;
  if (i)
    my_putchar((unsigned char)n, 1);
  return (i);
}

static size_t print_seq2(char *seq, FLAG echo)
{
  if (NMATCH("\\n", seq))
    return (1 + my_putchar('\n', 1));
  else if (NMATCH("\\r", seq) && !(echo & 4))
    return (1 + my_putchar('\r', 1));
  else if (NMATCH("\\t", seq) && !(echo & 4))
    return (1 + my_putchar('\t', 1));
  else if (NMATCH("\\v", seq) && !(echo & 4))
    return (1 + my_putchar('\v', 1));
  return (my_putchar(*seq, 1));
}

size_t print_seq(char *seq, FLAG echo, BOOL *end)
{
  if (!(echo & ECHO_E))
    return (my_putchar(*seq, 1));
  if (NMATCH("\\0", seq))
    return (2 + plus_seq(seq + 2, 8, 3));
  if (NMATCH("\\x", seq))
    return (2 + plus_seq(seq + 2, 16, 2));
  if (NMATCH("\\\\", seq))
    return (1 + my_putchar('\\', 1));
  else if (NMATCH("\\a", seq) && !(echo & 4))
    return (1 + my_putchar('\a', 1));
  else if (NMATCH("\\b", seq) && !(echo & 4))
    return (1 + my_putchar('\b', 1));
  else if (NMATCH("\\c", seq) && !(echo & 4))
    return (*end = TRUE);
  else if (NMATCH("\\e", seq) && !(echo & 4))
    return (1 + my_putchar('\e', 1));
  else if (NMATCH("\\f", seq) && !(echo & 4))
    return (1 + my_putchar('\f', 1));
  return (print_seq2(seq, echo));
}
