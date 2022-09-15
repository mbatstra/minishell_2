/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:18:51 by mbatstra          #+#    #+#             */
/*   Updated: 2022/09/15 16:16:11 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "libft.h"

int	builtin_cd(const char *path, char **envp)
{
	(void) envp;
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
