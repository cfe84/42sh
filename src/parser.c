/*
** parser.c for 42sh in src
**
** Made by feval_c
** Login   <feval_c@epita.fr>
**
** Started on  Thu Jan  6 21:06:09 2005 feval_c
** Last update Tue Jan 18 18:25:53 2005 gilles durget
*/

/**
 ** @file parser.c
 ** Contains the first parse functions. For further informations, refer
 ** to grammar
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "parser.h"
#include "lexer.h"
#include "global.h"
#include "defines.h"
#include "struct_parse.h"
#include "ast.h"
#include "is.h"
#include "display.h"
#include "error.h"

static struct s_ast_list	*good_input(struct s_parse *p,
					    struct s_glob *g)
{
   if (curt(p) == PVIRG || curt(p) == AMP || curt(p) == AMPAMP ||
       curt(p) == PIPE || curt(p) == PIPEPIPE)
   {
      error_msg(P_TOKEN_ERROR, g, p, "good_input");
      return NULL;
   }
   if (curt(p) == END_OF_FILE || (curt(p) == EOL && accept(p, g)))
      return NULL;
   return simple_list(p, g);
}

/**
 ** Parses a command line if mode is set to MODE_INTER, a file if
 ** set to MODE_FILE
 ** @param mode MODE_FILE or MODE_INTER
 ** @param file file or command line to parse
 */
struct s_ast_list	*parse(int mode, char *file, struct s_glob *g)
{
   struct s_parse	*p;
   struct s_ast_list	*ast_list = NULL;
   struct s_ast_list	*good_list = NULL;

   if (file == NULL)
      return NULL;
   p = create_parse(mode, file, g);
   while (curt(p) != END_OF_FILE && curt(p) != ERROR && g->retval == 0)
   {
      good_list = good_input(p, g);
      if (good_list != NULL)
	 ast_list = add_item(ast_list, good_list);
   }
   destroy_parse(p);
   return ast_list;
}
