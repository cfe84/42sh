/*
** mystrcat.c for 42sh in src
**
** Made by feval_c
** Login   <feval_c@epita.fr>
**
** Started on  Sun Jan 16 18:09:10 2005 feval_c
** Last update Sun Jan 16 19:18:58 2005 charles feval
*/

#include <strings.h>
#include <stdlib.h>
#include "mystrcat.h"

/**
 ** Append a char to a string
 */
char	*catchar(char *str, char c)
{
  int	len;

  len = ((str == NULL) ? 0 : strlen(str));
  str = realloc(str, (len + 2) * sizeof (char));
  str[len] = c;
  str[len + 1] = 0;
  return str;
}

/**
 ** Appends stra to strb
 */
char	*catstring(char *stra, char *strb)
{
  int	lena;
  int	lenb;

  lena = ((stra == NULL) ? 0 : strlen(stra));
  lenb = ((strb == NULL) ? 0 : strlen(strb));
  if (stra == NULL)
    return strb;
  else
    if (strb == NULL)
      return stra;
    else
    {
      stra = realloc(stra, (lena + lenb + 1) * sizeof (char));
      stra = strcat(stra, strb);
      return stra;
    }
}
