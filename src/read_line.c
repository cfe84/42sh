/*
** read_line.c for 42sh in src
**
** Made by feval_c
** Login   <feval_c@epita.fr>
**
** Started on  Thu Jan  6 21:07:56 2005 feval_c
** Last update Mon Jan 17 18:16:54 2005 gilles durget
*/

/**
 ** @file read_line.c
 ** Contains the function used to interact with user:
 ** Manage history, and keyboard.
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "read_line.h"
#include "history.h"
#include "global.h"
#include "defines.h"

/**
 ** Reads a line, with history functions.
 ** @param glob global variable
 */
char	*rd_line(struct s_glob *glob)
{
  char	*rd = NULL;
  int	r = 0;
  int	ret = 0;
  int	size = 0;

  rd = malloc(sizeof (char));
  while ((ret = read(STDIN_FILENO, &r, 1) > 0) && r != '\n')
  {
    rd = realloc(rd, ++size);
    rd[size - 1] = r;
  }
  if (ret <= 0)
     return NULL;
  else
     rd[size] = 0;
  if (glob->mode == MODE_INTER && size > 0)
    add_to_history(&(glob->history), rd);
  return rd;
}
