/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cyuzbas <cyuzbas@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/29 10:26:25 by cyuzbas       #+#    #+#                 */
/*   Updated: 2022/11/03 17:20:03 by cyuzbas       ########   odam.nl         */
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

void	execute(t_simplecmd **cmds, t_list **envp)
{
	int		last_pid;
	t_list	*arg;
	t_list	*in;
	t_list	*out;

	arg = *(cmds[0]->arg);
	in = *(cmds[0]->in);
	out = *(cmds[0]->out);
	// if (!arg && !in && !out)
	// 	exit (0);
	// g_mini.interactive = 0;
	if (!heredoc(cmds, envp))
	{
		g_mini.exit_code = -1;
		exit (-1);
	}
	// printf("int=%d exit=%d\n", g_mini.interactive, g_mini.exit_code);
	if (g_mini.interactive != 0)
	{
		if (builtin_and_redirection(cmds) || !is_builtin(*cmds))
		{
			last_pid = 0;
			exec_pipe(cmds, envp, &last_pid);
			g_mini.exit_code = wait_children(last_pid);
		}
		else
			execute_builtin(*cmds, envp);
	}
	
	// if (arg && ft_strcmp(arg->content, "./minishell") == 0)
	// 	{
	// 		signal(SIGINT, SIG_IGN);
	// 		signal(SIGQUIT, SIG_IGN);
	// 	}
}
