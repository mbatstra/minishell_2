/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cyuzbas <cyuzbas@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/29 10:26:25 by cyuzbas       #+#    #+#                 */
/*   Updated: 2022/11/04 17:35:52 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/exec.h"

void	exec_pipe(t_simplecmd **cmds, t_list **env, int *last_pid)
{
	t_fd	fd;
	int		idx;

	idx = 0;
	fd.fd_end = -1;
	fd.last_pid = last_pid;
	while (cmds[idx] != NULL)
	{
		if (cmds[idx + 1] != NULL)
			if (pipe(fd.fdpipe) == -1)
				exit(1);
		ft_fork(idx, cmds, env, &fd);
		if (fd.fd_end != -1)
		{
			protect_close(fd.fd_end);
			if (cmds[idx + 1] != NULL)
				fd.fd_end = fd.fdpipe[0];
		}
		else
			fd.fd_end = fd.fdpipe[0];
		idx++;
		if (cmds[idx] != NULL)
			protect_close(fd.fdpipe[1]);
	}
}

void	execute2(t_simplecmd **cmds, t_list **envp)
{
	int		last_pid;
	t_list	*in;
	t_list	*arg;

	arg = *(*cmds)->arg;
	in = *(*cmds)->in;
	last_pid = 0;
	exec_pipe(cmds, envp, &last_pid);
	g_mini.exit_code = wait_children(last_pid);
	if (g_mini.exit_code == 0 && in \
	&& ft_strcmp((char *)(arg->content), "exit") == 0)
		builtin_exit(arg, &g_mini.exit_code);
	else if (g_mini.exit_code != 1 \
	&& ft_strcmp((char *)(arg->content), "exit") == 0)
		exit(g_mini.exit_code);
}

void	execute(t_simplecmd **cmds, t_list **envp)
{
	// int		last_pid;
	// t_list	*in;
	// t_list	*arg;

	// arg = *(*cmds)->arg;
	// in = *(*cmds)->in;
	if (!heredoc(cmds, envp))
	{
		g_mini.exit_code = -1;
		return ;
	}
	if (g_mini.interactive != 0)
	{
		if (builtin_and_redirection(cmds) || !is_builtin(*cmds))
		{
			execute2(cmds, envp);
			// last_pid = 0;
			// exec_pipe(cmds, envp, &last_pid);
			// g_mini.exit_code = wait_children(last_pid);
			// if (g_mini.exit_code == 0 && in \
			// && ft_strcmp((char *)(arg->content), "exit") == 0)
			// 	builtin_exit(arg, &g_mini.exit_code);
			// else if (g_mini.exit_code != 1 \
			// && ft_strcmp((char *)(arg->content), "exit") == 0)
			// 	exit(g_mini.exit_code);
		}
		else
			execute_builtin(*cmds, envp);
	}
}
