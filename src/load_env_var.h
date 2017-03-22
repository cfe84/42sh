/*
** load_env_var.h for load_env_var in /u/a1/kadiri_a/tmp/grosli_o-42sh/src
**
** Made by anass kadiri
** Login   <kadiri_a@epita.fr>
**
** Started on  Mon Jan 17 18:55:43 2005 anass kadiri
** Last update Mon Jan 17 19:18:56 2005 anass kadiri
*/

#ifndef LOAD_ENV_VAR_H_
# define LOAD_ENV_VAR_H_

# include "env_var.h"
# include <stdlib.h>
# include "builtins/builtins.h"

extern char	**environ;

void		load_env_vars(struct s_glob *);
void		free_env_vars(struct s_glob *);

#endif /* !LOAD_ENV_VAR_H_ */
