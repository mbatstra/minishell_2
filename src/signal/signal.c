/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:42:50 by mbatstra          #+#    #+#             */
/*   Updated: 2022/10/28 16:35:56 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include "readline/readline.h"
#include "readline/history.h"
#include "minishell.h"
#include "libft.h"

void	catch_quit(int sig)
{
	signal(sig, &catch_quit);
	rl_replace_line("", 0);
}

void	catch_int(int sig)
{
	signal(sig, &catch_int);
	ioctl(IN, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}
