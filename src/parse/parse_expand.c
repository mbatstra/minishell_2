/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:20:25 by mbatstra          #+#    #+#             */
/*   Updated: 2022/10/26 15:51:46 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "minishell.h"
#include "libft.h"

static char	*has_expansion(char *str)
{
	int	dquote;
	int	squote;

	dquote = 0;
	squote = 0;
	while (*str != '\0')
	{
		if (*str == '\'' && squote)
			squote = 0;
		else if (*str == '\'' && !dquote && !squote && ft_strchr(str + 1, '\''))
			squote = 1;
		else if (*str == '"' && dquote)
			dquote = 0;
		else if (*str == '"' && !squote && !dquote && ft_strchr(str + 1, '"'))
			dquote = 1;
		else if (*str == '$' && !squote)
			return (str);
		str++;
	}
	return (NULL);
}

static int	count_quotes(char *str)
{
	int	numq;

	numq = 0;
	while (*str != '\0')
	{
		if ((*str == '"' || *str == '\'') && ft_strchr(str + 1, *str))
		{
			numq += 2;
			str = ft_strchr(str + 1, *str) + 1;
		}
		else
			str++;
	}
	return (numq);
}

static char	*rm_quotes(char *str)
{
	char	*new_str;
	char	lastq;
	int		i;
	int		offset;

	lastq = 0;
	i = 0;
	offset = 0;
	new_str = ft_calloc(ft_strlen(str) - count_quotes(str) + 1, sizeof(char));
	while (str[i] != '\0' && new_str != NULL)
	{
		if ((str[i] == '"' || str[i] == '\'') && \
			(lastq == '\0' || lastq == str[i]))
		{
			if (lastq == str[i])
				lastq = '\0';
			else
				lastq = str[i];
			i++;
			offset++;
		}
		new_str[i - offset] = str[i];
		i++;
	}
	return (new_str);
}

char	*parse_expand_env(char *old_val, t_list *envp)
{
	char	*dllr;
	char	*new_val;
	char	*new_sub;
	int		old_sublen;

	old_sublen = 1;
	dllr = has_expansion(old_val);
	if (dllr == NULL)
		return (old_val);
	while (ft_isalnum(dllr[old_sublen]))
		old_sublen++;
	new_sub = env_getval(envp, dllr + 1, old_sublen - 1);
	new_val = ft_replsubstr(old_val, new_sub, dllr, old_sublen);
	if (new_val == NULL)
		return (NULL);
	return (parse_expand_env(new_val, envp));
}

int	parse_expand(t_list *tokens, t_list *envp)
{
	t_token	*tok;
	char	*new_val;

	while (tokens != NULL)
	{
		tok = ((t_token *)tokens->content);
		if (tok->type == WORD)
		{
			new_val = parse_expand_env(tok->value, envp);
			if (new_val == NULL)
				return (1);
			if (new_val != tok->value)
			{
				free(tok->value);
				tok->value = new_val;
			}
			new_val = rm_quotes(tok->value);
			if (new_val == NULL)
				return (1);
			free(tok->value);
			tok->value = new_val;
		}
		tokens = tokens->next;
	}
	return (0);
}
