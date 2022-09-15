/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:07:07 by mbatstra          #+#    #+#             */
/*   Updated: 2022/09/15 16:16:50 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	builtin_pwd(void)
{
	char	*path;

	path = NULL;
	path = getcwd(path, 1);
	if (path == NULL)
	{
		perror("pwd");
		return (1);
	}
	else
	{
		printf("%s\n", path);
		free(path);
		return (0);
	}
}

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

// error messages? should output be buffered?
int	builtin_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (printf("%s\n", envp[i]) < 0)
			return (1);
		i++;
	}
	return (0);
}

void	builtin_exit(void)
{
	exit(EXIT_SUCCESS);
}
