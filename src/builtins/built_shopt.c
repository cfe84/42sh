/*
** built_shopt.c for built_shopt in /u/a1/kadiri_a/tmp/grosli_o-42sh/src/builtins
**
** Made by anass kadiri
** Login   <kadiri_a@epita.fr>
**
** Started on  Mon Jan 17 19:53:20 2005 anass kadiri
** Last update Tue Jan 18 20:08:26 2005 anass kadiri
*/

#include "builtins.h"

/*
** if opt is valid then interpret the option
** else print it
*/
static int      is_valid_opt(char *opt)
{
  int           i = 1;

  if (strlen(opt) == 1)
    return 0;
  while (opt[i] != '\0')
    {
      if (opt[i] != 'q' && opt[i] != 's' && opt[i] != 'u')
        return 0;
      i++;
    }
  return 1;
}

/*
** extract option from opt
*/
static void     extract_opt(char *str, struct s_shopt_opt *opt)
{
  int           i = 1;

  while (str[i] != '\0')
    {
      if (str[i] == 's')
        opt->s = 1;
      if (str[i] == 'u')
        opt->u = 1;
      if (str[i] == 'q')
        opt->q = 1;
      i++;
    }
}

/*
** get options from cmd
*/
static void      get_options(char **cmd, struct s_shopt_opt *opt)
{
  int           i = 1;

  while (cmd[i] != NULL && is_opt(cmd[i]))
    {
      if (is_opt(cmd[i]) && is_valid_opt(cmd[i]))
        extract_opt(cmd[i], opt);
      i++;
    }
}

/*
** init the opt struct
*/
static void     init_opt(struct s_shopt_opt *opt)
{
  opt->s = 0;
  opt->u = 0;
  opt->q = 0;
}

/*
** init_shopt tab in g
*/
void			init_shopt(struct s_glob *g)
{
  struct s_shopt	*tab;

  tab = malloc(3 * sizeof(struct s_shopt));
  tab[0].name = "xpg_echo";
  tab[0].on = 0;
  tab[1].name = NULL;
  tab[1].on = 0;
  g->shopt = tab;
}

/*
** shopt with option -s or -u
*/
static void	shopt_(struct s_glob *g, int s)
{
  int		i = 0;

  for (i = 0; g->shopt[i].name; i++)
    {
      if (s)
	{
	  if (g->shopt[i].on)
	    {
	      printf("%s        ", g->shopt[i].name);
	      printf("on\n");
	    }
	}
      else
	{
	  if (!g->shopt[i].on)
	    {
	      printf("%s        ", g->shopt[i].name);
	      printf("off\n");
	    }
	}
    }
}

/*
** the shopt builtins
*/
void			built_shopt(char **command, struct s_glob *g)
{
  struct s_shopt_opt	opt;
  int			i = 0;

  init_opt(&opt);
  get_options(command, &opt);
  if (opt.s && opt.u)
    printf("42$: shopt: cannot set and unset shell options simultaneously\n");
  if (opt.s || opt.u)
    {
      if (opt.s)
	shopt_(g, 1);
      else
	if (opt.u)
	  shopt_(g, 0);
      return;
    }
  for (i = 0; g->shopt[i].name; i++)
    {
      printf("%s        ", g->shopt[i].name);
      if (g->shopt[i].on)
	printf("on\n");
      else
	printf("off\n");
    }
}
