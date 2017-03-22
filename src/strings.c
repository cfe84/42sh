/*
** strings.c for 42sh in src
**
** Made by feval_c
** Login   <feval_c@epita.fr>
**
** Started on  Mon Jan 17 19:36:11 2005 feval_c
** Last update Mon Jan 17 19:46:56 2005 feval_c
*/

#include <stdlib.h>
#include "strings.h"
#include "mystrcat.h"

/**
 ** Transforms a NULL terminated vector to a string
 */
char	*vectostr(char **strs)
{
  int	i = 0;
  char	*res = NULL;

  while (strs[i] != NULL)
  {
    res = catstring(res, strs[i]);
    res = catchar(res, ' ');
    i++;
  }
  return res;
}
