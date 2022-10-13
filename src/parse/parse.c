/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 12:09:16 by mbatstra      #+#    #+#                 */
/*   Updated: 2022/10/13 19:07:43 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "libft.h"

int	parse_tokens(t_simplecmd **cmd_table, t_list **tokens)
{
	int	error;

	error = parse_redir(cmd_table, tokens);
	if (error)
		return (error);
	error = parse_word(cmd_table, tokens);
	return (error);
}
