/*
** my_signal.h for 42sh in /u/a1/raymon_e
**
** Made by enguerrand raymond
** Login   <raymon_e@epita.fr>
**
** Started on  Mon Jan 17 20:09:48 2005 enguerrand raymond
** Last update Tue Jan 18 19:40:51 2005 enguerrand raymond
*/

#ifndef MY_SIGNAL_H_
# define MY_SIGNAL_H_

void	redir_sig(int sig, void(*handler)(int));
void	ctrl_c(int sig);

#endif /* !MY_SIGNAL_H_ */
