/*
** launch.h for 42sh in src
**
** Made by feval_c
** Login   <feval_c@epita.fr>
**
** Started on  Thu Jan  6 20:33:50 2005 feval_c
** Last update Tue Jan 18 18:37:11 2005 gilles durget
*/

#ifndef LAUNCH_H_
# define LAUNCH_H_

# include "ast.h"
# include "global.h"

void	let_s_go(struct s_glob *g, char *str);
void	launch(int argc, char **argv);

#endif /* !LAUNCH_H_ */
