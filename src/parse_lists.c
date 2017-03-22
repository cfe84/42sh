/*
** parse_lists.c for 42sh in /goinfre/grosli_o-42sh/src
**
** Made by gilles durget
** Login   <durget_g@epita.fr>
**
** Started on  Fri Jan 14 00:52:46 2005 gilles durget
** Last update Tue Jan 18 18:59:09 2005 gilles durget
*/
#include <stdlib.h>
#include "parser.h"
#include "defines.h"
#include "error.h"
#include "is.h"

/**
 ** @var res->left receives the command
 ** @var res->right receives the next pipeline.
 */
static struct s_ast	*pipeline_2(struct s_parse *p, struct s_glob *g)
{
  struct s_ast		*res = NULL;

  if (g->retval)
     return NULL;
  if (curt(p) == PIPE)
    {
      accept(p, g);
      while (curt(p) == EOL)
	accept(p, g);
      res = create_ast(EMPTY);
      if ((res->left = command(p, g)) == NULL)
      {
	error_msg(P_TOKEN_ERROR, g, p, "pipeline_2");
	return NULL;
      }
      if (curt(p) == PIPE)
	res->type = PIPE;
      else
	res->type = EMPTY;
      res->right = pipeline_2(p, g);
    }
  return res;
}

/**
 ** @var res->left receives the command
 ** @var res->right receives the next pipeline.
 */
static struct s_ast	*pipeline(struct s_parse *p, struct s_glob *g)
{
  struct s_ast		*res = NULL;

  if (g->retval)
     return NULL;
  res = create_ast(EMPTY);
  if (curt(p) == BANG)
  {
    accept(p, g);
    res->not = 1;
  }
  if ((res->left = command(p, g)) == NULL)
     return destroy_ast(res);
  if (curt(p) == PIPE)
    res->type = PIPE;
  else
    res->type = EMPTY;
  res->right = pipeline_2(p, g);
  return res;
}

/**
 ** @var res->left receives the command
 ** @var res->right receives the remaining andor
 */
static struct s_ast	*and_or_2(struct s_parse *p, struct s_glob *g)
{
   struct s_ast		*res = NULL;

  if (g->retval)
     return NULL;
   if (curt(p) == PIPEPIPE || curt(p) == AMPAMP)
   {
      accept(p, g);
      if (curt(p) == PVIRG || curt(p) == AMP || curt(p) == AMPAMP ||
	  curt(p) == PIPE || curt(p) == PIPEPIPE)
      {
	 error_msg(P_TOKEN_ERROR, g, p, "and_or_2");
	 return NULL;
      }
      res = create_ast(EMPTY);
      while (curt(p) == EOL)
	 accept(p, g);
      if ((res->left = pipeline(p, g)) == NULL)
	 return destroy_ast(res);
      if (curt(p) == PIPEPIPE || curt(p) == AMPAMP)
	 res->type = curt(p);
      else
	 res->type = EMPTY;
      res->right = and_or_2(p, g);
   }
   return res;
}

/**
 ** @var res->left receives the command
 ** @var res->right receives the remaining andor
 */
struct s_ast	*and_or(struct s_parse *p, struct s_glob *g)
{
   struct s_ast	*res = NULL;

  if (g->retval)
     return NULL;
   res = create_ast(EMPTY);
   if ((res->left = pipeline(p, g)) == NULL)
      return destroy_ast(res);
   if (curt(p) == PIPEPIPE || curt(p) == AMPAMP)
      res->type = curt(p);
   else
      res->type = EMPTY;
   res->right = and_or_2(p, g);
   return res;
}

/**
 ** @var node->ast receives the andor command
 */
static struct s_ast_list	*simple_list_2(struct s_parse *p,
					       struct s_glob *g)
{
   struct s_ast_list		*node = NULL;
   int				tmp_type;

  if (g->retval)
     return NULL;
   if (curt(p) == AMP || curt(p) == PVIRG)
   {
      accept(p, g);
      if (curt(p) == PVIRG || curt(p) == AMP || curt(p) == AMPAMP ||
	  curt(p) == PIPE || curt(p) == PIPEPIPE)
      {
	 error_msg(P_TOKEN_ERROR, g, p, "simple_list_2");
	 return NULL;
      }
      node = malloc(sizeof (struct s_ast_list));
      if ((node->ast = and_or(p, g)) == NULL)
	 return destroy_ast_list(node);
      tmp_type = curt(p) ;
      node->type = (tmp_type == AMP || tmp_type == PVIRG) ? tmp_type : EMPTY;
      node->next = simple_list_2(p, g);
   }
   return node;
}

/**
 ** @var node->ast receives the andor command list
 */
struct s_ast_list	*simple_list(struct s_parse *p,
				     struct s_glob *g)
{
   struct s_ast_list	*node = NULL;
   int			tmp_type;

  if (g->retval)
     return NULL;
   node = malloc(sizeof (struct s_ast_list));
   if ((node->ast = and_or(p, g)) == NULL)
      return destroy_ast_list(node);
   tmp_type = curt(p);
   node->type = (tmp_type == AMP || tmp_type == PVIRG) ? tmp_type : EMPTY;
   node->next = simple_list_2(p, g);
   if (curt(p) == AMP || curt(p) == PVIRG)
      accept(p, g);
   return node;
}
