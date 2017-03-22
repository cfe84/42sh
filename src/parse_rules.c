/*
** parse_rules.c for 42sh in /goinfre/grosli_o-42sh/src
**
** Made by gilles durget
** Login   <durget_g@epita.fr>
**
** Started on  Fri Jan 14 00:39:14 2005 gilles durget
** Last update Tue Jan 18 19:01:39 2005 gilles durget
*/
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "parser.h"
#include "defines.h"
#include "error.h"

/**
 ** @var res->list receives the 'else' commands list. (If curword = ELSE)
 ** @var res->cond receives the condition body of 'elif'
 ** @var res->right receives the 'elif' commands list.
 */
static struct s_ast	*else_clause(struct s_parse *p, struct s_glob *g)
{
   struct s_ast		*res = NULL;

   if (g->retval)
      return NULL;
   if (curt(p) == ELSE)
   {
      res = create_ast(ELSE);
      accept(p, g);
      if ((res->list = compound_list(p, g)) == NULL)
	 return NULL;
   }
   else
      if (curt(p) == ELIF)
      {
	 res = create_ast(ELIF);
	 accept(p, g);
	 if ((res->cond = compound_list(p, g)) == NULL)
	    return NULL;
	 res->right = else_clause(p, g);
      }
   return res;
}

static struct s_ast	*rule_if_sub(struct s_parse *p,
				     struct s_glob *g,
				     struct s_ast *res)
{
   if (g->retval)
      return NULL;
   if ((res->list = compound_list(p, g)) == NULL)
      return NULL;
   if ((curt(p) == ELSE || curt(p) == ELIF))
      if ((res->right = else_clause(p, g)) == NULL)
	 return NULL;
   if (curt(p) == FI)
      accept(p, g);
   else
   {
      error_msg(P_FI_EX, g, p, "rule_if");
      return NULL;
   }
   return res;
}

/**
 ** @var cond receives condition list
 ** @var res->list receives 'then' commands list
 ** @var res->right receives 'else' node
 */
struct s_ast		*rule_if(struct s_parse *p, struct s_glob *g)
{
   struct s_ast		*res = NULL;

   if (g->retval)
      return NULL;
   if (curt(p) == IF)
   {
      res = create_ast(curt(p));
      accept(p, g);
      if ((res->cond = compound_list(p, g)) == NULL)
	 return NULL;
      if (curt(p) == THEN && accept(p, g))
	 return rule_if_sub(p, g, res);
      else
      {
	 error_msg(P_THEN_EX, g, p, "rule_if 2");
	 return NULL;
      }
   }
   return res;
}

/**
 ** @var res->list receives the commands contained between DO and DONE
 */
static struct s_ast	*do_group(struct s_parse *p, struct s_glob *g)
{
   struct s_ast		*res = NULL;

   if (g->retval)
      return NULL;
   if (curt(p) == DO)
   {
      res = create_ast(curt(p));
      accept(p, g);
      if ((res->list = compound_list(p, g)) == NULL)
	 return NULL;
      if (curt(p) == DONE)
	 accept(p, g);
      else
      {
	 error_msg(P_DONE_EX, g, p, "do_group");
	 return NULL;
      }
   }
   else
      error_msg(P_DO_EX, g, p, "do_group 2");
   return res;
}

/**
 ** @var res->cond receives the condition of until
 ** @var res->left receives the commands to execute in UNTIL
 */
struct s_ast		*rule_until(struct s_parse *p, struct s_glob *g)
{
   struct s_ast		*res = NULL;

   if (g->retval)
      return NULL;
   if (curt(p) == UNTIL)
   {
      res = create_ast(curt(p));
      accept(p, g);
      if ((res->cond = compound_list(p, g)) == NULL)
	 return NULL;
      if ((res->left = do_group(p, g)) == NULL)
	 return NULL;
   }
   return res;
}

/**
 ** @var res->cond receives the condition of while
 ** @var res->left receives the commands to execute in WHILE
 */
struct s_ast		*rule_while(struct s_parse *p, struct s_glob *g)
{
   struct s_ast		*res = NULL;

   if (g->retval)
      return NULL;
   if (curt(p) == WHILE)
   {
      res = create_ast(curt(p));
      accept(p, g);
      if ((res->cond = compound_list(p, g)) == NULL)
	 return NULL;
      if ((res->left = do_group(p, g)) == NULL)
	 return NULL;
   }
   return res;
}

static struct s_ast		*rule_for_sub(struct s_parse *p,
					      struct s_glob *g,
					      struct s_ast *res)
{
   int				size = 0;

   if (g->retval)
      return NULL;
   if (curt(p) == IN && accept(p, g))
   {
      while (curt(p) == WORD)
      {
	 res->cmd = realloc(res->cmd, (size + 1) * sizeof (char *));
	 res->cmd[size++] = strdup(cur(p));
	 accept(p, g);
      }
      if (res->cmd != NULL && (curt(p) == PVIRG || curt(p) == EOL))
	 accept(p, g);
      else
      {
	 error_msg(P_TOKEN_ERROR, g, p, "rule_for 2");
	 return NULL;
      }
      while (curt(p) == EOL)
	 accept(p, g);
   }
   res->left = do_group(p, g);
   return res;
}

/**
 ** @var res->varname receives the name of the variable of the FOR loop
 ** @var res->cmd receives the "IN" contents
 ** @var res->left receives the commands to execute in FOR
 */
struct s_ast		*rule_for(struct s_parse *p, struct s_glob *g)
{
   struct s_ast		*res = NULL;

   if (g->retval)
      return NULL;
   if (curt(p) == FOR)
   {
      res = create_ast(curt(p));
      accept(p, g);
      if (curt(p) == ERROR || curt(p) == END_OF_FILE)
      {
	 error_msg(L_UNX_EOF, g, p, "rule_for");
	 return NULL;
      }
      res->varname = strdup(cur(p));
      accept(p, g);
      while (curt(p) == EOL)
	 accept(p, g);
      return rule_for_sub(p, g, res);
   }
   return res;
}

/**
 ** @var res->varname receives the name of the function
 ** @var res->left receives the function body
 ** @var res->redir receives the function redirections
 */
struct s_ast	*function_def(struct s_parse *p, struct s_glob *g)
{
   struct s_ast	*res = NULL;

   if (g->retval)
      return NULL;
   if (curt(p) == WORD && !strcmp(cur(p), "function"))
      accept(p, g);
   if (curt(p) == WORD && lat(p) == L_PAR)
   {
      res = create_ast(curt(p));
      res->varname = strdup(cur(p));
      accept(p, g);
      accept(p, g);
      if (curt(p) == R_PAR)
	 accept(p, g);
      while (curt(p) == EOL)
	 accept(p, g);
      res->type = FUNC;
      res->left = shell_command(p, g);
      while (redirection(p, &(res->redir), g))
	 ;
   }
   return res;
}
