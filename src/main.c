/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:30:39 by mbatstra          #+#    #+#             */
/*   Updated: 2022/09/20 20:29:37 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "libft.h"

void	db_ptlist(t_list **lst)
{
	t_list	*node;

	node = *lst;
	while (node != NULL)
	{
		printf("%s\n", node->content);
		node = node->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*new_env;

	(void) argc;
	(void) argv;
	env_init(envp, &new_env);
	builtin_export(&new_env, "TEST=test");
	builtin_env(new_env);
	printf("\n-----\n");
	builtin_export(&new_env, "TEST=haha=haha");
	builtin_unset(&new_env, "SHELL");
	builtin_env(new_env);
	system("leaks -q minishell");
	return (0);
}
