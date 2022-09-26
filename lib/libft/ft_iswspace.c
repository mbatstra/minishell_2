/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswspace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:29:00 by mbatstra          #+#    #+#             */
/*   Updated: 2022/09/26 18:29:46 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iswspace(char c)
{
	if (c == ' ' || \
	c == '\t' || \
	c == '\n' || \
	c == '\v' || \
	c == '\f' || \
	c == '\r')
		return (1);
	else
		return (0);
}
