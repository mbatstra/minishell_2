/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cyuzbas <cyuzbas@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/29 10:26:25 by cyuzbas       #+#    #+#                 */
/*   Updated: 2022/10/18 13:57:58 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	first_child(t_simplecmd *cmds, t_list **env, int fd[2])
{
	int	pid;

	pid = fork();
	if (pid == -1)
		exit(-1);
	else if (pid == 0)
	{
		protect_close(fd[0]);
		protect_dup2(fd[1], STDOUT_FILENO);
		protect_close(fd[1]);
		choose_execute(cmds, env);
		exit(0);
	}
}

void	middle_child(t_simplecmd *cmds, t_list **env, int fd[2], int fd_end)
{
	int		pid;

	pid = fork();
	if (pid == -1)
		exit(-1);
	else if (pid == 0)
	{
		protect_dup2(fd[1], STDOUT_FILENO);
		protect_dup2(fd_end, STDIN_FILENO);
		protect_close(fd[0]);
		protect_close(fd[1]);
		protect_close(fd_end);
		choose_execute(cmds, env);
		exit(0);
	}
}

void	last_child(t_simplecmd *cmds, t_list **env, int fd[2], int *lastid)
{
	*lastid = fork();
	if (*lastid == -1)
		exit(-1);
	else if (*lastid == 0)
	{
		protect_dup2(fd[0], STDIN_FILENO);
		protect_close(fd[0]);
		choose_execute(cmds, env);
		exit(0);
	}
}

void	one_command(t_simplecmd *cmds, t_list **env, int *lastpid)
{
	t_list	*arg;

	arg = *(cmds->arg);
	*lastpid = fork();
	if (*lastpid == -1)
		exit(-1);
	if (*lastpid == 0)
	{
		choose_execute(cmds, env);
		exit(0);
	}
	else if (ft_str_cmp((char *)(arg->content), "cd")
			|| (ft_str_cmp((char *)(arg->content), "export")
				&& arg->next->content)
			|| ft_str_cmp((char *)(arg->content), "unset"))
		execute_builtin(cmds, env, 0);
}

void	fork_start(int i, t_simplecmd **cmds, t_list **env, t_fd *fd)
{
	if (i == 0 && !cmds[i + 1])
		one_command(cmds[i], env, fd->last_pid);
	else if (i == 0)
		first_child(cmds[i], env, fd->fdpipe);
	else if (!cmds[i + 1])
		last_child(cmds[i], env, fd->fdpipe, fd->last_pid);
	else
		middle_child(cmds[i], env, fd->fdpipe, fd->fd_end);
}