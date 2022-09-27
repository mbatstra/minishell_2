/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:30:49 by mbatstra          #+#    #+#             */
/*   Updated: 2022/09/27 19:31:06 by mbatstra         ###   ########.fr       */
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

typedef struct s_lexer_flags {
	int	is_single_quoted;
	int	is_double_quoted;
	int	is_delim;
	int	last_exit;
}			t_lexer_flags;

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
int		lexer_tokenize(t_list **tokens, char *cmd_line);
int		lexer_value_append(t_token *token, char *value, int val_len);
int		lexer_is_operator_char(char c);
void	lexer_clear_token(void *token);
void	lexer_tokenize_word(t_token *token, char *cmd, \
							int *i, t_lexer_flags *flags);
void	lexer_tokenize_operator(t_token *token, char *cmd, \
								int *i, t_lexer_flags *flags);

// expansion
char	*expand_relpath(char *relp);
char	*expand_parent_dir(t_list *envp);

// functions for expandign and setting env vars
void	env_init(char **envp, t_list **new_env);
void	env_setval(t_list **envp, const char *name, const char *val);
char	*env_getval(t_list *envp, const char *name);

// builtins
void	builtin_exit(void);
int		builtin_export(t_list **envp, char *nameval);
int		builtin_unset(t_list **envp, char *name);
int		builtin_cd(char *path, t_list **envp);
int		builtin_pwd(void);
int		builtin_echo(char *str, int nflag);
int		builtin_env(t_list *envp);

#endif 
