/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:04:31 by mbatstra          #+#    #+#             */
/*   Updated: 2022/10/07 15:17:37 by mbatstra         ###   ########.fr       */
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

int	parse_append_redir_in(t_cmd *cmd_table, t_token *redir)
{
	t_token	**new_arr;
	int		i;

	i = 0;
	while (cmd_table->in[i] != NULL)
		i++;
	new_arr = (t_token **)malloc((i + 2) * sizeof(t_token *));
	if (new_arr == NULL)
		return (1);
	i = 0;
	while (cmd_table->in[i] != NULL)
	{
		new_arr[i] = lexer_token_copy(cmd_table->in[i]);
		if (new_arr[i] == NULL)
		{
			parse_clear_tok_arr(new_arr);
			return (1);
		}
		i++;
	}
	new_arr[i] = redir;
	new_arr[i + 1] = NULL;
	parse_clear_tok_arr(cmd_table->in);
	cmd_table->in = new_arr;
	return (0);
}

int	parse_append_redir_out(t_cmd *cmd_table, t_token *redir)
{
	t_token	**new_arr;
	int		i;

	i = 0;
	while (cmd_table->out[i] != NULL)
		i++;
	new_arr = (t_token **)malloc((i + 2) * sizeof(t_token *));
	if (new_arr == NULL)
		return (1);
	i = 0;
	while (cmd_table->out[i] != NULL)
	{
		new_arr[i] = lexer_token_copy(cmd_table->out[i]);
		if (new_arr[i] == NULL)
		{
			parse_clear_tok_arr(new_arr);
			return (1);
		}
		i++;
	}
	new_arr[i] = redir;
	new_arr[i + 1] = NULL;
	parse_clear_tok_arr(cmd_table->out);
	cmd_table->out = new_arr;
	return (0);
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
		return (parse_append_redir_in(cmd_table, token));
	}
	else if (token->type < PIPE)
	{
		if (cmd_table->out == NULL)
		{
			cmd_table->out = parse_arr_init(token);
			if (cmd_table->out == NULL)
				return (1);
			return (0);
		}
		return (parse_append_redir_out(cmd_table, token));
	}
	else
		return (1);
}

// set type of next token equal to current
// add token to in, out or err
int	parse_redir(t_cmd *cmd_table, t_list *tok)
{
	t_token	*new_tok;
	t_list	*next;
	int		error;

	next = tok->next;
	// maybe better to move this error checking to lexer?
	if (next == NULL || ((t_token *)next->content)->type != WORD)
		return (1);
	new_tok = lexer_token_copy(next->content);
	if (new_tok == NULL)
		return (1);
	new_tok->type = ((t_token *)tok->content)->type;
	error = parse_add_rdr_to_cmd(cmd_table, new_tok);
	return (error);
}
