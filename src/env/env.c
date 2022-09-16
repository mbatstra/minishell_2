/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:07:01 by mbatstra          #+#    #+#             */
/*   Updated: 2022/09/16 13:49:48 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

// initialize string array and copy envp
char	**env_init(char **envp)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = (char **)malloc((arr_len(envp) + 1) * sizeof(char *));
	if (!new_env)
		return (NULL);
	arr_init(new_env, arr_len(envp) + 1);
	while (envp[i] != NULL)
	{
		new_env[i] = ft_strdup(envp[i]);
		if (new_env[i] == NULL)
		{
			arr_clear(new_env);
			return (NULL);
		}
		i++;
	}
	return (new_env);
}

// get the value for any env var by name
char	*env_getval(char **envp, const char *name)
{
	int	i;

	i = 0;
	while (envp[i] != NULL && ft_strncmp(envp[i], name, ft_strlen(name)))
		i++;
	if (envp[i] != NULL)
		return (ft_strchr(envp[i], '=') + 1);
	return (NULL);
}

// set the val of name env var
// name and val are not freed in this function
void	env_setval(char **envp, const char *name, const char *val)
{
	char	*new;
	int		i;

	i = 0;
	while (envp[i] != NULL && ft_strncmp(envp[i], name, ft_strlen(name)))
		i++;
	if (envp[i] == NULL)
		return ;
	new = (char *)malloc((ft_strlen(name) + ft_strlen(val) + 2) * sizeof(char));
	if (new == NULL)
		return ;
	ft_memmove(new, name, ft_strlen(name));
	new[ft_strlen(name)] = '=';
	ft_strlcpy(new + ft_strlen(name) + 1, val, ft_strlen(val) + 1);
	free(envp[i]);
	envp[i] = new;
}
