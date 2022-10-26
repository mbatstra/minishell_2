/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/15 15:18:51 by mbatstra      #+#    #+#                 */
/*   Updated: 2022/10/26 11:22:35 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "minishell.h"
#include "libft.h"
#include "exec.h"

// path == NULL means no arg
// will not free if path was alloc'd outside this func
// parent dir (..) env vars and relative paths should be expanded
// 		*BEFORE* calling any builtin

int	builtin_cd(char *path, t_list **envp)
{
	int	is_freeable;

	is_freeable = 0;
	if (path == NULL)
	{
		path = ft_strdup(env_getval(*envp, "HOME", 4));
		is_freeable = 1;
	}
	if (path == NULL)
		return (1);
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	env_setval(envp, "OLDPWD", env_getval(*envp, "PWD", 4));
	env_setval(envp, "PWD", path);
	if (is_freeable)
		free(path);
	return (0);
}
