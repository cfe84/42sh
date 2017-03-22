/*
** buffer.h for 42sh in src
**
** Made by feval_c
** Login   <feval_c@epita.fr>
**
** Started on  Wed Jan  5 17:10:05 2005 feval_c
** Last update Wed Jan  5 18:16:21 2005 feval_c
*/

#ifndef BUFFER_H_
# define BUFFER_H_

void	init_buf(struct s_parse *parse, int mode);
int	get_c(struct s_parse *p, int n);
int	get_ch(struct s_parse *p, int n, int lg, char **str);

#endif /* !BUFFER_H_ */
