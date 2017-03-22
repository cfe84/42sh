/*
** expand.c for 42sh in /goinfre/grosli_o-42sh/src/expansion
**
** Made by olivier grosliere
** Login   <grosli_o@epita.fr>
**
** Started on  Sun Jan 16 15:09:42 2005 olivier grosliere
** Last update Tue Jan 18 18:14:54 2005 olivier grosliere
*/
/**
 ** @file expand.c
 ** Contains the mainframe of expansion module
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include "../global.h"
#include "../ast.h"
#include "expand.h"
#include "paths.h"
#include "unquoting.h"

/**
 ** Returns a string tab containing the translation of the entire chained list
 ** @param cmd The chained list which has to be transformed
 */
char			**get_cmd(struct s_cmd *cmd)
{
  int			i = 0;
  struct s_cmd		*p = NULL;
  char			**args = NULL;

  for (p = cmd; p != NULL; p = p->next)
    i++;
  if ((args = malloc((i + 1) * sizeof (char *))) == NULL)
    return NULL;
  i = 0;
  for (p = cmd; p != NULL; p = p->next)
    args[i++] = remove_quote(p->cmd);
  args[i] = NULL;
  return args;
}

/**
 ** Launches the expansion functions for the current AST, and launches
 ** this function for all the sub-AST contained in the current AST
 ** @param ast The Abstract Syntax Tree to expand
 ** @param g The Global Structure of the program
 */
static void	expand_ast(struct s_ast *ast, struct s_glob *g)
{
  if (ast == NULL)
    return;
  expand_paths(ast, g);
  ast->cmd = get_cmd(ast->cmd_list);
  expand_ast(ast->left, g);
  expand_ast(ast->right, g);
  expand(ast->cond, g);
  expand(ast->list, g);
}

/**
 ** Parses a chained list of ASTs, and launches the expansion for
 ** each AST of the list
 ** @param ast The list of ASTs to expand
 ** @param g The Global Structure of the program
 */
void	expand(struct s_ast_list *ast_list, struct s_glob *g)
{
  if (ast_list == NULL)
    return;
  while (ast_list != NULL)
    {
      expand_ast(ast_list->ast, g);
      ast_list = ast_list->next;
    }
}
