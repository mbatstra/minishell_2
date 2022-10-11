/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:09:16 by mbatstra          #+#    #+#             */
/*   Updated: 2022/10/11 18:58:41 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "libft.h"

void	parse_tokens(t_cmd *cmd_table, t_list **tokens)
{
	int	error;

	error = parse_redir(cmd_table, tokens);
	if (error)
	{
		printf("Some error message\n");
		return ;
	}
}
