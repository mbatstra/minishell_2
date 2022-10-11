/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:53:52 by mbatstra          #+#    #+#             */
/*   Updated: 2022/10/11 20:01:27 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "libft.h"

int	parse_word(t_cmd *cmd_table, t_list **tokens)
{
	t_list	*node;
	int		i_cmd;
	int		error;

	node = *tokens;
	i_cmd = 0;
	error = 0;
	// count number of pipes and allocate pointers for simplecmds
	while (node != NULL)
	{
		if (((t_token *)node->content)->type == WORD)
		{} //append to current simplecmd
		else if (((t_token *)node->content)->type == PIPE)
		{} // new simplecmd
		else
		{} // shouldn't happen
		node = node->next;
	}
}
