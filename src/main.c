/*
** main.c for src in src
**
** Made by feval_c
** Login   <feval_c@epita.fr>
**
** Started on  Thu Jan  6 18:40:23 2005 feval_c
** Last update Tue Jan 18 19:41:50 2005 enguerrand raymond
*/
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include "launch.h"
#include "signal/my_signal.h"

/**
 ** Launches 42sh
 */
int	main(int argc, char **argv)
{
  redir_sig(SIGTERM, ctrl_c);
  launch(argc, argv);
  return 0;
}
