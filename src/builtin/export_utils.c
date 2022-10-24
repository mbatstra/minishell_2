/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cyuzbas <cyuzbas@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 15:44:27 by cyuzbas       #+#    #+#                 */
/*   Updated: 2022/10/24 15:45:00 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	free_spl_nameval(char **spl_nameval)
{
	free(spl_nameval[0]);
	free(spl_nameval[1]);
	free(spl_nameval);
}