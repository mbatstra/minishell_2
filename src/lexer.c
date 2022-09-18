/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:22:08 by mbatstra          #+#    #+#             */
/*   Updated: 2022/09/18 16:35:08 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

t_token	*tokenize(const char *str_token)
{
	t_token	*new_token;
	char	*new_value;

	new_token = (t_token *)malloc(sizeof(t_token));
	new_value = ft_strdup(str_token);
	if (new_token == NULL || new_value == NULL)
	{
		free(new_token);
		free(new_value);
		return (NULL);
	}
	new_token->value = new_value;
	// set type
	return (new_token);
}

// not sure yet what conditions to check llist on
// null, already contains elements, etc
int	lexer(t_list **tokens, char *cmd_line)
{
	char	**spl_line;
	int		i;

	i = 0;
	spl_line = ft_split(cmd_line, ' ');
	if (spl_line == NULL)
		return (1);
	while (spl_line[i] != NULL)
	{
		ft_lstadd_back(tokens, ft_lstnew(spl_line[i])); 
		// add return value to add_back to check if allocation success
		i++;
	}
	return (0);
}
