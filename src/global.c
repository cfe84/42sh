/*
** global.c for 42sh in src
**
** Made by feval_c
** Login   <feval_c@epita.fr>
**
** Started on  Thu Jan  6 20:48:21 2005 feval_c
** Last update Tue Jan 18 19:25:49 2005 anass kadiri
*/

/**
 ** @file global.c global variable tools
 */

#include <stdlib.h>
#include "global.h"
#include "defines.h"
#include "job.h"
#include "history.h"
#include "load_env_var.h"

/**
 ** Return a freshly created global variable
 ** @return new variable
 ** @var history commands history
 ** @var mode file or interactive
 ** @var retval return value ($?)
 */
struct s_glob	*create_glob(void)
{
  struct s_glob	*glob;

  glob = malloc(sizeof (struct s_glob));
  glob->history = NULL;
  glob->mode = ERROR;
  glob->retval = 0;
  glob->env_var = NULL;
  glob->jobs = init_job();
  load_env_vars(glob);
  init_shopt(glob);
  return glob;
}

/*
** destroy glob structure
*/
void	destroy_glob(struct s_glob *glob)
{
  free_env_vars(glob);
}
