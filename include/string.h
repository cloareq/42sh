/*
** string.h for  in /home/collio_v/rendu_svn/42.sh/42
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Mon Apr 29 20:25:19 2013 vincent colliot
** Last update Sun May 26 11:22:48 2013 vincent colliot
*/

#ifndef STRING_H_
# define STRING_H_

# include <stdlib.h>
# include <string.h>
# include "bool.h"
# include "fd.h"

# define IN(c, s) ((s)[my_strilen(s, c)] != 0)
# define S_IN(c, s) ((s)[my_strslen(s, c)] != 0)
# define LS_IN(c, s, n) ((s)[my_strnslen(s, c, n)] != 0)
# define MATCH(s, c) ((s && c) ? (!my_strcmp(s, c)) : (0))
# define NMATCH(s, c) (((s) && (c)) ? \
		       (!my_strncmp((s), (c), my_strlen(s))) : (0))
# define FNMATCH(s, c, n) (((s) && (c)) ?					\
		       (!my_strncmp((s), (c), n)) : (0))

	/* s_lenth */
size_t my_strlen(const char*);
size_t my_strilen(const char*, char);
size_t my_strslen(const char*, const char*);
size_t my_sstrlen(const char*, const char*);
size_t lenmatch(const char*, const char*);

	/* s_alloc */
char	*my_strdup(const char*);
void	*my_strndup(const void*, size_t);
char	*my_strcat(const char*, const char*);
char	*my_strncat(const char*, const char*, size_t);
char	*my_stricat(const char*, const char*, char);

	/* s_match */
BOOL	empty(const char*);
BOOL	nempty(const char*, size_t);
size_t	hempty(const char*);
size_t lastoccur_bf(const char*, char, size_t);

	/* s_alloc */
int	my_strcmp(const char*, const char*);
int	my_strncmp(const char*, const char*, size_t);

	/* match */
size_t	my_strnslen(const char*, const char*, size_t);
BOOL	match(const char*, const char*);
BOOL	nmatch(const char*, const char*, size_t);
size_t	last_occur(const char*, char, char);
size_t	last_soccur(const char*, const char*);

	/* s_print */
size_t	my_putchar(char, FD out);
size_t	print_err(const char*);
size_t	my_putstr(const char *s, FD out);
size_t	my_putpath(const char *s, const char *out);

	/* s_memset */
void	*my_memset(void*, int, size_t);
void	*my_realloc(void*, size_t, size_t);

	/* my_atoi */
int	my_getnbr(const char *str);

#endif
