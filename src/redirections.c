/*
** redirections.c for 42sh in src
**
** Made by feval_c
** Login   <feval_c@epita.fr>
**
** Started on  Tue Jan 18 16:40:55 2005 feval_c
** Last update Tue Jan 18 18:59:36 2005 feval_c
*/

/**
 ** @file redirections.c
 ** Contains redirections commands for 42sh
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "redirections.h"
#include "defines.h"
#include "strings.h"

/**
 ** Add a redirection in a redirection list
 ** @param num the file descriptor to redirect
 ** @param type redirection or indirection ?
 ** @param file where output is redirect
 ** @param redir redirection list
 */
struct s_redir		*add_redir(char *num,
				   int type,
				   char *file,
				   struct s_redir *redir)
{
  struct s_redir	*new = NULL;

  if ((new = malloc(sizeof (struct s_redir))) == NULL)
    return NULL;
  new->type = type;
  if (num != NULL)
    new->fd = atoi(num);
  else
    if (type == R_CH || type == D_R_CH)
      new->fd = STDOUT_FILENO;
    else
      new->fd = STDIN_FILENO;
  new->redir = strdup(file);
  new->next = redir;
  return new;
}

void	destroy_redir(struct s_redir *r)
{
  if (r == NULL)
    return;
  free(r->redir);
  destroy_redir(r->next);
  free(r);
}

/**
 ** Creates the file with good flags
 */
static int	create_fd(struct s_redir *r)
{
  int		flag = 0;
  int		fd;

  if (r->type == R_CH)
    flag = O_WRONLY | O_TRUNC | O_CREAT;
  else
    if (r->type == D_R_CH)
      flag = O_WRONLY | O_CREAT | O_APPEND;
    else
      if (r->type == L_CH)
	flag = O_RDONLY;
  if ((fd = open(r->redir, flag, 0666)) < 0)
  {
    fprintf(stderr, "42sh: ");
    perror(r->redir);
    return -1;
  }
  return fd;
}

/**
 ** Executes redirections.
 ** @return a backup of previous stdfds as int[3], or NULL if an error occured
 */
int	*redirections(struct s_redir *r)
{
  int	*backup;
  int	fd;

  backup = malloc(3 * sizeof (int));
  backup[0] = backup[1] = backup[2] = -1;
  while (r != NULL)
  {
    if ((r->fd == STDIN_FILENO || r->fd == STDOUT_FILENO ||
	 r->fd == STDERR_FILENO) && backup[r->fd] == -1)
      backup[r->fd] = dup(r->fd);
    if ((fd = create_fd(r)) >= 0)
      dup2(fd, r->fd);
    else
    {
      free(backup);
      return NULL;
    }
    r = r->next;
  }
  return backup;
}

/**
 ** restore previous backups of files descriptors
 */
void	redir_restore_backup(int *backup)
{
  int	i;

  for (i = 0; i < 3; i++)
    if (backup[i] != -1)
    {
      dup2(backup[i], i);
      close(backup[i]);
    }
  free(backup);
}
