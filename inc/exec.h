#ifndef EXEC_H
# define EXEC_H
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cyuzbas <cyuzbas@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/29 10:26:21 by cyuzbas       #+#    #+#                 */
/*   Updated: 2022/10/09 13:47:41 by cicekyuzbas   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>

#include "minishell.h"

# define TRUE 1
# define FALSE 0

typedef struct s_fd
{
	int			fdpipe[2];
	int			fd_end;
	int			*last_pid;
}				t_fd;

char	**envp_array(t_list *env_lst);

int		execute(t_simplecmd **cmds,t_list **envp, int exit_code);
int		wait_children(int last_process_pid);
void	print_error(char *command, char *text);

void	ft_execve(t_simplecmd *simplecmd, t_list **envp);

int		heredoc(t_simplecmd **cmds);
void	set_infile(t_simplecmd *cmds);
void	set_outfile(t_simplecmd *cmds);

int		builtin_and_redirection(t_simplecmd **cmds);
int		execute_builtin(t_simplecmd *cmds, t_list **env, int exit_code);
int		is_builtin(t_simplecmd *cmds);
void	choose_execute(t_simplecmd *cmds, t_list **env);
int		ft_str_cmp(char *s1, char *s2);

void	fork_start(int i, t_simplecmd **cmds, t_list **env, t_fd *fd);
void	one_command(t_simplecmd *cmds, t_list **env, int *lastpid);
void	first_child(t_simplecmd *cmds, t_list **env, int fd[2]);
void	middle_child(t_simplecmd *cmds, t_list **env, int fd[2], int fd_end);
void	last_child(t_simplecmd *cmds, t_list **env, int fd[2], int *lastid);

char	*protect_itoa(int i);
char	*strdup_protect(char *s1);
char	*join_protect(char *s1, char *s2);
void	protect_close(int id);
void	protect_dup2(int fd, int i);




#endif