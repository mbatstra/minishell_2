/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cyuzbas <cyuzbas@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/29 10:26:25 by cyuzbas       #+#    #+#                 */
/*   Updated: 2022/10/17 21:08:27 by cicekyuzbas   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	set_heredoc(t_simplecmd **cmds)
{
	size_t	i;
	size_t	j;
	t_token	*rdr;
	t_list	*in;

	i = 0;
	j = 0;
	while (cmds[j])
	{
		in = *(cmds[j]->in);
		while (in)
		{
			rdr = in->content;
			if (rdr->type == HEREDOC)
			{
				free(rdr->value);
				rdr->value = join_protect("/tmp/heredoc_",
						protect_itoa(i));
				i++;
			}
			in = in->next;
		}
		j++;
	}
}


static void	write_to_heredoc(t_list *lst, t_token *redirection)
{
	int		id;
	char	new_line;

	new_line = '\n';
	id = open(redirection->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (id < 0)
	{
		print_error(redirection->value, NULL);
		exit(1);
	}
	while (lst)
	{
		write(id, lst->content, ft_strlen(lst->content));
		write(id, &new_line, sizeof(new_line));
		lst = lst->next;
	}
	close(id);
	ft_lstclear(&lst, free);
}

static void	handle_heredoc(t_token *redirection, char *eof)
{
	t_list	*here_doc_input_list;
	char	*read_txt;

	here_doc_input_list = NULL;
	while (1)
	{
		read_txt = readline("> ");
		if (read_txt == NULL)
			break ;
		else if (ft_str_cmp(eof, read_txt))
			break ;
		ft_lstadd_back(&here_doc_input_list, ft_lstnew(read_txt));
	}
	free(eof);
	write_to_heredoc(here_doc_input_list, redirection);
}

static void	child_heredoc(t_simplecmd **cmds)
{
	size_t	i;
	int		j;
	char	*eof;
	t_list	*in;
	t_token	*rdr;

	i = 0;
	j = 0;
	while (cmds[j])
	{
		in = *(cmds[j]->in);
		while (in)
		{
			rdr = in->content;
			if (rdr->type == HEREDOC)
			{
				eof = strdup_protect(rdr->value);
				rdr->value = join_protect("/tmp/heredoc_",
						protect_itoa(i));
				handle_heredoc(rdr, eof);
				i ++;
			}
			in = in->next;
		}
		j++;
	}
	exit (0);
}

int	heredoc(t_simplecmd **cmds)
{
	int	pid;
	// int	exit_status;

	pid = fork();
	if (pid == -1)
		exit (-1);
	if (pid == 0)
		child_heredoc(cmds);
	// exit_status = wait_children(pid);
	wait_children(pid);
	// g_interactive = 1;
	set_heredoc(cmds);
	return (TRUE);
}