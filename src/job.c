/*
** job.c for 42sh in src
**
** Made by feval_c
** Login   <feval_c@epita.fr>
**
** Started on  Mon Jan 17 18:04:47 2005 feval_c
** Last update Mon Jan 17 19:47:18 2005 feval_c
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include "strings.h"
#include "job.h"
#include "global.h"

static void destroy_job(struct s_job *job)
{
  free(job->name);
  free(job);
}

struct s_jobs	*init_job(void)
{
  struct s_jobs	*jobs;

  jobs = malloc(sizeof (struct s_job));
  jobs->max_job = 0;
  jobs->jobs = NULL;
  return jobs;
}

void		add_job(struct s_jobs *j, int pid, char *name)
{
  struct s_job	*job;

  job = malloc(sizeof (struct s_job));
  job->next = j->jobs;
  j->jobs = job;
  job->pid = pid;
  if (name != NULL)
  {
    job->name = strdup(name);
    job->jobid = ++(j->max_job);
    printf("[%d] %s\n", job->jobid, name);
  }
}

static void	aff_term(struct s_job *job, int ret)
{
  printf("[%d]+ as exited with code %d \t%s\n", job->jobid, ret, job->name);
}

void		verif_and_kill(struct s_jobs *j)
{
  struct s_job	**jobs = &(j->jobs);
  struct s_job	*back;
  int		ret;

  while (*jobs != NULL)
  {
    if (waitpid((*jobs)->pid, &ret, WNOHANG) && WIFEXITED(ret))
    {
      back = *jobs;
      *jobs = back->next;
      if (back->name != NULL)
      {
        aff_term(back, ret);
        if (back->jobid == j->max_job)
	  j->max_job--;
      }
      destroy_job(back);
    }
    else
      jobs = &((*jobs)->next);
  }
}
