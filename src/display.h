/*
** display.h for 42sh in /u/a1/grosli_o/projet/grosli_o-42sh
**
** Made by olivier grosliere
** Login   <grosli_o@epita.fr>
**
** Started on  Sun Jan  9 19:38:10 2005 olivier grosliere
** Last update Sun Jan  9 20:28:13 2005 olivier grosliere
*/
#ifndef DISPLAY_H_
# define DISPLAY_H_

# include "ast.h"

void	disp_ast(struct s_ast *ast, int level);
void	disp_ast_list(struct s_ast_list *ast_list, char *where, int level);

#endif /* !DISPLAY_H_ */
