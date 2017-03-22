/*
** eval.c for 42sh in /goinfre/grosli_o-42sh/src
**
** Made by gilles durget
** Login   <durget_g@epita.fr>
**
** Started on  Sun Jan 16 21:15:49 2005 gilles durget
** Last update Tue Jan 18 20:58:35 2005 anass kadiri
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include "strings.h"
#include "eval.h"
#include "defines.h"
#include "lexer.h"
#include "ast.h"
#include "job.h"
#include "redirections.h"
#include "builtins/builtins.h"

static const struct s_built struct_built[] =
  {
    {"exit", built_exit},
    {"cd", built_cd},
    {"echo", built_echo},
    {"showv", show_vars},
    {"unset", unset_var},
    {"shopt", built_shopt},
    {NULL, NULL}
  };

/*
** exec the builtin if it match
*/
static int	exec_builtin(char *built, char **cmd, struct s_glob *g)
{
  int		i = 0;

  while (struct_built[i].name != NULL)
    {
      if (!strcmp(struct_built[i].name, built))
	{
	  struct_built[i].exec(cmd, g);
	  return 1;
	}
      i++;
    }
  return 0;
}

static int	builtins(struct s_ast *ast, struct s_glob *g)
{
  if (exec_builtin(ast->cmd[0], ast->cmd, g))
    return 1;
  return 0;
}

/**
 ** Evaluates simple commands
 ** @return the return value of the last executed function
 */
int	ev_exec(struct s_ast *ast, struct s_glob *g)
{
  int	pid;
  int	ret = 0;
  int	*backup = NULL;

  if ((backup = redirections(ast->redir)) == NULL)
    return 1;
  if (!builtins(ast, g))
    if (ast->type == COMMAND)
    {
      if ((pid = fork()))
      {
	 waitpid(pid, &ret, 0);
	 redir_restore_backup(backup);
	 return WEXITSTATUS(ret);
      }
      else
	if (execvp(ast->cmd[0], ast->cmd) < 0)
	  {
	    fprintf(stderr, "42$: %s: command not found\n", ast->cmd[0]);
	    exit(127);
	  }
    }
  redir_restore_backup(backup);
  return ret;
}

/**
 ** Evaluates | separated commands
 ** @return the return value of the last executed function
 */
int	ev_pipe(struct s_ast *ast, struct s_glob *g)
{
   int	fd[2];
   int	pid;
   int	ret;
   int	save_fd;

   if (ast->type == EMPTY)
      return ev_exec(ast->left, g);
   else
     {
       pipe(fd);
       if ((pid = fork()))
	 {
	   close(fd[1]);
	   save_fd = dup(STDIN_FILENO);
	   dup2(fd[0], STDIN_FILENO);
	   ev_pipe(ast->right, g);
	   waitpid(pid, &ret, 0);
	   dup2(save_fd, STDIN_FILENO);
	   return WEXITSTATUS(ret);
	 }
       else
	 {
	   close(fd[0]);
	   save_fd = dup(STDOUT_FILENO);
	   dup2(fd[1], STDOUT_FILENO);
	   ret = ev_exec(ast->left, g);
	   dup2(save_fd, STDOUT_FILENO);
	   exit(ret);
	 }
     }
}

/**
 ** Evaluates && or || separated commands
 ** @return the return value of the last executed function
 */
int	ev_logiq(struct s_ast *ast, struct s_glob *g)
{
   int	ret;

   if (ast->type == AMPAMP)
   {
      if ((ret = ev_pipe(ast->left, g)) == 0)
	 return ev_logiq(ast->right, g);
      else
	 return ret;
   }
   else
      if (ast->type == PIPEPIPE)
      {
	 if ((ret = ev_pipe(ast->left, g)) == 1)
	    return ev_logiq(ast->right, g);
	 else
	    return ret;
      }
      else
	 return ev_pipe(ast->left, g);
}

/**
 ** Evaluates starting ast list.
 ** @return the last command return code
 */
int	eval(struct s_ast_list *ast_list, struct s_glob *g)
{
  int	ret = 0;
  int	ok = 1;
  int	pid;
  char	*str;

  if (g->retval)
     return 0;
  while (ok && ast_list != NULL)
  {
    if (ast_list->type == AMP)
    {
      if ((pid = fork()) == 0)
	  exit(ev_logiq(ast_list->ast, g));
      else
      {
	str = vectostr(ast_list->ast->left->left->cmd);
	add_job(g->jobs, pid, str);
	free(str);
      }
    }
    else
      ret = ev_logiq(ast_list->ast, g);
    ast_list = ast_list->next;
  }
  return ret;
}
