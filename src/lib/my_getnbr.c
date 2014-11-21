/*
** my_getnbr.c for my_getnbr in /home/lecorr_b//piscine/Jour04/getnbr
**
** Made by thomas lecorre
** Login   <lecorr_b@epitech.net>
**
** Started on  Fri Oct 26 14:50:00 2012 thomas lecorre
** Last update Sun May 19 05:36:01 2013 vincent colliot
*/

#include "built.h"

int	my_getnbr(const char *str)
{
  int	signe;
  int	pos;
  int	nb;

  signe = 1;
  pos = 0;
  nb = 0;
  while (str[pos] == '+' || str[pos] == '-')
    {
      if (str[pos] == '-')
	signe = signe * -1;
      pos = pos + 1;
    }
  str = str + pos;
  pos = 0;
  while (str[pos] >= '0' && str[pos] <= '9')
    {
      nb = nb * 10;
      nb = nb - (str[pos] - '0');
      pos = pos + 1;
    }
  return (nb * signe * -1);
}
