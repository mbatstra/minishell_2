/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:41:52 by mbatstra          #+#    #+#             */
/*   Updated: 2022/10/12 21:33:07 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "libft.h"

static int	lexer_quote_isclosed(char *cmd, int start)
{
	int	i;

	i = start + 1;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == cmd[start])
			return (1);
		i++;
	}
	return (0);
}

static void	lexer_tokenize_quote(t_token *token, char *cmd, \
								int *i, t_lexer_flags *flags)
{
	if (cmd[*i] == '"')
	{
		if (flags->is_double_quoted)
			flags->is_double_quoted = 0;
		else if (lexer_quote_isclosed(cmd, *i))
			flags->is_double_quoted = 1;
		flags->last_exit = lexer_value_append(token, "\"", 1);
		*i += 1;
	}
	if (cmd[*i] == '\'')
	{
		if (flags->is_single_quoted)
			flags->is_single_quoted = 0;
		else if (lexer_quote_isclosed(cmd, *i))
			flags->is_single_quoted = 1;
		flags->last_exit = lexer_value_append(token, "'", 1);
		*i += 1;
	}
}

static void	lexer_tokenize_delim(t_token *token, char *cmd, \
								int *i, t_lexer_flags *flags)
{
	if (lexer_is_operator_char(cmd[*i]) || ft_iswspace(cmd[*i]))
	{
		if (flags->is_double_quoted || flags->is_single_quoted)
		{
			flags->last_exit = lexer_value_append(token, cmd + *i, 1);
			*i += 1;
		}
		else
		{
			while (ft_iswspace(cmd[*i]))
				*i += 1;
			flags->is_delim = 1;
		}
	}
}

static void	lexer_tokenize_char(t_token *token, char *cmd, \
								int *i, t_lexer_flags *flags)
{
	if (!flags->is_single_quoted && cmd[*i] == '$')
		token->expand = 1;
	if (!flags->is_single_quoted && !flags->is_double_quoted && cmd[*i] == '~')
		token->expand = 1;
	flags->last_exit = lexer_value_append(token, cmd + *i, 1);
	*i += 1;
}

void	lexer_tokenize_word(t_token *token, char *cmd, \
							int *i, t_lexer_flags *flags)
{
	while (cmd[*i] != '\0')
	{
		lexer_tokenize_quote(token, cmd, i, flags);
		lexer_tokenize_delim(token, cmd, i, flags);
		if (flags->is_delim)
			return ;
		lexer_tokenize_char(token, cmd, i, flags);
		if (cmd[*i] == '\0')
			flags->is_delim = 1;
	}
}
