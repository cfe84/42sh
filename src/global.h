/*
** global.h for 42sh in src
**
** Made by feval_c
** Login   <feval_c@epita.fr>
**
** Started on  Thu Jan  6 20:44:13 2005 feval_c
** Last update Tue Jan 18 19:25:34 2005 anass kadiri
*/

#ifndef GLOBAL_H_
# define GLOBAL_H_

# include "history.h"

/**
 ** Structure used like a global variable, that carries with her settings
 ** variables, history,...
 ** @param history contains history of entries of the user.
 ** @param env_var contains environment vars.
 ** @param mode contains mode: interactive or file or pipe.
 ** @param ncommands number of commands typed by the user
 */
struct			s_glob
{
  struct s_history	*history;
  struct s_env_var	*env_var;
  struct s_jobs		*jobs;
  struct s_shopt	*shopt;
  int			mode;
  int			ncommands;
  int			retval;
};

struct s_glob	*create_glob(void);
void		destroy_glob(struct s_glob *);

#endif /* !GLOBAL_H_ */
