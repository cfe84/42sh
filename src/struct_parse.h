/*
** struct_parse.h for 42sh in src
**
** Made by feval_c
** Login   <feval_c@epita.fr>
**
** Started on  Thu Jan  6 19:30:06 2005 feval_c
** Last update Mon Jan 17 20:41:50 2005 gilles durget
*/

#ifndef STRUCT_PARSE_H_
# define STRUCT_PARSE_H_

# include "global.h"

struct s_parse		*create_parse(int mode, char *file, struct s_glob *g);
void			destroy_parse(struct s_parse *p);
struct s_ast_list	*add_item(struct s_ast_list *astl,
				  struct s_ast_list *new);

#endif /* !STRUCT_PARSE_H_ */
