/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/20 15:11:42 by mbatstra      #+#    #+#                 */
/*   Updated: 2022/10/18 15:46:10 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	invalid_name(char *name)
{
	int			i;

	i = 0;
	while (name[i])
	{
		if (ft_isdigit(name[0]) || (!ft_isalpha(name[i]) && \
				!ft_isdigit(name[i]) && name[i] != '_'))
			return (1);
		i++;
	}
	return (0);
}

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

int	builtin_unset(t_list **envp, t_list *arg)
{
	t_list	*node;
	t_list	*prev;
	char	*name;

	if (!arg->next)
		return (1);
	name = (char *)(arg->next->content);
	if (invalid_name(name))
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
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
