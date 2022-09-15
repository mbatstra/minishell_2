/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:46:41 by mbatstra          #+#    #+#             */
/*   Updated: 2022/09/06 17:46:43 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*current;

	if (*lst == NULL)
		return ;
	temp = *lst;
	current = temp;
	while (current->next != NULL)
	{
		current = temp;
		del(current->content);
		free(current);
		current = temp;
		temp = temp->next;
	}
	*lst = NULL;
}
