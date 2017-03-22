/*
** paths.c for 42sh in /goinfre/grosli_o-42sh/src/expansion
**
** Made by olivier grosliere
** Login   <grosli_o@epita.fr>
**
** Started on  Sun Jan 16 15:17:09 2005 olivier grosliere
** Last update Tue Jan 18 18:32:24 2005 anass kadiri
*/
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "../libs/my_fnmatch.h"
#include "../global.h"
#include "../ast.h"
#include "expand.h"
#include "paths.h"
#include "path_treatment.h"

static char	*get_pattern(char *s, int level, int *is_dir, int *f_rep)
{
  int		i = 0;
  int		deb = 0;
  int		fin = -1;
  char		*res = NULL;
  int		bs_on = 0;

  deb = i = eat_begin(s, level);
  if (s[i] == '\0')
    return NULL;
  while (s[i] != '\0' && fin == -1)
    {
      if (s[i] == '\\')
	bs_on = !bs_on;
      else
	if (!bs_on && s[i] == '/')
	  fin = i;
	else
	  bs_on = 0;
      i++;
    }
  if (fin == -1)
    fin = i;
  *is_dir = s[i - 1] == '/';
  *f_rep = s[i - 1] == '/' && s[i] == '\0';
  res = malloc(fin - deb + 1);
  res[fin -deb] = '\0';
  return strncpy(res, s + deb, fin - deb);
}

static char	*get_dir(char *s)
{
  int		i = 0;
  int		last_slash = 0;
  int		bs_on = 0;
  char		*res = NULL;

  while (s[i] != '\0')
    {
      if (s[i] == '\\')
	bs_on = !bs_on;
      else
	{
	  if (s[i] == '/' && !bs_on)
	    last_slash = i + 1;
	  else
	    if ((s[i] == '*' || s[i] == '?' || s[i] == '[') && !bs_on)
	      {
		res = malloc(last_slash + 1);
		res[last_slash] = '\0';
		return strncpy(res, s, last_slash);
	      }
	    else
	      bs_on = 0;
	}
      ++i;
    }
  return NULL;
}

static int	get_level(char *s)
{
  int		i = 0;
  int		nb_slash = 0;
  int		bs_on = 0;

  while (s[i] != '\0')
    {
      if (s[i] == '\\')
	bs_on = !bs_on;
      else
	if (s[i] == '/' && !bs_on)
	  nb_slash++;
	else
	  bs_on = 0;
      ++i;
    }
  return nb_slash;
}

static int	is_rep(char *path)
{
  struct stat	*stati_path;

  stati_path = malloc(sizeof (struct stat));
  stat(path, stati_path);
  if ((stati_path->st_mode & S_IFDIR) == 0040000)
    {
      free(stati_path);
      return 1;
    }
  return 0;
}

static int	expand_command(char *dir,
			       struct s_cmd **p,
			       char *ori_str,
			       int subdir)
{
  int		is_dir = 0;
  int		f_rep = 0;
  int		max_level = 0;
  char		*pattern;
  struct dirent *dirl;
  DIR		*rep;

  if ((pattern = get_pattern(ori_str, subdir, &is_dir, &f_rep)) == NULL)
    return 1;
  if ((rep = dir[0] == '\0' ? opendir(".") : opendir(dir)) == NULL)
    return 1;
  max_level = get_level(ori_str);
  while ((dirl = readdir(rep)))
    if (strcmp(dirl->d_name, ".") && strcmp(dirl->d_name, ".."))
      {
	if (!my_fnmatch(pattern, dirl->d_name, 0) && dirl->d_name[0] != '.')
	  {
	    expand_command(my_repcat(dir, dirl->d_name, 0),
			   p, ori_str, subdir + 1);
	    if ((f_rep && is_rep(my_repcat(dir, dirl->d_name, 0)))
		|| (!f_rep && max_level == subdir))
	      add_to_list(my_repcat(dir, dirl->d_name, f_rep), p);
	  }
      }
  closedir(rep);
  return 0;
}

static void	set_last_pointer(struct s_cmd *cmd, struct s_cmd *new_follow)
{
  while (cmd->next != NULL)
    cmd = cmd->next;
  cmd->next = new_follow;
}

void		expand_paths(struct s_ast *ast, struct s_glob *g)
{
  struct s_cmd	*p = ast->cmd_list;
  struct s_cmd	*new_list = NULL;
  struct s_cmd	*old = p;
  char		*dir = NULL;

  g = g;
  if (p == NULL)
    return;
  while (p != NULL)
    {
      new_list = NULL;
      if (!is_quoted(p->cmd))
	{
	  if ((dir = get_dir(p->cmd)) != NULL)
	    {
	      expand_command(dir, &new_list, p->cmd, get_level(dir));
	      if (new_list != NULL)
		{
		  set_last_pointer(sort_arglist(new_list), p->next);
		  old->next = new_list;
		}
	    }
	}
      old = p;
      p = p->next;
    }
}
