/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:11:42 by mbatstra          #+#    #+#             */
/*   Updated: 2022/09/20 20:26:31 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// check proper name length in order to not match similar-starting names
static void	match_node(t_list **node, t_list **prev, char *name)
{
	unsigned long	temp_namelen;

	while (*node != NULL)
	{
		temp_namelen = (void *)ft_strchr((*node)->content, '=') - \
					(*node)->content;
		if (temp_namelen < ft_strlen(name))
			temp_namelen = ft_strlen(name);
		if (!ft_strncmp((*node)->content, name, temp_namelen))
			break ;
		*prev = *node;
		*node = (*node)->next;
	}
}

int	builtin_unset(t_list **envp, char *name)
{
	t_list	*node;
	t_list	*prev;

	node = *envp;
	prev = *envp;
	match_node(&node, &prev, name);
	if (node == NULL)
		return (1);
	else if (node == prev)
		(*envp)->next = node->next;
	else
		prev->next = node->next;
	ft_lstdelone(node, &free);
	return (0);
}
