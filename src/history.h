/*
** history.h for 42sh in src
**
** Made by feval_c
** Login   <feval_c@epita.fr>
**
** Started on  Thu Jan  6 21:00:02 2005 feval_c
** Last update Thu Jan  6 21:04:44 2005 feval_c
*/

#ifndef HISTORY_H_
# define HISTORY_H_

struct			s_history
{
  char			*entry;
  struct s_history	*next;
};

struct s_history	*create_history(char *entry);
void			add_to_history(struct s_history **hist, char *entry);
void			destroy_history(struct s_history *hist);

#endif /* !HISTORY_H_ */
