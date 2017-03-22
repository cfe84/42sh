/*
** history.c for 42sh in src
**
** Made by feval_c
** Login   <feval_c@epita.fr>
**
** Started on  Thu Jan  6 20:57:03 2005 feval_c
** Last update Fri Jan 14 14:27:38 2005 feval_c
*/

/**
 ** @file history.c
 ** History of read_line management file.
 */

#include <stdlib.h>
#include <string.h>
#include "history.h"

#ifdef SUN
char	*strdup(const char *a);
#endif /* !SUN */

struct s_history	*create_history(char *entry)
{
  struct s_history	*hist = NULL;

  hist = malloc(sizeof (struct s_history));
  hist->next = NULL;
  hist->entry = strdup(entry);
  return hist;
}

/**
 ** Add an entry to history
 */
void			add_to_history(struct s_history **hist, char *entry)
{
  struct s_history	*new;

  new = create_history(entry);
  new->next = *hist;
  *hist = new;
}

void			destroy_history(struct s_history *hist)
{
  while (hist != NULL)
  {
    free(hist->entry);
    destroy_history(hist->next);
    free(hist);
  }
}
