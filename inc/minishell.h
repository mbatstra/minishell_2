/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:30:49 by mbatstra          #+#    #+#             */
/*   Updated: 2022/09/16 14:05:01 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

char	**env_init(char **envp);
char	*env_getval(char **envp, const char *name);
void	env_setval(char **envp, const char *name, const char *val);

void	arr_clear(char **arr);
void	arr_init(char **arr, int len);
int		arr_len(char **arr);

void	builtin_exit(void);
int		builtin_cd(char *path, char **envp);
int		builtin_pwd(void);
int		builtin_echo(char *str, int nflag);
int		builtin_env(char **envp);

#endif 
