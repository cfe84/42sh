/*
** lexer_block_extractor.c for 42sh in src
**
** Made by feval_c
** Login   <feval_c@epita.fr>
**
** Started on  Sun Jan 16 16:06:22 2005 feval_c
** Last update Tue Jan 18 20:33:15 2005 gilles durget
*/

#include <stdlib.h>
#include "lexer_block_extractor.h"
#include "mystrcat.h"
#include "defines.h"
#include "buffer.h"
#include "lexer.h"
#include "error.h"
#include "is.h"

/**
 ** Recursive function for block surrounded by simple quotes
 ** extraction
 ** @param p parse structure
 ** @param pos starting position in the file
 ** @return block
 */
static char	*ex_block_simple_quote(struct s_parse *p,
				       int *pos,
				       struct s_glob *g)
{
  int		c;
  char		*res = NULL;

  while ((c = get_c(p, *pos)) != -1 && c != '\'')
  {
    res = catchar(res, c);
    (*pos)++;
  }
  if (c == -1)
    error_msg(L_UNX_EOF, g, p, "ex_block_rec");
  (*pos)++;
  res = catchar(res, c);
  return res;
}

/**
 ** Recursive function for block extraction surrounded
 ** by quotes or parenthesis
 ** @param p parse structure
 ** @param quote ending quote to match
 ** @param pos starting position in the file
 ** @return ending position of the block
 */
static char	*ex_block_rec_quote(struct s_parse *p,
				    char quote,
				    int *pos,
				    struct s_glob *g)
{
  int		bs = 0;
  int		c;
  char		d;
  char		*res = NULL;

  while ((c = get_c(p, *pos)) != -1 && (quote != c || bs))
  {
    if (!bs && (d = is_quote(p, *pos)) && d != '\'')
    {
      res = catchar(res, c);
      (*pos)++;
      res = catstring(res, ex_block_rec_quote(p, d, pos, g));
    }
    else
    {
      (*pos)++;
      if (bs)
      {
	if (c != '\n')
	  res = catchar(catchar(res, '\\'), c);
      }
      else
	if (c != '\\')
	  res = catchar(res, c);
    }
    bs = (c == '\\' && !bs);
  }
  if (c == -1)
    error_msg(L_UNX_EOF, g, p, "ex_block_rec");
  (*pos)++;
  res = catchar(res, c);
  return res;
}

/**
 ** Recursive function for standard block extraction
 ** @param p parse structure
 ** @param pos starting position in the file
 *resreturn ending position of the block
 */
static char	*ex_block_rec(struct s_parse *p,
			      int *pos,
			      struct s_glob *g)
{
  int		bs = 0;
  int		c;
  char		d;
  char		*res = NULL;

  while ((c = get_c(p, *pos)) != -1 && (!is_stop(p, *pos) || bs))
  {
    if (!bs && (d = is_quote(p, *pos)))
    {
       res = catchar(res, c);
       (*pos)++;
       if (d == '\'')
	  res = catstring(res, ex_block_simple_quote(p, pos, g));
       else
	  res = catstring(res, ex_block_rec_quote(p, d, pos, g));
    }
    else
    {
      (*pos)++;
      if (!bs && (c != '\\' || bs))
	 res = catchar(res, c);
      if (bs && c != '\n')
	 res = catchar(catchar(res, '\\'), c);
    }
     bs = (c == '\\' && !bs);
  }
  return res;
}

/**
 ** Extracts next block.
 ** @param p parse structure
 ** @return extracted block
 */
char		*ex_block(struct s_parse *p, struct s_glob *g)
{
   char		*res = NULL;
   char		c;
   int		k = p->pos;

   if ((c = is_quote(p, k)))
   {
     res = catchar(NULL, get_c(p, k));
     ++k;
   }
   if (c == '\'')
     res = catstring(res, ex_block_simple_quote(p, &k, g));
   else
     if (c)
       res = catstring(res, ex_block_rec_quote(p, c, &k, g));
     else
       res = catstring(res, ex_block_rec(p, &k, g));
   p->pos = k;
   return res;
}
