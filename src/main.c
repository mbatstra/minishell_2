/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 17:37:17 by mbatstra      #+#    #+#                 */
/*   Updated: 2022/11/04 13:35:55 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "minishell.h"
#include "libft.h"
#include "exec.h"

static void	change_shlvl(t_list **envp)
{
	int		shlvl;
	char	*level;
	char	*minipwd;

	shlvl = ft_atoi(env_getval(*envp, "SHLVL", 5));
	shlvl += 1;
	level = protect_itoa(shlvl);
	env_setval(envp, "SHLVL", level);
	minipwd = env_getval(*envp, "PWD", 3);
	minipwd = ft_strjoin(minipwd, "/minishell");
	env_setval(envp, "SHELL", minipwd);
	free(level);
	free(minipwd);
}

static void	ft_exit(void)
{
	printf("exit\n");
	exit(g_mini.exit_code);
}

static void	minishell(t_list *new_env)
{
	t_simplecmd	**cmd_table;
	t_list		*tokens;
	char		*input;

	signal(SIGINT, &catch_int);
	input = readline("minishell-$ ");
	if (input == NULL)
		ft_exit();
	add_history(input);
	tokens = NULL;
	if (lexer_tokenize(&tokens, input))
		g_mini.exit_code = 258;
	else if (ft_strlen(input))
	{
		cmd_table = parse_cmd_init(tokens);
		g_mini.exit_code = parse_tokens(cmd_table, &tokens, new_env);
		execute(cmd_table, &new_env);
		parse_clear_cmd_table(cmd_table);
	}
	ft_lstclear(&tokens, &lexer_clear_token);
	if (g_mini.exit_code == 12)
		ft_putendl_fd("Allocation failure", 2);
	free(input);
	g_mini.interactive = 1;
}

int	main(int argc, char **argv, char **env)
{
	t_simplecmd	**cmd_table;
	t_list		*tokens;
	t_list		*new_env;
	char		*input;

	(void)argc;
	(void)argv;
	g_mini.exit_code = 0;
	signal_suppress_output();
	new_env = NULL;
	env_init(env, &new_env);
	change_shlvl(&new_env);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &catch_int);
	g_mini.interactive = 1;
	while (1)
		minishell(new_env);
	return (0);
}
