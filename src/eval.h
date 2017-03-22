/*
** eval.h for 42sh in /goinfre/grosli_o-42sh/src
**
** Made by gilles durget
** Login   <durget_g@epita.fr>
**
** Started on  Sun Jan 16 22:08:39 2005 gilles durget
** Last update Mon Jan 17 21:25:22 2005 anass kadiri
*/
#ifndef EVAL_H_
# define EVAL_H_

# include "ast.h"
# include "global.h"

typedef void (*t_built)(char **, struct s_glob *);

/*
** builtins struture
*/
struct          s_built
{
  char          *name;
  t_built       exec;
};

int	eval(struct s_ast_list *ast_list, struct s_glob *g);

#endif /* !EVAL_H_ */
