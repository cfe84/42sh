/*
** redirections.h for 42sh in src
**
** Made by feval_c
** Login   <feval_c@epita.fr>
**
** Started on  Tue Jan 18 16:41:42 2005 feval_c
** Last update Tue Jan 18 18:49:24 2005 feval_c
*/

#ifndef REDIRECTIONS_H_
# define REDIRECTIONS_H_

/**
 ** @param fd file descriptor
 ** @param type type of redirection
 ** @param redir filename where the data will be redirected
 */
struct			s_redir
{
  int			fd;
  int			type;
  char			*redir;
  struct s_redir	*next;
};

struct s_redir		*add_redir(char *num,
				   int type,
				   char *file,
				   struct s_redir *redir);
struct s_ast		*destroy_ast(struct s_ast *a);
void			destroy_redir(struct s_redir *r);
int			*redirections(struct s_redir *r);
void			redir_restore_backup(int *backup);

#endif /* !REDIRECTIONS_H_ */
