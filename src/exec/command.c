/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cicekyuzbas <cyuzbas@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/03 21:36:18 by cicekyuzbas   #+#    #+#                 */
/*   Updated: 2022/10/16 17:49:54 by cicekyuzbas   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

static void	ft_free(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

static char	*join_path(char **paths, char *cmd)
{
	char	*full_path;
	char	*tmp_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp_path, cmd);
		free(tmp_path);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	ft_free(paths);
	return (NULL);
}

static char	*find_path(char *cmd, t_list **envp)
{
	char	**paths;
	char	*full_path;
	char	*path;

	path = NULL;
	path = env_getval(*envp, "PATH");
	if (!path)
		return (0);
	// printf("%s\n", path);
	paths = ft_split(path, ':');
	full_path = join_path(paths, cmd);
	// printf("%s\n", full_path);
	if (full_path)
		return (full_path);
	free(full_path);
	return (0);
}

void ft_execve(t_simplecmd *simplecmd, t_list **envp)
{
	char 	*path;
	char 	**envp_arr;
	char 	**cmd_arr;
	t_list	**arg;
	
	arg = simplecmd->arg;
	cmd_arr = envp_array(*arg);
	envp_arr = envp_array(*envp);
	if (simplecmd == NULL)
	{
		execve("", cmd_arr, envp_arr);
		printf("Null path : error with execve\n");
		return ;
	}
	else if (ft_strchr(cmd_arr[0], '/') != 0)
	{
		execve(cmd_arr[0], cmd_arr, envp_arr);
		printf("error with execve\n");
		//strjoin all argv's or put in a loop when printing?
		perror(cmd_arr[0]);
		// ft_putstr_fd(simplecmd->argv[0], 2);
		// ft_putendl_fd(": No such file or directory", 2);
		// exit (127);
	}
	else if (envp[0])
	{
		path = find_path(cmd_arr[0], envp);
		// printf("cmdarr=%s - path=%s\n", cmd_arr[0], path);
		
		execve(path, cmd_arr, envp_arr);
		printf("error with execve\n");
	}
}