/*
** is.c for 42sh in /u/a1/durget_g/grosli_o-42sh/src
**
** Made by gilles durget
** Login   <durget_g@epita.fr>
**
** Started on  Fri Jan  7 14:49:20 2005 gilles durget
** Last update Tue Jan 18 21:30:31 2005 feval_c
*/
#include <stdlib.h>
#include <string.h>
#include "is.h"
#include "defines.h"
#include "lexer.h"
#include "buffer.h"

/**
 ** @file is.c
 ** Contains the characters checking functions.
 */

/**
 ** Contains keywords and their token value.
 ** \see s_keywords
 */
static const struct s_keywords	keywords[] =
{
   {"\n",	EOL},
   {";",	PVIRG},
   {"!",	BANG},
   {"&&",	AMPAMP},
   {"&",	AMP},
   {"||",	PIPEPIPE},
   {"|",	PIPE},
   {">",        R_CH},
   {"<",	L_CH},
   {">>",	D_R_CH},
   {"<<",	D_L_CH},
   {"<<-",	S_D_L_CH},
   {"(",	L_PAR},
   {")",	R_PAR},
   {"{",	L_BRA},
   {"}",	R_BRA},
   {"if",	IF},
   {"then",	THEN},
   {"else",	ELSE},
   {"elif",	ELIF},
   {"fi",	FI},
   {"for",	FOR},
   {"in",	IN},
   {"done",	DONE},
   {"do",	DO},
   {"while",	WHILE},
   {"until",	UNTIL},
   {NULL,	0}
};

/**
 ** Contains the character that make the lexer stops.
 */
static const char	*stop[] =
{
   "\"",
   " ",
   "\t",
   "\r",
   "\n",
   "#",
   ";",
   "|",
   "&",
   ">",
   "<",
   "!",
   "(",
   ")",
   "{",
   "}",
   "\0"
};

/**
 ** Contains the characters ignored by the lexer.
 */
static const char	*blank[] =
{
   "\\n",
   " ",
   "\t",
   "\r",
   "\0"
};

/**
 ** Contains possible quotes.
 */
static const char	*quotes[] =
{
   "$(",
   "\"",
   "'",
   "`",
};

/*
** Returns keyword associated with keyword code.
** @param n keyword code
*/
const struct s_keywords	*get_kw(void)
{
   return keywords;
}

/**
 ** Checks if a character is both a keyword and a stop character.
 ** @param n intern code of the character
 ** @retval 1 if the character is a stop
 ** @retval 0 otherwise
 */
static int		is_keynstop(int n)
{
   return n == EOL || n == PVIRG || n == BANG || n == AMPAMP || n == AMP ||
      n == PIPEPIPE ||  n == PIPE || n == R_CH || n == L_CH || n == D_R_CH ||
      n == D_L_CH || n == S_D_L_CH || n == L_PAR || n == R_PAR || n == L_BRA ||
      n == R_BRA;
}

/**
 ** Checks if a character is a stop character.
 ** @param p parse structure
 ** @param n position in file
 ** @retval 1 if the character is a stop
 ** @retval 0 otherwise
 */
int		is_stop(struct s_parse *p, int n)
{
   int		i = 0;
   int		lg;
   char		*ex;

   if (get_ch(p, n, 2, &ex) == 0)
      return 0;
   while (i < NB_STOPS)
   {
      lg = strlen(stop[i]);
      if (!strncmp(ex, stop[i], lg))
	 return lg;
      ++i;
   }
   return 0;

}

/**
 ** Checks if a character is a blank character to skip.
 ** @param p parse structure
 ** @param n position in file
 ** @retval number of blanks skipped
 ** @retval 0 otherwise
 */
int		is_blank(struct s_parse *p, int n)
{
   int		i = 0;
   int		lg;
   char		*ex;

   if (get_ch(p, n, 2, &ex) == 0)
      return 0;
   while (i < NB_BLANKS)
   {
      lg = strlen(blank[i]);
      if (!strncmp(ex, blank[i], lg))
	 return lg;
      ++i;
   }
   return 0;
}

/**
 ** Checks if a character is a blank character to skip.
 ** @param p parse structure
 ** @param n position in file
 ** @return the matching closing quote, '\0' if none
 */
char		is_quote(struct s_parse *p, int n)
{
   int		i = 0;
   int		lg;
   char		*ex;

   if (get_ch(p, n, 2, &ex) == 0)
      return 0;
   while (i < NB_QUOTES)
   {
      lg = strlen(quotes[i]);
      if (!strncmp(ex, quotes[i], lg))
	 return i ? *(quotes[i]) : ')';
      ++i;
   }
   return '\0';
}

/**
 ** Checks if the next word is a keyword.
 ** @param parse parser structure
 ** @return keyword identifier if keyword found, 0 otherwise
 */
int		is_keyword(struct s_parse *p)
{
  int		i = 0;
  int		k = p->pos;
  int		len;
  int		outlen;
  char		*str;

  while (keywords[i].key != NULL)
  {
    len = strlen(keywords[i].key);
    outlen = get_ch(p, k, len, &str);
    if (!strcmp(keywords[i].key, str) &&
	(is_keynstop(keywords[i].val) || is_stop(p, k + len) ||
	 get_c(p, k + len) == -1))
    {
      p->pos += outlen;
      free(str);
      return keywords[i].val + 1;
    }
    free(str);
    ++i;
  }
  return 0;
}
