/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:22:40 by mbatstra          #+#    #+#             */
/*   Updated: 2022/09/19 17:16:38 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

// error messages? should output be buffered?
int	builtin_env(t_list *envp)
{
	while (envp != NULL)
	{
		if (printf("%s\n", envp->content) < 0)
			return (1);
		envp = envp->next;
	}
	return (0);
}
