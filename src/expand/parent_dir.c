/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:31:49 by mbatstra          #+#    #+#             */
/*   Updated: 2022/09/22 17:16:20 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*expand_parent_dir(t_list *envp)
{
	char	*pwd;
	char	*tail;
	char	*parent_dir;

	pwd = env_getval(envp, "PWD");
	if (pwd == NULL)
	{
		free(pwd);
		return (NULL);
	}
	tail = pwd + ft_strlen(pwd);
	while (tail > pwd && *tail != '/')
		tail--;
	if (tail != pwd)
		parent_dir = ft_strndup(pwd, tail - pwd);
	else
		parent_dir = ft_strdup("/");
	return (parent_dir);
}
