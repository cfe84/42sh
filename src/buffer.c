/*
** buffer.c for 42sh in src
**
** Made by feval_c
** Login   <feval_c@epita.fr>
**
** Started on  Wed Jan  5 17:05:39 2005 feval_c
** Last update Sun Jan 16 20:09:26 2005 charles feval
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "lexer.h"
#include "defines.h"

/**
 ** \file buffer.c
 ** Buffer manipulation tools
 */

/**
 ** Initializes the buffer.
 ** @param parse parser structure
 ** @param mode MODE_INTER || MODE_FILE
 */
void	init_buf(struct s_parse *parse, int mode)
{
  if (mode == MODE_FILE)
  {
    if ((parse->buf.buf = malloc((BUF_SIZE + 1) * sizeof (char))) == NULL)
    {
      perror("42sh");
      exit (1);
    }
  parse->buf.buf[BUF_SIZE + 1] = 0;
  }
  parse->buf.pos = 0;
  parse->buf.size = 0;
}

/**
 ** Refills the buffer if the mode is FILE.
 ** @param parse parser structure
 ** @param pos new position of the buffer
 ** @retval 1 if the file is finished
 ** @retval 0 else
 */
static int	fill_buf(struct s_parse *parse, int pos)
{
  if (parse->mode == MODE_INTER)
    return 1;
  parse->buf.pos = pos;
  if (lseek(parse->fd, pos, SEEK_SET) < 0)
    return 1;
  if ((parse->buf.size = read(parse->fd, parse->buf.buf, BUF_SIZE)) <= 0)
    return 1;
  return 0;
}

/**
 ** Gets a character in the buffer pointed by `n'.
 ** Refills the buffer if necessary. \see fill_buf
 ** @param parse parse structure
 ** @param n position of the character to be read
 ** @return character at position n, or -1 if finished
 */
int	get_c(struct s_parse *p, int n)
{
  if (p->buf.pos + p->buf.size <= n || p->buf.pos > n)
    if (fill_buf(p, n))
      return -1;
  return 0 + p->buf.buf[n - p->buf.pos];
}

/**
 ** Extracts a string from the buffer.
 ** Refills the buffer if necessary. \see fill_buf
 ** @param parse parse structure
 ** @param n position of the first character to be read
 ** @param lg number of characters to extract
 ** @param str will contain the extracted string
 ** @return number of char actually extracted
 */
int		get_ch(struct s_parse *p, int n, int lg, char **str)
{
  int		i = 0;
  int		cp = 0;
  int		ok = 1;
  int		bs = 0;

  if ((*str = malloc((lg + 1) * sizeof (char))) == NULL)
    return 0;
  while (i < lg && ok != -1)
    if ((ok = get_c(p, n++)) != -1)
    {
      if (bs)
      {
	if (ok != '\n')
	{
	  (*str)[i++] = '\\';
	  (*str)[i++] = ok;
	}
	cp += 2;
      }
      else
	if (ok != '\\')
	  {
	    (*str)[i++] = ok;
	    ++cp;
	  }
      bs = !bs && ok == '\\';
    }
  (*str)[i] = '\0';
  return cp;
}
