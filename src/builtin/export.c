/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:37:33 by mbatstra          #+#    #+#             */
/*   Updated: 2022/09/20 20:24:51 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

static int	is_defined(t_list **envp, char *nameval)
{
	t_list	*node;
	int		namelen;

	node = *envp;
	namelen = ft_strchr(nameval, '=') - nameval;
	while (node != NULL)
	{
		if (!ft_strncmp(node->content, nameval, namelen))
			return (1);
		node = node->next;
	}
	return (0);
}

static char	**nameval_split(char *nameval)
{
	char	**spl_nameval;
	char	*name;
	char	*val;
	int		namelen;

	spl_nameval = (char **)malloc(2 * sizeof(char *));
	namelen = ft_strchr(nameval, '=') - nameval;
	name = ft_strndup(nameval, namelen);
	val = ft_strdup(ft_strchr(nameval, '=') + 1);
	if (spl_nameval == NULL || name == NULL || val == NULL)
	{
		free(spl_nameval);
		free(name);
		free(val);
		return (NULL);
	}
	spl_nameval[0] = name;
	spl_nameval[1] = val;
	return (spl_nameval);
}

int	builtin_export(t_list **envp, char *nameval)
{
	t_list	*node;
	char	*dup;
	char	**spl_nameval;

	if (is_defined(envp, nameval))
	{
		spl_nameval = nameval_split(nameval);
		if (spl_nameval == NULL)
			return (1);
		env_setval(envp, spl_nameval[0], spl_nameval[1]);
		free(spl_nameval[0]);
		free(spl_nameval[1]);
		free(spl_nameval);
		return (0);
	}
	dup = ft_strdup(nameval);
	node = ft_lstnew(dup);
	if (node == NULL)
	{
		free(dup);
		return (1);
	}
	ft_lstadd_back(envp, node);
	return (0);
}
