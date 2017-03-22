/*
** struct_parse.c for 42sh in src
**
** Made by feval_c
** Login   <feval_c@epita.fr>
**
** Started on  Thu Jan  6 18:48:40 2005 feval_c
** Last update Mon Jan 17 20:44:17 2005 gilles durget
*/

/**
 ** @file  struct s_parse.c
 ** Contains struct s_parse tools
 **/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "lexer.h"
#include "buffer.h"
#include "defines.h"
#include "error.h"
#include "ast.h"

/**
 ** Returns a freshly created parser
 ** @param mode MODE_INTER or MODE_FILE
 ** @param file File, or string to parse.
 */
struct s_parse		*create_parse(int mode, char *file, struct s_glob *g)
{
  struct s_parse	*p;

  p = malloc(sizeof (struct s_parse));
  init_buf(p, mode);
  if (mode == MODE_FILE)
  {
    if ((p->fd = open(file, O_RDONLY, 0)) < 0)
    {
      perror("42sh");
      my_exit(127, p);
    }
  }
  else
  {
    p->buf.buf = file;
    p->buf.size = strlen(file);
  }
  p->mode = mode;
  p->pos = 0;
  p->stop = 0;
  p->tokens.cur = p->tokens.la = NULL;
  accept(p, g);
  accept(p, g);
  return p;
}

/**
 ** Destroy a parser
 ** @param p parser to destroy
 */
void	destroy_parse(struct s_parse *p)
{
  if (p == NULL)
    return;
  free(p->buf.buf);
  free(p);
}

/**
 ** Adds a list element in a ast list.
 */
struct s_ast_list	*add_item(struct s_ast_list *astl,
				  struct s_ast_list *new)
{
   struct s_ast_list	*tmp = astl;

   if (tmp == NULL)
      return new;
   while (tmp->next != NULL)
      tmp = tmp->next;
   tmp->next = new;
   return astl;
}
