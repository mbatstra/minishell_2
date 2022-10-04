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
	current = *lst;
	temp = current->next;
	while (current != NULL)
	{
		del(current->content);
		free(current);
		current = temp;
		if (temp != NULL)
			temp = temp->next;
	}
	*lst = NULL;
}
