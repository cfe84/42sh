/*
** lexer2.c for 42sh in /u/a1/grosli_o/projet/grosli_o-42sh/src
**
** Made by olivier grosliere
** Login   <grosli_o@epita.fr>
**
** Started on  Mon Jan 10 15:24:47 2005 olivier grosliere
** Last update Mon Jan 10 15:28:14 2005 olivier grosliere
*/

#include "lexer.h"

/**
 ** Checks if next char of the current word is a redirection char
 ** @param p parse structure
 ** @retval 1 if the character is a redirection char
 ** @retval 0 else
 */
int	curr(struct s_parse *p)
{
  return p->tokens.cur_redir;
}

/**
 ** Checks if next char of the la is a redirection char
 ** @param p parse structure
 ** @retval 1 if the character is a redirection char
 ** @retval 0 else
 */
int	lar(struct s_parse *p)
{
  return p->tokens.la_redir;
}
