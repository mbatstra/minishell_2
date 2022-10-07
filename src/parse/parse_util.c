/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:56:12 by mbatstra          #+#    #+#             */
/*   Updated: 2022/10/07 14:04:09 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "libft.h"

void	parse_init_cmd(t_cmd *cmd)
{
	cmd->simplecmds = NULL;
	cmd->in = NULL;
	cmd->out = NULL;
	cmd->err = NULL;
}

void	parse_clear_tok_arr(t_token **tok_arr)
{
	int	i;

	if (tok_arr == NULL)
		return ;
	i = 0;
	while (tok_arr[i] != NULL)
	{
		lexer_clear_token(tok_arr[i]);
		i++;
	}
	free(tok_arr[i]);
	free(tok_arr);
}

void	parse_clear_cmd(t_cmd *cmd)
{
	int	i_cmd;
	int	i_tok;

	i_cmd = 0;
	i_tok = 0;
	if (cmd->simplecmds != NULL)
	{
		while (cmd->simplecmds[i_cmd] != NULL)
		{
			free(cmd->simplecmds[i_cmd]);
			i_cmd++;
		}
	}
	parse_clear_tok_arr(cmd->in);
	parse_clear_tok_arr(cmd->out);
	parse_clear_tok_arr(cmd->err);
}
