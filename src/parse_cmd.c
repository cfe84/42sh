/*
** parse_cmd.c for 42sh in /goinfre/grosli_o-42sh/src
**
** Made by gilles durget
** Login   <durget_g@epita.fr>
**
** Started on  Fri Jan 14 00:45:55 2005 gilles durget
** Last update Tue Jan 18 19:00:40 2005 gilles durget
*/
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "parser.h"
#include "defines.h"
#include "error.h"
#include "is.h"

struct s_ast		*command(struct s_parse *p, struct s_glob *g)
{
   struct s_ast		*res = NULL;

   if (g->retval)
      return NULL;
   if ((res = simple_command(p, g)) != NULL)
      return res;
   if ((res = shell_command(p, g)) != NULL)
   {
      while (redirection(p, &(res->redir), g))
	 ;
      return res;
   }
   if ((res = function_def(p, g)) != NULL)
      return res;
   return NULL;
}

/**
 ** @var node->ast receives a command.
 ** @var node->next receives the end of the compound list
 */
static struct s_ast_list	*compound_list_2(struct s_parse *p,
						 struct s_glob *g)
{
   struct s_ast_list		*node = NULL;
   int				tmp_type;

   if (g->retval)
      return NULL;
   if (curt(p) == AMP || curt(p) == PVIRG || curt(p) == EOL)
   {
      accept(p, g);
      if (curt(p) == PVIRG || curt(p) == AMP || curt(p) == AMPAMP ||
	  curt(p) == PIPE || curt(p) == PIPEPIPE)
      {
	 error_msg(P_TOKEN_ERROR, g, p, "compound_list");
	 return NULL;
      }
      while (curt(p) == EOL)
	 accept(p, g);
      node = malloc(sizeof (struct s_ast_list));
      if ((node->ast = and_or(p, g)) == NULL)
	 return destroy_ast_list(node);
      tmp_type = curt(p);
      node->next = compound_list_2(p, g);
      node->type = node->next != NULL ? tmp_type : EMPTY;
   }
   return node;
}

/**
 ** @var node->ast receives a command.
 ** @var node->next receives the end of the compound list
 */
struct s_ast_list	*compound_list(struct s_parse *p, struct s_glob *g)
{
   struct s_ast_list	*node = NULL;
   int			tmp_type;

   if (g->retval)
      return NULL;
   while (curt(p) == EOL)
      accept(p, g);
   node = malloc(sizeof (struct s_ast_list));
   if ((node->ast = and_or(p, g)) == NULL)
   {
      error_msg(P_TOKEN_ERROR, g, p, "compound_list");
      return destroy_ast_list(node);
   }
   tmp_type = curt(p);
   node->next = compound_list_2(p, g);
   node->type = node->next != NULL ? tmp_type : EMPTY;
   if (curt(p) == AMP || curt(p) == PVIRG || curt(p) == EOL)
      accept(p, g);
   while (curt(p) == EOL)
      accept(p, g);
   return node;
}

static struct s_ast	*shell_command_sub(struct s_parse *p,
					   struct s_glob *g,
					   int o_type)
{
   struct s_ast		*res = NULL;

   if (g->retval)
      return NULL;
   res = create_ast(curt(p));
   accept(p, g);
   if (curt(p) == PVIRG || curt(p) == AMP || curt(p) == AMPAMP ||
       curt(p) == PIPE || curt(p) == PIPEPIPE)
   {
      error_msg(P_TOKEN_ERROR, g, p, "shell_command");
      return destroy_ast(res);
   }
   res->type = o_type;
   res->list = compound_list(p, g);
   return res;
}

/**
 ** @var res->list receives the list of commands
 */
struct s_ast		*shell_command(struct s_parse *p, struct s_glob *g)
{
   struct s_ast		*res = NULL;

   if (g->retval)
      return NULL;
   if (curt(p) == L_BRA)
   {
      res = shell_command_sub(p, g, L_BRA);
      if (curt(p) == R_BRA && accept(p, g))
	 return res;
   }
   if (curt(p) == L_PAR)
   {
      res = shell_command_sub(p, g, L_PAR);
      if (curt(p) == R_PAR && accept(p, g))
	 return res;
   }
   if (((res = rule_for(p, g)) != NULL) || ((res = rule_while(p, g)) != NULL) ||
       ((res = rule_until(p, g)) != NULL) || ((res = rule_if(p, g)) != NULL))
      return res;
   return NULL;
}

int			redirection(struct s_parse *p,
				    struct s_redir **redir,
				    struct s_glob *g)
{
   char			*num = NULL;

   if (g->retval)
      return 0;
   if (curt(p) == WORD && is_num(cur(p)) && curr(p))
   {
      num = strdup(cur(p));
      accept(p, g);
   }
   if (is_redir(curt(p)) && lat(p) == WORD)
   {
      *redir = add_redir(num, curt(p), la(p), *redir);
      accept(p, g);
      accept(p, g);
      return 1;
   }
   if (num != NULL)
      free(num);
   return 0;
}

static int	element(struct s_parse *p,
			struct s_glob *g,
			struct s_redir **redir,
			char **res)
{
   if (g->retval)
      return 0;
   if (cur(p) == NULL || !strcmp(cur(p), "function") || lat(p) == L_PAR)
      return EL_STOP;
   if (curt(p) == WORD && (!is_num(cur(p)) || !is_redir(lat(p)) || !curr(p)))
   {
      *res = strdup(cur(p));
      accept(p, g);
      return EL_WORD;
   }
   else
      if (redirection(p, redir, g))
	 return EL_REDIR;
   return EL_STOP;
}

/**
 **
 **
 */
static struct s_cmd	*add_cmd_to_list(struct s_cmd *cmd, char *elt)
{
   struct s_cmd		*res = NULL;
   struct s_cmd		*p = cmd;

   if ((res = malloc(sizeof(struct s_cmd))) == NULL)
      return NULL;
   res->next = NULL;
   res->cmd = elt;
   if (p == NULL)
      return res;
   while (p->next != NULL)
      p = p->next;
   p->next = res;
   return cmd;
}

/**
 ** @var redir receives the redirections list
 ** @var cmd receives the commands list (ex: echo toto tata)
 */
struct s_ast		*simple_command(struct s_parse *p, struct s_glob *g)
{
   struct s_ast		*res = NULL;
   int			result;
   char			*tmp = NULL;
   struct s_redir	*redir = NULL;
   struct s_cmd		*cmd_list = NULL;

   if (g->retval)
      return NULL;
   if ((result = element(p, g, &redir, &tmp)) != EL_STOP)
   {
      do
	 if (result == EL_WORD)
	    cmd_list = add_cmd_to_list(cmd_list, tmp);
      while ((result = element(p, g, &redir, &tmp)) != EL_STOP);
      res = create_ast(COMMAND);
      res->redir = redir;
      res->cmd_list = cmd_list;
   }
   return res;
}
