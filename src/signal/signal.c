/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 17:42:50 by mbatstra      #+#    #+#                 */
/*   Updated: 2022/11/03 14:50:49 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "readline/readline.h"
#include "readline/history.h"
#include "minishell.h"
#include "libft.h"

void	signal_suppress_output(void)
{
	struct termios	s_termios;

	if (tcgetattr(0, &s_termios))
		perror("minishell: tcsetattr");
	s_termios.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, 0, &s_termios))
		perror("minishell: tcsetattr");
}

void	catch_quit(int sig)
{
	signal(sig, &catch_quit);
	rl_replace_line("", 0);
}

void	catch_int(int sig)
{
	signal(sig, &catch_int);
	ioctl(IN, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	catch_int_child(int sig)
{
	signal(sig, &catch_int_child);
}

