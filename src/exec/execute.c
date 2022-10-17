/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cyuzbas <cyuzbas@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/29 10:26:25 by cyuzbas       #+#    #+#                 */
/*   Updated: 2022/10/17 21:10:06 by cicekyuzbas   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/exec.h"
#include <stdbool.h>

// void	free_parse_list_element(t_simplecmd **cmds)
// {
// 	size_t		i;

// 	i = 0;
// 	while (((t_pipeline *)(pipeline))->command[i] != NULL)
// 	{
// 		free(((t_pipeline *)(pipeline))->command[i]);
// 		i++;
// 	}
// 	free(((t_pipeline *)(pipeline))->command);
// 	ft_lstclear(&((t_pipeline *)(pipeline))->redirection,
// 		free_redirection_element);
// 	free((t_pipeline *)(pipeline));
// }

// void	clear_data(t_simplecmd **cmds)
// {
// 	int i;
	
// 	i = 0;
// 	while (cmds[i])
// 	{
// 		ft_lstclear(**cmds, free_parse_list_element);
// 		i++;
// 	}
// 	// ft_lstclear(*cmds, free_parse_list_element);
// }

void	print_error(char *command, char *text)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	if (text == NULL)
		ft_putstr_fd(strerror(errno), 2);
	else
		ft_putstr_fd(text, 2);
	ft_putstr_fd("\n", 2);
}

int	wait_children(int last_process_pid)
{
	int	pid;
	int	last_process_exit_status;
	int	status;

	pid = 1;
	last_process_exit_status = 0;
	while (pid > 0)
	{
		pid = wait(&status);
		if (pid == last_process_pid)
		{
			if (WIFEXITED(status))
				last_process_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_process_exit_status = WTERMSIG(status) + 128;
		}
	}
	return (last_process_exit_status);
}

void	choose_execute(t_simplecmd *cmds, t_list **env)
{
	t_list	*in;
	t_list	*out;
	
	in = *(cmds->in);
	out = *(cmds->out);
	// printf("in->%s\n",((t_token *)in->content)->value);
	// printf("out->%s\n",((t_token *)out->content)->value);
	if (in)
		set_infile(cmds); 
	if (out)
		set_outfile(cmds);
	if (is_builtin(cmds))
		execute_builtin(cmds, env, 0);
	else
		ft_execve(cmds, env);
}

void	ft_fork(t_simplecmd **cmds, t_list **env, int *last_pid)
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
		// g_interactive = 0;
		fork_start(idx, cmds, env, &fd);
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

int execute(t_simplecmd **cmds, t_list **envp, int exit_code)
{
	int	last_pid;

	if (!heredoc(cmds))
		return (-1);
	if(builtin_and_redirection(cmds) || !is_builtin(*cmds))
	{
		last_pid = 0;
		ft_fork(cmds, envp, &last_pid);
		exit_code = wait_children(last_pid);
		// g_interactive = 1;
	}
	else if(is_builtin(*cmds))
		exit_code = execute_builtin(*cmds, envp, exit_code);
	// printf("%d\n", exit_code);
	// clear_data(&cmds);
	return (exit_code);
}