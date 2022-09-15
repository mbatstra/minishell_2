/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:48:41 by mbatstra          #+#    #+#             */
/*   Updated: 2022/09/06 17:48:43 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t size)
{
	char	*dup;
	int		len;

	dup = (char *) malloc(sizeof(char) * size + 1);
	if (!dup)
		return (dup);
	len = ft_strlcpy(dup, s1, size + 1);
	return (dup);
}
