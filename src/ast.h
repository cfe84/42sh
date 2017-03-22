/*
** ast.h for 42sh in src
**
** Made by feval_c
** Login   <feval_c@epita.fr>
**
** Started on  Fri Jan  7 20:15:55 2005 feval_c
** Last update Tue Jan 18 17:45:40 2005 feval_c
*/

#ifndef AST_H_
# define AST_H_

# include "redirections.h"

/**
 ** @param cmd a command token
 */
struct			s_cmd
{
  char			*cmd;
  struct s_cmd		*next;
};

struct			s_ast_list;

/**
 ** @param type stores the type of the node. (TYPE_*)
 ** @param cmd command and arguments
 ** @param cond condition.
 ** @param not invert the return value
 */
struct			s_ast
{
  int			type;
  struct s_ast		*left;
  struct s_ast		*right;
  struct s_redir	*redir;
  struct s_ast_list	*list;
  struct s_ast_list	*cond;
  struct s_cmd		*cmd_list;
  char			**cmd;
  char			*varname;
  int			not;
};

/**
 ** @param ast ast to evaluate
 ** @param next pointer to the next ast
 ** @param type contains the token between the command and the next one
 */
struct			s_ast_list
{
  struct s_ast		*ast;
  struct s_ast_list	*next;
  int			type;
};

struct s_ast		*create_ast(int type);
struct s_ast_list	*destroy_ast_list(struct s_ast_list *a);

#endif /* !AST_H_ */
