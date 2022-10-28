/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/20 14:37:33 by mbatstra      #+#    #+#                 */
/*   Updated: 2022/10/28 11:57:21 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "libft.h"
#include "exec.h"

static int	is_defined(t_list **envp, char *nameval)
{
	t_list	*node;
	int		namelen;

	node = *envp;
	namelen = ft_strchr(nameval, '=') - nameval;
	while (node != NULL)
	{
		if (!ft_strncmp(node->content, nameval, namelen))
			return (1);
		node = node->next;
	}
	return (0);
}

static char	**nameval_split(char *nameval)
{
	char	**spl_nameval;
	char	*name;
	char	*val;
	int		namelen;

	spl_nameval = (char **)malloc(2 * sizeof(char *));
	namelen = ft_strchr(nameval, '=') - nameval;
	name = ft_strndup(nameval, namelen);
	val = ft_strdup(ft_strchr(nameval, '=') + 1);
	if (spl_nameval == NULL || name == NULL || val == NULL)
	{
		free(spl_nameval);
		free(name);
		free(val);
		return (NULL);
	}
	spl_nameval[0] = name;
	spl_nameval[1] = val;
	return (spl_nameval);
}

static int	invalid_name(char *name)
{
	int			i;

	i = 0;
	while (name[i])
	{
		if (name[i] == '=' && i > 0)
			break ;
		if (ft_isdigit(name[0]) || \
			(!ft_isalnum(name[i]) && name[i] != '_'))
		{
			print_error("export: `", name, "': not a valid identifier");
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_export(char *nameval, t_list **envp)
{
	int		exit_code;
	char	**spl_nameval;

	if (invalid_name(nameval))
	{
		exit_code = 1;
	}
	if (is_defined(envp, nameval))
	{
		spl_nameval = nameval_split(nameval);
		if (spl_nameval == NULL)
			return (1);
		env_setval(envp, spl_nameval[0], spl_nameval[1]);
		free_spl_nameval(spl_nameval);
		return (0);
	}
	return (exit_code);
}

int	builtin_export(t_list **envp, t_list *arg)
{
	t_list	*node;
	char	*dup;
	char	*nameval;
	int		exit_code;

	if (!arg->next)
		return (write_export_env(*envp));
	while (arg->next)
	{
		nameval = (char *)(arg->next->content);
		exit_code = check_export(nameval, envp);
		dup = ft_strdup(nameval);
		node = ft_lstnew(dup);
		if (node == NULL)
		{
			free(dup);
			return (1);
		}
		ft_lstadd_back(envp, node);
		arg = arg->next;
	}
	return (exit_code);
}
