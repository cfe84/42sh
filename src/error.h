/*
** error.h for 42sh in src
**
** Made by feval_c
** Login   <feval_c@epita.fr>
**
** Started on  Thu Jan  6 20:13:57 2005 feval_c
** Last update Thu Jan 13 22:58:35 2005 olivier grosliere
*/

#ifndef ERROR_H_
# define ERROR_H_

# include "lexer.h"
# include "global.h"

struct	s_error
{
  int	errnum;
  char	*msg;
  int	ret;
  int	afftoken;
};

void	my_exit(int retval, struct s_parse *p);
void	error_msg(int errnum, struct s_glob *g, struct s_parse *p, char *ctx);

#endif /* !ERROR_H_ */
