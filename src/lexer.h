/*
** lexer.h for 42sh in /u/a1/grosli_o/projet/grosli_o-42sh
**
** Made by olivier grosliere
** Login   <grosli_o@epita.fr>
**
** Started on  Tue Jan  4 22:19:05 2005 olivier grosliere
** Last update Sat Jan 15 14:14:45 2005 gilles durget
*/
#ifndef LEXER_H_
# define LEXER_H_

/**
 ** \file lexer.h
 ** Data structures for the lexer.
 */

# ifdef SUN
char    *strdup(char *str);
# endif /* !SUN */

# include "global.h"

/**
 ** Buffer structure
 ** @param buf contains the cmd line
 ** @param pos position of the buffer in the file
 ** @param size size of the buffer
 */
struct	s_buf
{
  char	*buf;
  int	pos;
  int	size;
};

/**
 ** Tokens structure
 ** @param la look ahead
 ** @param cur current word
 ** @param la_type type of the look ahead @see defines.h
 ** @param cur_type type of the current word
 ** @param la_redir set if the next character is a redirection char
 ** @param cur_redir set if the next character is a redirection char
 */
struct	s_tokens
{
  char	*la;
  char	*cur;
  int	la_type;
  int	cur_type;
  int	la_redir;
  int	cur_redir;
};

/**
 ** Contains keyword and token value
 ** @param key keyword
 ** @param val token value
 */
struct s_keywords
{
  char	*key;
  int	val;
};

/**
 ** Parse meta-structure
 ** @param interactive mode or non-interactive
 ** @param fd open file descriptor
 ** @param pos position of the cursor in the file
 ** @param stop stop the parsing if stop is set
 ** @param buf buffer structure \see s_buf
 ** @param tokens token structure \see s_tokens
 */
struct			s_parse
{
  int			mode;
  int			fd;
  int			pos;
  int			stop;
  struct s_buf		buf;
  struct s_tokens	tokens;
};

int	curt(struct s_parse *p);
int	lat(struct s_parse *p);
char	*cur(struct s_parse *p);
char	*la(struct s_parse *p);
int	accept(struct s_parse *p, struct s_glob *g);
int	curr(struct s_parse *p);
int	lar(struct s_parse *p);

#endif /* !LEXER_H_ */
