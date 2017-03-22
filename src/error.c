/*
** error.c for 42sh in src
**
** Made by feval_c
** Login   <feval_c@epita.fr>
**
** Started on  Thu Jan  6 20:11:36 2005 feval_c
** Last update Tue Jan 18 20:11:06 2005 gilles durget
*/
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "error.h"
#include "lexer.h"
#include "struct_parse.h"
#include "global.h"
#include "defines.h"
#include "is.h"

/**
 ** Errors messages.
 */
static const struct s_error	msgs[] =
  {
    {L_UNX_EOF,		L_UNX_EOF_MSG,	L_UNX_EOF_RET,	L_UNX_DISPCUR},
    {P_TOKEN_ERROR,	P_TOKEN_MSG,	P_TOKEN_RET,	P_TOKEN_DISPCUR},
    {P_DONE_EX,		P_DONE_EX_MSG,	P_DONE_RET,	P_DONE_DISPCUR},
    {P_DO_EX,		P_DO_EX_MSG,	P_DO_RET,	P_DO_DISP_CUR},
    {P_THEN_EX,		P_THEN_EX_MSG,	P_THEN_RET,	P_THEN_DISP_CUR},
    {P_FI_EX,		P_FI_EX_MSG,	P_FI_RET,	P_FI_DISP_CUR},
    {P_EL_EX,		P_EL_EX_MSG,	P_EL_RET,	P_EL_DISP_CUR},
    {0,			NULL,		0,		0}
  };

/**
 ** Frees the parser, the returns retval
 ** @param retval exit value
 ** @param p parser to free
 */
void	my_exit(int retval, struct s_parse *p)
{
  destroy_parse(p);
  exit(retval);
}

/**
 ** Prints error messages.
 ** @param errnum error number
 ** @param g meta structure
 ** @param p parse structure
 */
void	error_msg(int errnum, struct s_glob *g, struct s_parse *p, char *ctx)
{
   char	*msg = NULL;

   if (cur(p) != NULL)
      msg = cur(p);
   else
      if (curt(p) == END_OF_FILE)
	 msg = "EOF";
   if (msgs[errnum].afftoken && msg != NULL)
#ifdef AFFTREE
      fprintf(stderr, "42sh: %s `%s' from %s\n", msgs[errnum].msg, msg, ctx);
#else
      fprintf(stderr, "42sh: %s `%s'\n", msgs[errnum].msg, msg);
#endif /* !AFFTREE */
   else
    fprintf(stderr, "42sh: %s from %s\n", msgs[errnum].msg, ctx);
  g->retval = msgs[errnum].ret;
  if (g->mode == MODE_FILE || g->mode == MODE_PIPE)
    my_exit(msgs[errnum].ret, p);
}
