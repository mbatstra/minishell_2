/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:04:31 by mbatstra          #+#    #+#             */
/*   Updated: 2022/10/11 19:04:25 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "libft.h"

// in parsing context redirections are stored as tokens where
// type is the operator and value the operand/argument

static t_token	**parse_arr_init(t_token *content)
{
	t_token	**arr;

	arr = (t_token **)malloc(2 * sizeof(t_token *));
	if (arr == NULL)
		return (NULL);
	arr[0] = content;
	arr[1] = NULL;
	return (arr);
}

static int	parse_add_rdr_to_cmd(t_cmd *cmd_table, t_token *token)
{
	if (token->type < RDR_OUT)
	{
		if (cmd_table->in == NULL)
		{
			cmd_table->in = parse_arr_init(token);
			if (cmd_table->in == NULL)
				return (1);
			return (0);
		}
		cmd_table->in = parse_append_arr(cmd_table->in, token);
		if (cmd_table->in == NULL)
			return (1);
		return (0);
	}
	if (cmd_table->out == NULL)
	{
		cmd_table->out = parse_arr_init(token);
		if (cmd_table->out == NULL)
			return (1);
		return (0);
	}
	cmd_table->out = parse_append_arr(cmd_table->out, token);
	if (cmd_table->out == NULL)
		return (1);
	return (0);
}

int	parse_redir(t_cmd *cmd_table, t_list **tokens)
{	
	t_token	*new_tok;
	t_list	*current;
	t_list	*skip;
	int		error;

	current = *tokens;
	error = 0;
	while (current != NULL && current->next != NULL && !error)
	{
		if (((t_token *)current->content)->type < PIPE)
		{
			new_tok = lexer_token_copy(current->next->content);
			if (new_tok == NULL)
				return (1);
			new_tok->type = ((t_token *)current->content)->type;
			error = parse_add_rdr_to_cmd(cmd_table, new_tok);
			skip = current->next->next;
			ft_lst_delnode(tokens, current, &lexer_clear_token);
			ft_lst_delnode(tokens, current->next, &lexer_clear_token);
			current = skip;
		}
		else
			current = current->next;
	}
	return (error);
}
