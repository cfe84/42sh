/*
** is.h for 42sh in /u/a1/durget_g/grosli_o-42sh/src
**
** Made by gilles durget
** Login   <durget_g@epita.fr>
**
** Started on  Fri Jan  7 14:51:16 2005 gilles durget
** Last update Fri Jan 14 01:23:42 2005 gilles durget
*/
#ifndef IS_H_
# define IS_H_

# include "lexer.h"

/*
** Functions in 'is.c'
*/
int			is_stop(struct s_parse *p, int n);
int			is_blank(struct s_parse *p, int n);
char			is_quote(struct s_parse *p, int n);
int			is_keyword(struct s_parse *p);
const struct s_keywords	*get_kw(void);

/*
** Functions in 'is2.c'
*/
int		is_redir(int type);
int		is_num(char *s);

#endif /* !IS_H_ */
