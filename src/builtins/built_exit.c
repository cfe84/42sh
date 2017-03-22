/*
** built_exit.c for built_exit in /u/a1/kadiri_a/tmp/grosli_o-42sh/src/builtins
**
** Made by anass kadiri
** Login   <kadiri_a@epita.fr>
**
** Started on  Sun Jan 16 15:35:41 2005 anass kadiri
** Last update Mon Jan 17 20:44:22 2005 anass kadiri
*/

#include "builtins.h"

void	built_exit(char **command, struct s_glob *g)
{
  char	*cmd;
  int	n = 0;

  cmd = command[0];
  if (command[1] != NULL)
    n = atoi(command[1]);
  destroy_glob(g);
  exit(n);
}
