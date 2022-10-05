/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:09:16 by mbatstra          #+#    #+#             */
/*   Updated: 2022/10/05 21:25:44 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "libft.h"

void	parse_tokens(t_cmd *cmd_table, t_list **tokens)
{
	t_list	*node;
	int		error;

	node = *tokens;
	while (node != NULL)
	{
		if (((t_token *)node->content)->type < PIPE)
		{
			error = parse_redir(cmd_table, node);
			printf("%d\n", error);
		}
		// if (error)
			// deal with it
		node = node->next;
	}
}
