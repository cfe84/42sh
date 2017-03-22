/*
** is2.c for 42sh in /goinfre/grosli_o-42sh/src
**
** Made by gilles durget
** Login   <durget_g@epita.fr>
**
** Started on  Thu Jan 13 18:15:58 2005 gilles durget
** Last update Fri Jan 14 01:04:07 2005 gilles durget
*/
#include <stdlib.h>
#include "is.h"
#include "defines.h"

/**
 ** Checks if the nth character is a number.
 ** @param p parse structure
 ** @n position of the character in the file
 */
int		is_redir(int type)
{
   return type == R_CH || type == L_CH || type == D_R_CH ||
      type == D_L_CH || type == S_D_L_CH;
}

/**
 ** @param s String to verify
 ** @retval 1 if s is a correct redirection number
 ** @retval 0 else
 */
int		is_num(char *s)
{
  int		i = 0;

  while (s[i] >= '0' && s[i] <= '9')
    ++i;
  return s[i] == '\0' && atoi(s) <= 63;
}
