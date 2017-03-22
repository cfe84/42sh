/*
** env_var.h for env_var in /u/a1/kadiri_a/tmp/grosli_o-42sh/src/builtins
**
** Made by anass kadiri
** Login   <kadiri_a@epita.fr>
**
** Started on  Sun Jan 16 20:50:27 2005 anass kadiri
** Last update Mon Jan 17 21:27:14 2005 anass kadiri
*/

#ifndef ENV_VAR_H_
# define ENV_VAR_H_

#include <stdio.h>
#include <stdlib.h>
#include "global.h"

/*
** structure of variables
*/
struct			s_env_var
{
  char			*name;
  char			*val;
  struct s_env_var	*next;
};

void	set_var(char *, char *, struct s_glob *);
void	unset_var(char **, struct s_glob *);
char	*get_var(char *, struct s_glob *);
void	show_vars(char **, struct s_glob *);

#endif /* !ENV_VAR_H_ */
