/*
** path_treatment.c for 42sh in /goinfre/grosli_o-42sh/src/expansion
**
** Made by olivier delestre
** Login   <delest_o@epita.fr>
**
** Started on  Tue Jan 18 15:12:11 2005 olivier delestre
** Last update Tue Jan 18 15:16:31 2005 olivier delestre
*/
#include <stdio.h>
#include <stdlib.h>
#include "../ast.h"
#include "path_treatment.h"

struct s_cmd	*sort_arglist(struct s_cmd *cmd)
{
  struct s_cmd	*tmp_str;
  char		*tmp_s;
  int		is_modif = 1;

  if (cmd == NULL || cmd->next == NULL)
    return cmd;
  while (is_modif)
    {
      is_modif = 0;
      tmp_str = cmd;
      while (tmp_str->next != NULL)
	{
	  if (strcmp(tmp_str->cmd, tmp_str->next->cmd) > 0)
	    {
	      tmp_s = tmp_str->cmd;
	      tmp_str->cmd = tmp_str->next->cmd;
	      tmp_str->next->cmd = tmp_s;
	      is_modif = 1;
	    }
	  tmp_str = tmp_str->next;
	}
    }
  return cmd;
}

int	is_quoted(char *s)
{
  if (s == NULL)
    return 1;
  return s[0] == '"' || s[0] == '\'' || s[0] == '`';
}

char		*my_repcat(char *r1, char *r2, int final_slash)
{
  char		*res;
  unsigned int	i;
  unsigned int	j;

  if (r1 == NULL || r2 == NULL)
    return NULL;
  res = malloc(strlen(r1) + strlen(r2) + 3);
  for (i = 0; i < strlen(r1); ++i)
    res[i] = r1[i];
  if (i >= 1 && res[i - 1] != '/')
    res[i++] = '/';
  for (j = 0; j < strlen(r2); ++j)
    res[i + j] = r2[j];
  if (final_slash == 1)
    res[i++ + j] = '/';
  res[i + j] = '\0';
  return res;
}

void		add_to_list(char *s, struct s_cmd **p)
{
  struct s_cmd	*new;

  new = malloc(sizeof(struct s_cmd));
  new->cmd = s;
  new->next = *p;
  *p = new;
}

int		eat_begin(char *s, int level)
{
  int		i = 0;
  int		bs_on = 0;

  while (level > 0 && s[i] != '\0')
    {
      if (s[i] == '\\')
	bs_on = !bs_on;
      else
	if (s[i] == '/' && s[i + 1] != '/')
	  level--;
	else
	  bs_on = 0;
      i++;
    }
  return i;
}
