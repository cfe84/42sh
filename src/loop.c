/*
** loop.c for 42sh in src
**
** Made by feval_c
** Login   <feval_c@epita.fr>
**
** Started on  Thu Jan  6 20:36:12 2005 feval_c
** Last update Tue Jan 18 18:37:45 2005 gilles durget
*/

#include <stdio.h>
#include <stdlib.h>
#include "loop.h"
#include "lexer.h"
#include "global.h"
#include "read_line.h"
#include "prompt.h"
#include "parser.h"
#include "defines.h"
#include "eval.h"
#include "display.h"
#include "job.h"
#include "expansion/expand.h"
#include "launch.h"

/**
 ** Interactive loop:
 ** Reads a line, then parses it and executes it.
 */
void			loop(struct s_glob *glob)
{
  char			*rd;

  do
  {
    glob->retval = 0;
    print_prompt(glob);
    if ((rd = rd_line(glob)) != NULL)
    {
      verif_and_kill(glob->jobs);
      let_s_go(glob, rd);
    }
  }
  while (rd != NULL);
}
