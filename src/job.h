/*
** job.h for 42sh in src
**
** Made by feval_c
** Login   <feval_c@epita.fr>
**
** Started on  Mon Jan 17 18:07:39 2005 feval_c
** Last update Mon Jan 17 18:43:43 2005 feval_c
*/

#ifndef JOB_H_
# define JOB_H_

struct		s_job
{
  char		*name;
  int		pid;
  int		jobid;
  struct s_job	*next;
};

struct		s_jobs
{
  int		max_job;
  struct s_job	*jobs;
};

struct s_jobs	*init_job(void);
void		add_job(struct s_jobs *j, int pid, char *name);
void		verif_and_kill(struct s_jobs *j);

#endif /* !JOB_H_ */
