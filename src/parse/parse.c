/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 12:09:16 by mbatstra      #+#    #+#                 */
/*   Updated: 2022/10/13 18:21:54 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "libft.h"

void	parse_tokens(t_simplecmd **cmd_table, t_list **tokens)
{
	int	error;

	error = parse_redir(cmd_table, tokens);
	if (error)
	{
		printf("redir error message\n");
		return ;
	}
	error = parse_word(cmd_table, tokens);
	if (error)
	{
		printf("redir error message\n");
		return ;
	}
}
