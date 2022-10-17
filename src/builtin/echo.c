/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/16 14:16:25 by mbatstra      #+#    #+#                 */
/*   Updated: 2022/10/17 17:06:41 by cicekyuzbas   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

// error messages? should output be buffered?
int	builtin_echo(const char *str, int nflag)
{
	if (nflag)
	{
		if (printf("%s\n", str) > 0)
			return (0);
		else
			return (1);
	}
	else
	{
		if (printf("%s", str) > 0)
			return (0);
		else
			return (1);
	}
}
