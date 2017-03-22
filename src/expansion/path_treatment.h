/*
** path_treatment.h for 42sh in /goinfre/grosli_o-42sh/src/expansion
**
** Made by olivier delestre
** Login   <delest_o@epita.fr>
**
** Started on  Tue Jan 18 15:11:15 2005 olivier delestre
** Last update Tue Jan 18 15:16:15 2005 olivier delestre
*/

#ifndef		PATH_TREATMENT_H_
# define	PATH_TREATMENT_H_

struct s_cmd	*sort_arglist(struct s_cmd *cmd);
int		is_quoted(char *s);
char		*my_repcat(char *r1, char *r2, int final_slash);
void		add_to_list(char *s, struct s_cmd **p);
int		eat_begin(char *s, int level);

#endif	    /* !PATH_TREATMENT_H_ */
