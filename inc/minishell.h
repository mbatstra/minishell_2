/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:30:49 by mbatstra          #+#    #+#             */
/*   Updated: 2022/09/15 18:34:51 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

char	**env_init(char **envp);
char	*env_getval(char **envp, char *name);
void	env_setval(char **envp, char *name, char *val);

void	arr_clear(char **arr);
void	arr_init(char **arr, int len);
int		arr_len(char **arr);

void	builtin_exit(void);
int		builtin_pwd(void);
int		builtin_cd(const char *path, char **envp);
int		builtin_echo(const char *str, int nflag);
int		builtin_env(char **envp);

#endif 
