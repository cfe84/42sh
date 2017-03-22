/*
** launch.c for 42sh in src
**
** Made by feval_c
** Login   <feval_c@epita.fr>
**
** Started on  Thu Jan  6 20:06:56 2005 feval_c
** Last update Tue Jan 18 19:33:37 2005 gilles durget
*/

/**
 ** @file launch.c
 ** If 42sh is launched in a tty, then launches the interaction loop,
 ** else launches the parser on the submitted file.
 */
#include <stdio.h>
#include <unistd.h>
#include "launch.h"
#include "defines.h"
#include "lexer.h"
#include "loop.h"
#include "struct_parse.h"
#include "global.h"
#include "parser.h"
#include "eval.h"
#include "expansion/expand.h"
#include "display.h"

/**
 ** Common part of the launch procedure.
 ** @param astl the ast list
 ** @param g the global structure
 ** @param str the string to evaluate
 */
void	let_s_go(struct s_glob *g, char *str)
{
  struct s_ast_list	*astl;

  if ((astl = parse(g->mode, str, g)) != NULL)
   {
      expand(astl, g);
#ifdef AFFTREE
      disp_ast_list(astl, "start", 1);
      printf("*** eval starts here ***\n");
#endif /* !AFFTREE */
      if (astl != NULL)
	 eval(astl, g);
      destroy_ast_list(astl);
   }
}

/**
 ** If there is a file, then launches parser on the file.
 ** else, if interaction mode is selected, then launches an interactive loop
 ** with readline
 ** @param argc Arguments count
 ** @param argv Arguments vector
 ** @var glob Global variable that will travel through all functions
 */
void			launch(int argc, char **argv)
{
  struct s_glob	*g;

  g = create_glob();
  g->mode = ((argc > 1) ? MODE_FILE : (isatty(STDIN_FILENO) ?
				       MODE_INTER : MODE_PIPE));
  if (argc > 1)
     let_s_go(g, argv[1]);
  else
     loop(g);
}
