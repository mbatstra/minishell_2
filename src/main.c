/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 17:37:17 by mbatstra      #+#    #+#                 */
/*   Updated: 2022/11/04 11:20:10 by mbatstra      ########   odam.nl         */
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

t_mini	g_mini;

void	db_ptlist(t_list **lst)
{
	t_list	*node;

	node = *lst;
	while (node != NULL)
	{
		printf("%s: type: %d\n", \
			((t_token *)node->content)->value, \
			((t_token *)node->content)->type);
		node = node->next;
	}
}

void	db_ptcmd(t_simplecmd **cmd_table)
{
	int	i;

	i = 0;
	while (cmd_table[i] != NULL)
	{
		t_list	*arg = *(cmd_table[i]->arg);
		t_list	*in = *(cmd_table[i]->in);
		t_list	*out = *(cmd_table[i]->out);
		printf("---\n%d\n---\n", i);
		printf("arg: ");
		while (arg != NULL)
		{
			printf("%s\t", (char *)(arg->content));
			arg = arg->next;
		}
		printf("\n");
		printf("in: ");
		if (in == NULL)
			printf("default");
		else while (in != NULL)
		{
			printf("%s\t", ((t_token *)in->content)->value);
			in = in->next;
		}
		printf("\n");
		printf("out: ");
		if (out == NULL)
			printf("default");
		else while (out != NULL)
		{
			printf("%s\t", ((t_token *)out->content)->value);
			out = out->next;
		}
		printf("\n");
		i++;
	}
}

// void	check_leaks(void)
// {
// 	system("leaks minishell");
// }

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

int	main(int argc, char **av, char **env)
{
	t_simplecmd	**cmd_table;
	t_list		*tokens;
	t_list		*new_env;
	char		*input;

	(void)argc;
	(void)av;
	g_mini.exit_code = 0;
	signal_suppress_output();
	new_env = NULL;
	env_init(env, &new_env);
	change_shlvl(&new_env);
	signal(SIGQUIT, &catch_quit);
	signal(SIGINT, &catch_int);
	g_mini.interactive = 1;
	while (1)
	{
		signal(SIGQUIT, &catch_quit);
		signal(SIGINT, &catch_int);
		input = readline("minishell-$ ");
		if (input == NULL)
		{
			printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		add_history(input);
		tokens = NULL;
		if (lexer_tokenize(&tokens, input))
			g_mini.exit_code = 258;
		else
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
	return (0);
}
