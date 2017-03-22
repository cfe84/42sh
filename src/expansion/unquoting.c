/*
** unquoting.c for 42sh in /goinfre/grosli_o-42sh/src/expansion
**
** Made by olivier grosliere
** Login   <grosli_o@epita.fr>
**
** Started on  Tue Jan 18 17:06:50 2005 olivier grosliere
** Last update Tue Jan 18 20:03:41 2005 olivier delestre
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include "../global.h"
#include "../ast.h"
#include "unquoting.h"

void	supp_quote_sq(char *dest, char *src, int *pos_dest, int *pos_src)
{
  ++(*pos_src);
  while (src[*pos_src] != '\'')
    dest[(*pos_dest)++] = src[(*pos_src)++];
}

void	supp_quote_dq(char *dest, char *src, int *pos_dest, int *pos_src)
{
  int	bs_on = 0;

  ++(*pos_src);
  while (src[*pos_src] != '"' || (src[*pos_src] == '"' && bs_on))
    {			 /* Possibilite de rajouter des trucs */
      if (bs_on && (src[*pos_src] == '"' || src[*pos_src] == '\\'))
	{
	  dest[(*pos_dest)++] = src[(*pos_src)++];
	  bs_on = 0;
	}
      else
	{
	  if (bs_on)
	    {
	      dest[(*pos_dest)++] = '\\';
	      bs_on = 0;
	    }
	  if (src[*pos_src] == '\\')
	    bs_on = 1;
	  else
	    dest[(*pos_dest)++] = src[*pos_src];
	  ++(*pos_src);
	}
    }
}

void	supp_quote(char *dest, char *src, int *pos_dest, int *pos_src)
{
  int	bs_on = 0;

  while (src[*pos_src] != '\0')
    {
      if (src[*pos_src] == '\\')
	{
	  if (bs_on)
	    dest[(*pos_dest)++] = src[*pos_src];
	  bs_on = !bs_on;
	}
      else
	{
	  if (src[*pos_src] == '\'' && !bs_on)
	    supp_quote_sq(dest, src, pos_dest, pos_src);
	  else
	    {
	      if (src[*pos_src] == '"' && !bs_on)
		supp_quote_dq(dest, src, pos_dest, pos_src);
	      else
		dest[(*pos_dest)++] = src[*pos_src];
	    }
	  bs_on = 0;
	}
      (*pos_src)++;
    }
  dest[(*pos_dest)++] = '\0';
}

char	*remove_quote(char *str)
{
  char	*res = NULL;
  int	pos_dest = 0;
  int	pos_src = 0;

  if (str == NULL || (res = malloc(strlen(str))) == NULL)
    return NULL;
  supp_quote(res, str, &pos_dest, &pos_src);
  /*  write(STDOUT_FILENO, str, strlen(str));
  write(STDOUT_FILENO, "\n", 1);
  write(STDOUT_FILENO, res, strlen(res));
  write(STDOUT_FILENO, "\n", 1);*/
  return res;
}
