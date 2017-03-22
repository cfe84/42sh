/*
** built_echo.h for built_echo in /u/a1/kadiri_a/tmp/grosli_o-42sh/src/builtins
**
** Made by anass kadiri
** Login   <kadiri_a@epita.fr>
**
** Started on  Sun Jan 16 15:55:27 2005 anass kadiri
** Last update Mon Jan 17 21:16:42 2005 anass kadiri
*/

#ifndef BUILT_ECHO_H_
# define BUILT_ECHO_H_

/*
** option structure
** for echo builtin
*/
struct	s_opt
{
  int	n;
  int	e;
  int	E;
};

/*
** structure of
** escaped characters
*/
struct	s_esc
{
  char	c;
  char	*str;
};

void	built_echo(char **, struct s_glob *);

#endif /* !BUILT_ECHO_H_ */
