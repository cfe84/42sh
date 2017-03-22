/*
** built_shopt.h for built_shopt in /u/a1/kadiri_a/tmp/grosli_o-42sh/src/builtins
**
** Made by anass kadiri
** Login   <kadiri_a@epita.fr>
**
** Started on  Mon Jan 17 19:51:53 2005 anass kadiri
** Last update Tue Jan 18 19:10:37 2005 anass kadiri
*/

#ifndef BUILT_SHOPT_H_
# define BUILT_SHOPT_H_

/*
** options structure
** for shopt builtin
*/
struct	s_shopt_opt
{
  int	s;
  int	q;
  int	u;
};

/*
** structure of builtins shopt
*/
struct	s_shopt
{
  char	*name;
  int	on;
};

void	init_shopt(struct s_glob *);
void	built_shopt(char **, struct s_glob *);

#endif /* !BUILT_SHOPT_H_ */
