/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:53:52 by mbatstra          #+#    #+#             */
/*   Updated: 2022/10/12 22:08:28 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "libft.h"

static int	simplecmd_init(t_cmd *cmd_table, t_list **tokens)
{
	t_list	*node;
	int		numpipes;
	int		i;

	node = *tokens;
	numpipes = 0;
	while (node != NULL)
	{
		if (((t_token *)node->content)->type == PIPE)
			numpipes++;
		node = node->next;
	}
	cmd_table->simplecmds = (t_simplecmd **)malloc((numpipes + 2) * \
											sizeof(t_simplecmd *));
	if (cmd_table->simplecmds == NULL)
		return (1);
	i = 0;
	while (i <= numpipes + 1)
	{
		cmd_table->simplecmds[i] = NULL;
		i++;
	}
	return (0);
}

static int	parse_word_append_init(t_cmd *cmd_table, t_token *token, int i_cmd)
{
	cmd_table->simplecmds[i_cmd] = (t_simplecmd *)malloc(sizeof(t_simplecmd));
	if (cmd_table->simplecmds[i_cmd] == NULL)
		return (1);
	cmd_table->simplecmds[i_cmd]->argc = 1;
	cmd_table->simplecmds[i_cmd]->argv = (char **)malloc(sizeof(char *));
	if (cmd_table->simplecmds[i_cmd]->argv == NULL)
		return (1);
	cmd_table->simplecmds[i_cmd]->argv[0] = ft_strdup(token->value);
	if (cmd_table->simplecmds[i_cmd]->argv[0] == NULL)
		return (1);
	return (0);
}

static char	**parse_app_arr(t_simplecmd *current, t_token *token)
{
	char		**new_argv;
	int			i;

	i = 0;
	new_argv = (char **)malloc((current->argc + 1) * sizeof(char *));
	while (i < current->argc)
	{
		new_argv[i] = ft_strdup(current->argv[i]);
		if (new_argv[i] == NULL)
		{
			parse_clear_arr(new_argv, i);
			return (NULL);
		}
		i++;
	}
	new_argv[i] = ft_strdup(token->value);
	if (new_argv[i] == NULL)
	{
		parse_clear_arr(new_argv, i);
		return (NULL);
	}
	return (new_argv);
}

static int	parse_word_append(t_cmd *cmd_table, t_token *token, int i_cmd)
{
	t_simplecmd	*current;
	char		**new_argv;

	current = cmd_table->simplecmds[i_cmd];
	if (current == NULL)
		return (parse_word_append_init(cmd_table, token, i_cmd));
	new_argv = parse_app_arr(current, token);
	if (new_argv == NULL)
		return (1);
	parse_clear_arr(current->argv, current->argc);
	current->argv = new_argv;
	current->argc++;
	return (0);
}

int	parse_word(t_cmd *cmd_table, t_list **tokens)
{
	t_list	*node;
	int		i_cmd;
	int		error;

	if (tokens == NULL || *tokens == NULL)
		return (1); // not necessarily an error?
	node = *tokens;
	i_cmd = 0;
	error = simplecmd_init(cmd_table, tokens);
	while (node != NULL && !error)
	{
		if (((t_token *)node->content)->type == WORD)
			error = parse_word_append(cmd_table, node->content, i_cmd);
		else if (((t_token *)node->content)->type == PIPE)
			i_cmd++;
		else
			error = 1;
		node = node->next;
	}
	return (error);
}
