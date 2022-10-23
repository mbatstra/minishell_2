/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cyuzbas <cyuzbas@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/29 10:26:25 by cyuzbas       #+#    #+#                 */
/*   Updated: 2022/10/20 14:38:11 by cicekyuzbas   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/exec.h"

// int	ft_str_cmp(char *s1, char *s2)
// {
// 	int	i;

// 	i = 0;
// 	if (!s1 || !s2)
// 		return (FALSE);
// 	while (s1[i])
// 	{
// 		if (!s2[i])
// 			return (FALSE);
// 		if (s1[i] != s2[i])
// 			return (FALSE);
// 		i++;
// 	}
// 	if (s2[i])
// 		return (FALSE);
// 	return (TRUE);
// }

// int	ft_strcmp(const char *s1, const char *s2)
// {
// 	while (*s1 != '\0' || *s2 != '\0')
// 	{
// 		if (*s1 != *s2)
// 			return ((unsigned char)*s1 - (unsigned char)*s2);
// 		s1++;
// 		s2++;
// 	}
// 	return (0);
// }

int	is_builtin(t_simplecmd *cmds)
{
	t_list	*arg;
	int		is_builtin;

	arg = *(cmds->arg);
	is_builtin = FALSE;
	if (arg != NULL)
	{
		if (ft_strcmp((char *)(arg->content), "cd") == 0)
			is_builtin = TRUE;
		else if (ft_strcmp((char *)(arg->content), "pwd") == 0)
			is_builtin = TRUE;
		else if (ft_strcmp((char *)(arg->content), "exit") == 0)
			is_builtin = TRUE;
		else if (ft_strcmp((char *)(arg->content), "echo") == 0)
			is_builtin = TRUE;
		else if (ft_strcmp((char *)(arg->content), "env") == 0)
			is_builtin = TRUE;
		else if (ft_strcmp((char *)(arg->content), "export") == 0)
			is_builtin = TRUE;
		else if (ft_strcmp((char *)(arg->content), "unset") == 0)
			is_builtin = TRUE;
	}
	return (is_builtin);
}

int	execute_builtin(t_simplecmd *cmds, t_list **env, int exit_code)
{
	t_list	*arg;
	char	*command_next;

	arg = *(cmds->arg);
	if (!arg->next)
		command_next = NULL;
	else
		command_next = (char *)(arg->next->content);
	if (ft_strcmp((char *)(arg->content), "cd") == 0)
		exit_code = builtin_cd(command_next, env);
	else if (ft_strcmp((char *)(arg->content), "pwd") == 0)
		exit_code = builtin_pwd();
	else if (ft_strcmp((char *)(arg->content), "exit") == 0)
		builtin_exit(arg, &exit_code);
	else if (ft_strcmp((char *)(arg->content), "echo") == 0)
		exit_code = builtin_echo(arg);
	else if (ft_strcmp((char *)(arg->content), "env") == 0)
		exit_code = builtin_env(*env);
	else if (ft_strcmp((char *)(arg->content), "export") == 0)
		exit_code = builtin_export(env, arg);
	else if (ft_strcmp((char *)(arg->content), "unset") == 0)
		exit_code = builtin_unset(env, arg);
	return (exit_code);
}

int	builtin_and_redirection(t_simplecmd **cmds)
{
	t_list	*in;
	t_list	*out;

	in = *(cmds[0]->in);
	out = *(cmds[0]->out);
	if ((in || out || cmds[1]) && is_builtin(cmds[0]))
		return (1);
	return (0);
}