/*
** strings.h for 42sh in src
**
** Made by feval_c
** Login   <feval_c@epita.fr>
**
** Started on  Mon Jan 17 18:44:17 2005 feval_c
** Last update Mon Jan 17 19:46:20 2005 feval_c
*/

#ifndef STRINGS_H_
# define STRINGS_H_

# include <strings.h>

# ifdef SUN
char	*strdup(const char *str);
# endif /* !SUN */

char	*vectostr(char **strs);

#endif /* !STRINGS_H_ */
