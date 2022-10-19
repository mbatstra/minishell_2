/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/16 14:16:25 by mbatstra      #+#    #+#                 */
/*   Updated: 2022/10/19 13:07:23 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "exec.h"

// error messages? should output be buffered?
// int	builtin_echo(const char *str, int nflag)
// {
// 	if (nflag)
// 	{
// 		if (!str)
// 		{
// 			printf("\n");
// 			return (0);
// 		}
// 		else if (printf("%s\n", str) > 0)
// 			return (0);
// 		else
// 			return (1);
// 	}
// 	else
// 	{
// 		if (printf("%s", str) > 0)
// 			return (0);
// 		else
// 			return (1);
// 	}
// }

void	write_echo(t_list *arg, int i)
{
	char	*command;
	int		x;

	while (i > 0)
	{
		arg = arg->next;
		i--;
	}
	while (arg)
	{
		command = (char *)(arg->content);
		x = 0;
		if (!ft_str_cmp("\"\"", command))
		{
			while (command[x])
			{
				ft_putchar_fd(command[x], 1);
				x++;
			}
		}
		if (arg->next)
			ft_putchar_fd(' ', 1);
		arg = arg->next;
	}
}

int	builtin_echo(t_list *arg)
{
	int		new_line;
	int		i;
	t_list	*tmp;

	new_line = 1;
	i = 1;
	tmp = arg;
	if (!arg->next)
	{
		printf("\n");
		return (0);
	}
	while (ft_str_cmp((char *)(tmp->next->content), "-n"))
	{
		new_line = 0;
		i++;
		tmp = tmp->next;
	}
	write_echo(arg, i);
	if (new_line)
		ft_putchar_fd('\n', 1);
	return (0);
}
