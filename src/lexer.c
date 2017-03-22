/*
** lexer.c for 42sh in /u/a1/grosli_o/projet/grosli_o-42sh
**
** Made by olivier grosliere
** Login   <grosli_o@epita.fr>
**
** Started on  Tue Jan  4 22:18:23 2005 olivier grosliere
** Last update Tue Jan 18 21:31:22 2005 feval_c
*/
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "defines.h"
#include "lexer.h"
#include "lexer_block_extractor.h"
#include "buffer.h"
#include "is.h"
#include "error.h"
#include "mystrcat.h"

/**
 ** @file lexer.c
 ** Contains the lexer's functions.
 */

/**
 ** Skips all blanks caracters.
 ** @param parse parser structure
 ** @return number of skipped blanks
 */
static int	skip_blank(struct s_parse *p)
{
  int		res = 0;
  int		ret;

  while ((ret = is_blank(p, p->pos)))
  {
    res += ret;
    p->pos += ret;
  }
  return res;
}

/**
 ** Skip all comments.
 ** @param parse parser structure
 ** @retval 1 if comment found
 ** @retval 0 otherwise
 */
static int	skip_comment(struct s_parse *p)
{
  int		c = 0;

  if ((c = get_c(p, p->pos)) == '#')
  {
    while ((c = get_c(p, p->pos)) != -1 && c != '\n')
      ++p->pos;
    return 1;
  }
  else
    return 0;
}

/**
 ** Gets next token.
 ** @param p parse structure
 ** @param word will contain the extracted token if the token is a WORD
 ** @return type of the extracted token \see defines.h, ERROR if none
 */
static int	get_next_token(struct s_parse *p,
			       char **word,
			       struct s_glob *g)
{
  int		ret = 0;
  char		*res;

  while (skip_blank(p) || skip_comment(p))
    ;
  if (get_c(p, p->pos) == -1)
    return END_OF_FILE;
  if ((ret = is_keyword(p)))
  {
    *word = strdup(get_kw()[ret - 1].key);
    return get_kw()[ret - 1].val;
  }
  do
    {
      res = ex_block(p, g);
      if (res != NULL)
	*word = catstring(*word, res);
    }
  while (res != NULL && (is_quote(p, p->pos) || !is_stop(p, p->pos)));
  return *word != NULL ? WORD : EOL;
}

/**
 ** Returns the type of the current word
 ** @param p parse structure
 ** @return type of current token
 */
int	curt(struct s_parse *p)
{
  return p->tokens.cur_type;
}

/**
 ** Returns the type of the look ahead
 ** parse struct and loads it if not
 ** @param p parse structure
 ** @return type of the look ahead
 */
int	lat(struct s_parse *p)
{
  return p->tokens.la_type;
}

/**
 ** Returns a pointer to current word
 ** @param p parse structure
 */
char	*cur(struct s_parse *p)
{
  return p->tokens.cur;
}

/**
 ** Returns a pointer to current lookahead
 ** @param p parse structure
 */
char	*la(struct s_parse *p)
{
  return p->tokens.la;
}

/**
 ** Get a new token in Look ahead and put the old one in current token
 ** @param p parse structure
 */
int	accept(struct s_parse *p, struct s_glob *g)
{
   char	*la = NULL;

  if (p->tokens.cur != NULL)
    free(p->tokens.cur);
  p->tokens.cur = p->tokens.la;
  p->tokens.cur_type = p->tokens.la_type;
  p->tokens.cur_redir = p->tokens.la_redir;
  p->tokens.la_type = get_next_token(p, &la, g);
  p->tokens.la_redir = (get_c(p, p->pos) == '<' ||
			get_c(p, p->pos) == '>');
  p->tokens.la = la;
  return 1;
}
