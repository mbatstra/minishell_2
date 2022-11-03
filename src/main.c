/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 17:37:17 by mbatstra      #+#    #+#                 */
/*   Updated: 2022/11/03 13:22:05 by cyuzbas       ########   odam.nl         */
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

// void	db_ptcmd(t_simplecmd **cmd_table)
// {
// 	int	i;

// 	i = 0;
// 	while (cmd_table[i] != NULL)
// 	{
// 		t_list	*arg = *(cmd_table[i]->arg);
// 		t_list	*in = *(cmd_table[i]->in);
// 		t_list	*out = *(cmd_table[i]->out);
// 		printf("---\n%d\n---\n", i);
// 		printf("arg: ");
// 		while (arg != NULL)
// 		{
// 			printf("%s\t", (char *)(arg->content));
// 			arg = arg->next;
// 		}
// 		printf("\n");
// 		printf("in: ");
// 		if (in == NULL)
// 			printf("default");
// 		else while (in != NULL)
// 		{
// 			printf("%s\t", ((t_token *)in->content)->value);
// 			in = in->next;
// 		}
// 		printf("\n");
// 		printf("out: ");
// 		if (out == NULL)
// 			printf("default");
// 		else while (out != NULL)
// 		{
// 			printf("%s\t", ((t_token *)out->content)->value);
// 			out = out->next;
// 		}
// 		printf("\n");
// 		i++;
// 	}
// }

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
	int			error;

	(void)argc;
	(void)av;
	g_exit_code = 0;
	signal_suppress_output();
	new_env = NULL;
	env_init(env, &new_env);
	change_shlvl(&new_env);
	signal(SIGQUIT, &catch_quit);
	signal(SIGINT, &catch_int);
	while (1)
	{
		error = 0;
		input = readline("minishell-$ ");
		if (input == NULL)
		{
			printf("exit\n");
			exit(EXIT_FAILURE);
		}
		add_history(input);
		tokens = NULL;
		error = lexer_tokenize(&tokens, input);
		if (!error)
		{
			cmd_table = parse_cmd_init(tokens);
			error = parse_tokens(cmd_table, &tokens, new_env);
			execute(cmd_table, &new_env);
			parse_clear_cmd_table(cmd_table);
		}
		ft_lstclear(&tokens, &lexer_clear_token);
		if (error == 1)
			printf("Allocation failure\n");
		free(input);
	}
	return (0);
}
