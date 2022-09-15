/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:30:39 by mbatstra          #+#    #+#             */
/*   Updated: 2022/09/15 18:38:03 by mbatstra         ###   ########.fr       */
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
	printf("%s\n", env_getval(new_env, "SHELL"));
	printf("%s\n", env_getval(new_env, "LOGNAME"));
	env_setval(new_env, "LOGNAME", "martijn");
	printf("%s\n", env_getval(new_env, "LOGNAME"));
	// system("leaks minishell");
	// builtin_cd("/Users/mbatstra/", envp);
	// builtin_pwd();
	// builtin_env(envp);
	return (0);
}
