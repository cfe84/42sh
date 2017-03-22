/*
** env_var.c for env_var in ~/tmp/grosli_o-42sh/src
**
** Made by anass kadiri
** Login   <kadiri_a@epita.fr>
**
** Started on  Sun Jan 16 19:55:03 2005 anass kadiri
** Last update Tue Jan 18 20:34:25 2005 anass kadiri
*/

#include "env_var.h"

/*
** init a s_env_var structure
*/
static struct s_env_var	*init_var(char *name, char *val)
{
  struct s_env_var	*tmp;

  if ((tmp = malloc(sizeof(struct s_env_var))) == NULL)
    return NULL;
  tmp->name = name;
  tmp->val = val;
  tmp->next = NULL;
  return tmp;
}

/*
** free the s_env_var structure
*/
static void	free_var(struct s_env_var *var)
{
  free(var->name);
 /*  free(var->val); */
  free(var);
}

/*
** set the environment name with the value val
*/
void			set_var(char *name, char *val, struct s_glob *g)
{
  struct s_env_var	*tmp;
  int			ok = 0;

  tmp = g->env_var;
  if (tmp == NULL)
    g->env_var = init_var(name, val);
  else
    {
      if (!strcmp(name, tmp->name))
	{
	  free(tmp->val);
	  tmp->val = val;
	  ok = 1;
	}
      while (tmp->next != NULL && !ok)
	{
	  if (!strcmp(name, tmp->name))
	    {
	      free(tmp->val);
	      tmp->val = val;
	      ok = 1;
	    }
	  tmp = tmp->next;
	}
      if (!strcmp(name, tmp->name))
	{
	  free(tmp->val);
	  tmp->val = val;
	  ok = 1;
	}
      if (!ok)
	tmp->next = init_var(name, val);
    }
}

/*
** unset the environment var name
*/
void			unset_var(char **name, struct s_glob *g)
{
  struct s_env_var	*head;
  struct s_env_var	*tmp;
  struct s_env_var	*tmp2 = NULL;
  int			found = 0;

  head = g->env_var;
  if (head == NULL)
    return;
  else
    {
      if (!strcmp(head->name, name[1]))
	{
	  tmp2 = g->env_var;
	  g->env_var = g->env_var->next;
	  found = 1;
	}
      else
	{
	  tmp = head;
	  while (tmp->next != NULL && strcmp(tmp->next->name, name[1]))
	    tmp = tmp->next;
	  if (tmp->next != NULL && !strcmp(tmp->next->name, name[1]))
	    {
	      found = 1;
	      tmp2 = tmp->next;
	      tmp->next = tmp->next->next;
	    }
	}
    }
  if (found)
    free_var(tmp2);
}

/*
** get the value of the environment var name
*/
char			*get_var(char *name, struct s_glob *g)
{
  struct s_env_var	*head;
  struct s_env_var	*tmp;

  head = g->env_var;
  tmp = head;
  while (tmp != NULL)
    {
      if (!strcmp(tmp->name, name))
	return tmp->val;
      tmp = tmp->next;
    }
  return NULL;
}

/*
** show all environment vars declared
** option ??
*/
void			show_vars(char **useless, struct s_glob *g)
{
  struct s_env_var	*tmp;

  useless = useless;
  tmp = g->env_var;
  while (tmp != NULL)
    {
      printf("\033[32m$%s\033[0m=%s\033[0m \n", tmp->name, tmp->val);
      tmp = tmp->next;
    }
}
