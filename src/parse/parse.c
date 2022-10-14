/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:12:32 by mbatstra          #+#    #+#             */
/*   Updated: 2022/10/14 16:50:29 by mbatstra         ###   ########.fr       */
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
