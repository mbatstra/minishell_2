/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:30:49 by mbatstra          #+#    #+#             */
/*   Updated: 2022/09/20 18:17:31 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define STDIN 0
# define STDOUT 1
# define STDERR 2

# include "libft.h"

enum e_types {
	RDR_IN,
	RDR_OUT,
	RDR_RDIN,
	RDR_APP,
	PIPE,
	WORD
};

typedef struct s_token {
	enum e_types	type;
	char			*value;
}			t_token;

typedef struct s_io_table {
	int	in;
	int	out;
	int	err;
}			t_io_table;

typedef struct s_simplecmd {
	int		argc;
	char	**argv;
}			t_simplecmd;

typedef struct s_cmd {
	t_simplecmd	**simplecmds;
	t_io_table	io;
}			t_cmd;

// lexing and parsing
int		lexer(t_list **tokens, char *cmd_line);

// functions for expandign and setting env vars
void	env_init(char **envp, t_list **new_env);
void	env_setval(t_list **envp, const char *name, const char *val);
char	*env_getval(t_list **envp, const char *name);

// builtins
void	builtin_exit(void);
int		builtin_export(t_list **envp, char *nameval);
int		builtin_unset(t_list **envp, char *name);
int		builtin_cd(char *path, t_list **envp);
int		builtin_pwd(void);
int		builtin_echo(char *str, int nflag);
int		builtin_env(t_list *envp);

#endif 
