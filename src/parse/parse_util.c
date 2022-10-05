/*************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:56:12 by mbatstra          #+#    #+#             */
/*   Updated: 2022/10/05 15:54:11 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "libft.h"

t_cmd	*parse_init_cmd(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->simplecmds = NULL;
	cmd->in = NULL;
	cmd->out = NULL;
	cmd->err = NULL;
	return (cmd);
}

static void	clear_tok_arr(t_token **tok_arr)
{
	int	i;

	if (tok_arr == NULL)
		return ;
	i = 0;
	while (tok_arr[i] != NULL)
	{
		free(tok_arr[i]);
		i++;
	}
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
	clear_tok_arr(cmd->in);
	clear_tok_arr(cmd->out);
	clear_tok_arr(cmd->err);
	free(cmd);
}
