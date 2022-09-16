/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:30:39 by mbatstra          #+#    #+#             */
/*   Updated: 2022/09/16 14:04:19 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	**new_env;

	(void) argc;
	(void) argv;
	new_env = env_init(envp);
	printf("-----\n");
	builtin_pwd();
	printf("-----\n");
	builtin_env(new_env);
	builtin_cd(NULL, new_env);
	printf("-----\n");
	builtin_pwd();
	printf("-----\n");
	builtin_env(new_env);
	// system("leaks minishell");
	return (0);
}
