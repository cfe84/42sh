/*
** my_signal.c for 42sh in /u/a1/raymon_e
**
** Made by enguerrand raymond
** Login   <raymon_e@epita.fr>
**
** Started on  Mon Jan 17 20:35:08 2005 enguerrand raymond
** Last update Tue Jan 18 19:49:15 2005 enguerrand raymond
*/

#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

int fg_pid = 29736;

void			redir_sig(int sig, void(*handler)(int))
{
  sigset_t		set;
  struct sigaction	act;

  sigprocmask(SIG_SETMASK, NULL, &set);
  sigdelset(&set, sig);
  sigprocmask(SIG_SETMASK, &set, NULL);
  act.sa_handler = handler;
  sigaction(sig, &act, NULL);
}

void			ctrl_c(int sig)
{
  sig = sig;
  printf("asdgsdgSA\n");
  /*kill(fg_pid, SIGTERM);*/
}
