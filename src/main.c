/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:30:39 by mbatstra          #+#    #+#             */
/*   Updated: 2022/10/07 15:28:27 by mbatstra         ###   ########.fr       */
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
		parse_init_cmd(&cmd_table);
		parse_tokens(&cmd_table, &tokens);
		printf("%s, %d\n", cmd_table.out[0]->value, cmd_table.out[0]->type);
		printf("%s, %d\n", cmd_table.out[1]->value, cmd_table.out[1]->type);
		printf("%p\n", cmd_table.out[2]);
		db_ptlist(&tokens);
		parse_clear_cmd(&cmd_table);
		ft_lstclear(&tokens, &lexer_clear_token);
		free(input);
	}
	return (0);
}
