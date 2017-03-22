/*
** main2.c for main in /u/a1/kadiri_a/tmp/grosli_o-42sh/src
**
** Made by anass kadiri
** Login   <kadiri_a@epita.fr>
**
** Started on  Sun Jan 16 20:59:41 2005 anass kadiri
** Last update Tue Jan 18 18:57:24 2005 anass kadiri
*/

#include "load_env_var.h"

/*
** get name from cmd
*/
static char	*get_name(char *cmd)
{
  char		*name = NULL;
  int		i = 0;

  while (cmd[i] != '\0' && cmd[i] != '=')
    i++;
  name = my_strndup(cmd, i);
  return name;
}

/*
** get value from cmd
*/
static char	*get_value(char *cmd)
{
  int		i = 0;
  char		*value = NULL;

  while (cmd[i] != '\0' && cmd[i] != '=')
    i++;
  value = my_strndup(cmd + i + 1, strlen(cmd) - i);
  return value;
}

/*
** load all env vars from environ
** and put them into g
*/
void	load_env_vars(struct s_glob *g)
{
  int	i = 0;

  for (i = 0; environ[i]; i++)
    set_var(get_name(environ[i]), get_value(environ[i]), g);
  set_var(strdup("OLDPWD"), NULL, g);
}

/*
** free all env vars
** when exiting the program
*/
void			free_env_vars(struct s_glob *g)
{
  struct s_env_var	*tmp;
  int			rm = 1;
  char			*tab[2];

  while (rm && g->env_var)
    {
      rm = 0;
      tmp = g->env_var;
      while (tmp != NULL && !rm)
        {
          tab[0] = NULL;
	  tab[1] = tmp->name;
	  unset_var(tab, g);
          rm = 1;
        }
    }

}

/* int		main(int argc, char **argv) */
/* { */
/*   struct s_glob *g; */
/*   char		**t= NULL; */

/*   argc = argc; */
/*   argv = argv; */
/*   g = create_glob(); */
/*   load_env_vars(g); */
/*   show_vars(t, g); */
/*   free_env_vars(g); */
/*   printf("--------\n"); */
/*   show_vars(t, g); */
/*   printf("--------\n"); */
/*   return 0; */
/* } */
/*   /\* my_cd(argv + 1, g); *\/ */
/*   /\*   printf("$PWD=%s\n", get_var("PWD", g)); *\/ */
/*   /\*   printf("$OLDPWD=%s\n", get_var("OLDPWD", g)); *\/ */
/*   return 0; */
/* } */
