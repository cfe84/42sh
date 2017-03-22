/*
** display.c for 42sh in /u/a1/grosli_o/projet/grosli_o-42sh
**
** Made by olivier grosliere
** Login   <grosli_o@epita.fr>
**
** Started on  Sun Jan  9 19:04:09 2005 olivier grosliere
** Last update Tue Jan 18 18:16:44 2005 gilles durget
*/
#include <stdlib.h>
#include <stdio.h>
#include "display.h"
#include "is.h"
#include "defines.h"

/**
 ** Unprintable tokens.
 */
static const char	*unprint[] =
{
   "END OF FILE",
   "ERROR",
   "WORD",
   "COMMAND",
   "EMPTY",
   "FUNC"
};

static void	disp_cmd(struct s_ast *ast)
{
  int		i = 0;
  char		**cmd = ast->cmd;

  if (!cmd)
    return;
  printf("    - commands : ");
  while (*cmd)
    printf("%d. %s ", ++i, *(cmd++));
  printf("\n");
}

static void	       	disp_redir(struct s_ast *ast)
{
  int			i = 0;
  struct s_redir	*redir = ast->redir;

  if (!redir)
    return;
  printf("    - redirections : ");
  while (redir != NULL)
    {
      printf("%d. type: %d, fd: %d, file: %s ",
	     ++i, redir->type, redir->fd, redir->redir);
      redir = redir->next;
    }
  printf("\n");
}

/**
 ** Prints a token.
 */
static const char	       	*nat_token(int type)
{
   if (type >= 0 && type < NB_PRINT_TOKENS)
      return get_kw()[type].key;
   else
      if (type >= NB_PRINT_TOKENS &&
	  type < NB_PRINT_TOKENS + NB_UNPRINT_TOKENS)
	 return unprint[type - NB_PRINT_TOKENS];
      else
	 return "UNKNOWN";
}

/*
** Displays an ast (infix parsing).
** @param ast the ast
** @param level node number
*/
void	disp_ast(struct s_ast *ast, int level)
{
  if (ast == NULL)
    return;
  printf("  * AST level %d\n", level);
  printf("    - token : %s (%d)\n", nat_token(ast->type), ast->type);
  if (ast->not)
    printf("    - not : %d\n", ast->not);
  if (ast->varname != NULL)
    printf("    - varname : %s\n", ast->varname);
  disp_cmd(ast);
  disp_redir(ast);
  disp_ast_list(ast->cond, "condition", level);
  disp_ast_list(ast->list, "sublist", level);
  printf("\n");
  disp_ast(ast->left, 2 * level);
  disp_ast(ast->right, 2 * level + 1);
}

/*
** Displays an ast list.
** @param ast_list the ast_list
** @param where context string to display
** @param level node level
*/
void	disp_ast_list(struct s_ast_list *ast_list, char *where, int level)
{
  if (ast_list == NULL)
    return;
  printf("<+%d> ast_list for %s\n", level, where);
    while (ast_list != NULL)
    {
       printf("@ list separator type %s (%d)\n", nat_token(ast_list->type),
	      ast_list->type);
       disp_ast(ast_list->ast, 1);
       ast_list = ast_list->next;
    }
  printf("<-%d> end of ast_list for %s\n", level, where);
}
