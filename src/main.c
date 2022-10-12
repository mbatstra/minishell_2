/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:30:39 by mbatstra          #+#    #+#             */
/*   Updated: 2022/10/12 21:24:06 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include "libft.h"

void	db_ptlist(t_list **lst)
{
	t_list	*node;

	node = *lst;
	while (node != NULL)
	{
		printf("%s: type: %d, exp: %d\n", \
			((t_token *)node->content)->value, \
			((t_token *)node->content)->type, \
			((t_token *)node->content)->expand);
		node = node->next;
	}
}

void	db_pttable(t_cmd *cmd)
{
	int	i_cmd;
	int	i_arg;
	int	i_tok;

	i_cmd = 0;
	i_arg = 0;
	i_tok = 0;
	while (cmd->simplecmds[i_cmd] != NULL)
	{
		printf("%d: ", i_cmd);
		while (i_arg < cmd->simplecmds[i_cmd]->argc)
		{
			printf("%s\t", cmd->simplecmds[i_cmd]->argv[i_arg]);
			i_arg++;
		}
		i_arg = 0;
		i_cmd++;
		printf("\n");
	}
	printf("---\n");
	printf("in: ");
	if (cmd->in == NULL)
		printf("default");
	else while (cmd->in[i_tok] != NULL)
	{
		printf("%s\t", cmd->in[i_tok]->value);
		i_tok++;
	}
	printf("\n");

	i_tok = 0;
	printf("out: ");	
	if (cmd->out == NULL)
		printf("default");
	else while (cmd->out[i_tok] != NULL)
	{
		printf("%s\t", cmd->out[i_tok]->value);
		i_tok++;
	}
	printf("\n");
}

int	main(void)
{
	char	*input;
	t_list	*tokens;
	t_cmd	cmd_table;

	while (1)
	{
		input = readline("minishell-$ ");
		if (input == NULL)
			printf("error\n");
		add_history(input);
		tokens = NULL;
		lexer_tokenize(&tokens, input);
		db_ptlist(&tokens);
		parse_init_cmd(&cmd_table);
		parse_tokens(&cmd_table, &tokens);
		db_pttable(&cmd_table);
		parse_clear_cmd(&cmd_table);
		ft_lstclear(&tokens, &lexer_clear_token);
		free(input);
	}
	return (0);
}
