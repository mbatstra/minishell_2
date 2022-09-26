/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:22:08 by mbatstra          #+#    #+#             */
/*   Updated: 2022/09/26 18:27:31 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "libft.h"

static t_token	*init_token(void)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->value = NULL;
	return (token);
}

static void	init_flags(t_lexer_flags *flags)
{
	flags->is_double_quoted = 0;
	flags->is_double_quoted = 0;
	flags->is_delim = 0;
	flags->last_exit = 0;
}

static void	delimit(t_list **tokens, t_token **token, t_lexer_flags *flags)
{
	if (flags->last_exit)
		// deal with it
	if (flags->is_delim)
	{
		// set type
		ft_lstadd_back(tokens, ft_lstnew(*token));
		*token = init_token();
		init_flags(flags);
	}
}

int	lexer_is_operator_char(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

int	lexer_value_append(t_token *token, char value)
{
	char	*new;

	new = (char *)ft_calloc(ft_strlen(token->value) + 2, sizeof(char));
	if (new == NULL)
		return (1);
	ft_strlcpy(new, token->value, ft_strlen(token->value) + 1);
	free(token->value);
	new[ft_strlen(token->value) + 1] = value;
	token->value = new;
	return (0);
}

int	lexer_tokenize(t_list **tokens, char *cmd_line)
{
	t_lexer_flags	flags;
	t_token			*token;
	int				i;

	i = 0;
	token = init_token();
	init_flags(&flags);
	while (cmd_line[i] != '\0')
	{
		if (lexer_is_operator_char(cmd_line[i]))
			lexer_tokenize_operator(token, cmd_line, &i, &flags);
		else
			lexer_tokenize_word(token, cmd_line, &i, &flags);
		delimit(tokens, &token, &flags);
	}
	return (0);
}
