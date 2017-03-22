/*
** prompt.c for 42sh in src
**
** Made by feval_c
** Login   <feval_c@epita.fr>
**
** Started on  Fri Jan  7 14:13:06 2005 feval_c
** Last update Fri Jan 14 01:21:59 2005 gilles durget
*/

/**
 ** @file prompt.c
 ** Tools for the prompt
 */

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include "defines.h"
#include "global.h"

/**
 ** Prints the prompt if needed
 */
void	print_prompt(struct s_glob *global)
{
  char	*prompt;

  if (global->mode == MODE_INTER)
  {
/*    if ((prompt = getenv("PS1")) == NULL) */
      prompt = DEFAULT_PROMPT;
    printf("%s", prompt);
    fflush(stdout);
  }
}
