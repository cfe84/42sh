/*
** built_cd.c for built_cd in /u/a1/kadiri_a/tmp/grosli_o-42sh/src/builtins
**
** Made by anass kadiri
** Login   <kadiri_a@epita.fr>
**
** Started on  Sun Jan 16 19:51:21 2005 anass kadiri
** Last update Tue Jan 18 20:55:02 2005 anass kadiri
*/

#include "builtins.h"

/*
** updates $OLDPWD and $PWD
*/
void	update_vars(char *pwd, char *oldpwd, struct s_glob *g)
{
  set_var("OLDPWD", oldpwd, g);
  set_var("PWD", pwd, g);
}

/*
** swap $OLDPWD <-> $PWD
*/
static void	swap_vars(struct s_glob *g)
{
  char		*swap;

  swap = strdup(get_var("OLDPWD", g));
  set_var("PWD", strdup(get_var("OLDPWD", g)), g);
  set_var("OLDPWD", swap, g);
}

/*
** cd builtins
** cd works
** cd - works
*/
void	built_cd(char **cmd, struct s_glob *g)
{
  if (cmd[1] == NULL)
    {
      if (!chdir(get_var("HOME", g)))
	update_vars(strdup(get_var("HOME", g)), strdup(get_var("PWD", g)), g);
      else
	printf("42$: cd: HOME not set\n");
    }
  else
    {
      if (!strcmp("-", cmd[1]))
	{
	  if (get_var("OLDPWD", g))
	    {
	      if (!chdir(get_var("OLDPWD", g)))
		swap_vars(g);
	    }
	  else
	    printf("42$: cd: OLDPWD not set\n");
	}
      else
	{
	  if (!chdir(cmd[1]))
	    update_vars(getcwd(NULL, MAXPATHLEN), strdup(get_var("PWD", g)), g);
	  else
	    {
	      fprintf(stderr, "42$: cd: ");
	      perror(cmd[1]);
	    }
	}
    }
}
