/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:04:31 by mbatstra          #+#    #+#             */
/*   Updated: 2022/10/05 21:35:03 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "libft.h"

// in parsing context redirections are stored as tokens where
// type is the operator and value the operand/argument

int	parse_append_redir(t_cmd *cmd_table, t_token *redir, int mode)
{
	// if array is uninitialized, create new array where
	// idnex 0 == redir and index 1 == NULL
	// else
	// realloc and append redir
}

static int parse_add_rdr_to_cmd(t_cmd *cmd_table, t_token *token)
{
	if (token->type < RDR_OUT)
		return (parse_append_redir(cmd_table->in, token));
	else if (token->type < PIPE)
		return (parse_append_redir(cmd_table->out, token));
	else
		return (1);
}

// set type of next token equal to current
// add token to in, out or err
int	parse_redir(t_cmd *cmd_table, t_list *tokens)
{
	t_token	*new_tok;
	t_list	*next;
	int		error;

	(void) cmd_table;
	next = tokens->next;
	if (next == NULL || ((t_token *)next->content)->type != WORD)
		return (1);
	new_tok = lexer_token_copy(next->content);
	if (new_tok == NULL)
		return (1);
	new_tok->type = ((t_token *)tokens->content)->type;
	error = parse_add_rdr_to_cmd(cmd_table, new_tok);
	// remove from list
	return (error);
}
