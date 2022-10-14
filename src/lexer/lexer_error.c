/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 21:06:45 by mbatstra          #+#    #+#             */
/*   Updated: 2022/10/14 18:03:12 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "libft.h"

// errors:
// redirs with invalid operand
// pipes with invalid operands
// what else?

static int	lexer_error_redir(t_list *tokens)
{
	while (tokens != NULL)
	{
		if (((t_token *)tokens->content)->type < PIPE)
		{
			if (tokens->next == NULL)
			{
				printf("syntax error near unexpected token `newline'\n"); 
				return (2);
			}
			else if (((t_token *)tokens->next->content)->type != WORD)
			{
				printf("syntax error near unexpected token `%s'\n", \
								((t_token *)tokens->next->content)->value);
				return (2);
			}
		}
		tokens = tokens->next;
	}
	return (0);
}

static int	lexer_error_pipe(t_list *tokens)
{
	if (tokens == NULL)
		return (0);
	if (((t_token *)tokens->content)->type == PIPE)
	{
		printf("syntax error near unexpected token `|'\n");
		return (2);
	}
	while (tokens->next != NULL)
	{
		if (((t_token *)tokens->next->content)->type == PIPE)
		{
			if (((t_token *)tokens->content)->type != WORD || \
				tokens->next->next == NULL)
			{
				printf("syntax error near unexpected token `newline'\n"); 
				return (2);
			}
			else if (((t_token *)tokens->content)->type != WORD || \
					((t_token *)tokens->next->next->content)->type != WORD)
			{
				printf("syntax error near unexpected token `%s'\n", \
								((t_token *)tokens->next->content)->value);
				return (2);
			}
		}
		tokens = tokens->next;
	}
	return (0);
}

int	lexer_error(t_list *tokens)
{
	int	error;

	error = lexer_error_redir(tokens);
	if (!error)
		error = lexer_error_pipe(tokens);
	return (error);
}
