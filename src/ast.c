/*
** ast.c for 42sh in /u/a1/grosli_o/projet/grosli_o-42sh/src
**
** Made by olivier grosliere
** Login   <grosli_o@epita.fr>
**
** Started on  Sat Jan  8 17:12:41 2005 olivier grosliere
** Last update Tue Jan 18 17:45:40 2005 feval_c
*/
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ast.h"
#include "defines.h"

#ifdef SUN
char	*strdup(const char *a);
#endif /* !SUN */

struct s_ast	*create_ast(int type)
{
  struct s_ast	*res = NULL;

  if ((res = malloc(sizeof (struct s_ast))) == NULL)
    return NULL;
  res->type = type;
  res->left = NULL;
  res->right = NULL;
  res->cond = NULL;
  res->redir  = NULL;
  res->list = NULL;
  res->cmd = NULL;
  res->cmd_list = NULL;
  res->varname = NULL;
  res->not = 0;
  return res;
}

struct s_ast_list	*destroy_ast_list(struct s_ast_list *a)
{
  if (a == NULL)
    return NULL;
  destroy_ast(a->ast);
  destroy_ast_list(a->next);
  free(a);
  return NULL;
}

static void	destroy_cmd_list(struct s_cmd *a)
{
  if (a == NULL)
    return;
  if (a->cmd != NULL)
    free(a->cmd);
  destroy_cmd_list(a->next);
  free(a);
}

struct s_ast	*destroy_ast(struct s_ast *a)
{
  int		i = 0;

  if (a == NULL)
    return NULL;
  destroy_ast(a->left);
  destroy_ast(a->right);
  destroy_redir(a->redir);
  destroy_ast_list(a->list);
  destroy_ast_list(a->cond);
  if (a->cmd != NULL)
  {
    while (a->cmd[i] != NULL)
      free(a->cmd[i++]);
    free(a->cmd);
  }
  if (a->varname != NULL)
    free(a->varname);
  destroy_cmd_list(a->cmd_list);
  free(a);
  return NULL;
}
