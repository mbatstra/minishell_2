/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cyuzbas <cyuzbas@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/29 10:26:25 by cyuzbas       #+#    #+#                 */
/*   Updated: 2022/10/17 20:58:55 by cicekyuzbas   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/exec.h"

int	ft_str_cmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (FALSE);
	while (s1[i])
	{
		if (!s2[i])
			return (FALSE);
		if (s1[i] != s2[i])
			return (FALSE);
		i++;
	}
	if (s2[i])
		return (FALSE);
	return (TRUE);
}

int	is_builtin(t_simplecmd *cmds)
{
	t_list	*arg;
	bool	is_builtin;

	arg = *(cmds->arg);
	is_builtin = FALSE;
	if (ft_str_cmp((char *)(arg->content), "cd"))
		is_builtin = TRUE;
	else if (ft_str_cmp((char *)(arg->content), "pwd"))
		is_builtin = TRUE;
	else if (ft_str_cmp((char *)(arg->content), "exit"))
		is_builtin = TRUE;
	else if (ft_str_cmp((char *)(arg->content), "echo"))
		is_builtin = TRUE;
	else if (ft_str_cmp((char *)(arg->content), "env"))
		is_builtin = TRUE;
	else if (ft_str_cmp((char *)(arg->content), "export"))
		is_builtin = TRUE;
	else if (ft_str_cmp((char *)(arg->content), "unset"))
		is_builtin = TRUE;
	return (is_builtin);
}

int	execute_builtin(t_simplecmd *cmds, t_list **env, int exit_code)
{
	t_list	*arg;
	int		i;
	
	arg = *(cmds->arg);
	// i = (int *)(arg->next->next->content);
	i=1;
	// printf("command = %s\n", (char *)(arg->content));
	if (ft_str_cmp((char *)(arg->content), "cd"))
		exit_code = builtin_cd((char *)(arg->next->content), env);
	else if (ft_str_cmp((char *)(arg->content), "pwd"))
		exit_code = builtin_pwd();
	else if (ft_str_cmp((char *)(arg->content), "exit"))
		builtin_exit(); //cmds, &exit_code
	else if (ft_str_cmp((char *)(arg->content), "echo"))
		exit_code = builtin_echo((char *)(arg->next->content), i); //flag
	else if (ft_str_cmp((char *)(arg->content), "env"))
		exit_code = builtin_env(*env);
	else if (ft_str_cmp((char *)(arg->content), "export"))
		exit_code = builtin_export(env, (char *)(arg->next->content));
	else if (ft_str_cmp((char *)(arg->content), "unset"))
		exit_code = builtin_unset(env, (char *)(arg->next->content));
	return (exit_code);
}


int	builtin_and_redirection(t_simplecmd **cmds)
{
	t_list	*arg;
	t_list	*in;
	t_list	*out;
	
	arg = *(cmds[0]->arg);
	in = *(cmds[0]->in);
	out = *(cmds[0]->out);
	if ((in || out || arg->next ) && is_builtin(cmds[0]))
			return (1);
	return (0);
}