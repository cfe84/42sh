/*
** expand.h for 42sh in /goinfre/grosli_o-42sh/src/expansion
**
** Made by olivier grosliere
** Login   <grosli_o@epita.fr>
**
** Started on  Sun Jan 16 15:09:07 2005 olivier grosliere
** Last update Mon Jan 17 20:13:05 2005 olivier grosliere
*/
#ifndef		EXPAND_H_
# define	EXPAND_H_

# include	"../ast.h"

void	expand(struct s_ast_list *ast_list, struct s_glob *g);

#endif	    /* !EXPAND_H_ */
