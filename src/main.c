/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:30:39 by mbatstra          #+#    #+#             */
/*   Updated: 2022/09/27 21:02:49 by mbatstra         ###   ########.fr       */
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
		printf("%s\n", ((t_token *)node->content)->value);
		node = node->next;
	}
}

int	main(void)
{
	char	*input;
	t_list	*tokens;

	tokens = NULL;
	lexer_tokenize(&tokens, "ls -la > my_file");
	db_ptlist(&tokens);
	ft_lstclear(&tokens, &lexer_clear_token);
	tokens = NULL;
	system("leaks -q minishell");
	// while (1)
	// {
	// 	input = readline("minishell-$ ");
	// 	if (input == NULL)
	// 		printf("error\n");
	// 	add_history(input);
	// 	printf("%s\n", input);
	// 	// lex and parse
	// 	free(input);
	// }
	return (0);
}
