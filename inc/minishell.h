/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:30:49 by mbatstra          #+#    #+#             */
/*   Updated: 2022/10/11 19:07:35 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define IN 0
# define OUT 1
# define ERR 2

# include "libft.h"

enum e_types {
	RDR_IN,
	HEREDOC,
	RDR_OUT,
	RDR_APP,
	PIPE,
	WORD
};

typedef struct s_token {
	enum e_types	type;
	char			*value;
	int				expand;
}			t_token;

typedef struct s_lexer_flags {
	int	is_single_quoted;
	int	is_double_quoted;
	int	is_delim;
	int	last_exit;
}			t_lexer_flags;

typedef struct s_simplecmd {
	int		argc;
	char	**argv;
}			t_simplecmd;

typedef struct s_cmd {
	t_simplecmd	**simplecmds;
	t_token		**in;
	t_token		**out;
	t_token		**err;
}			t_cmd;

// lexing 
t_token	*lexer_token_copy(t_token *token);
void	lexer_clear_token(void *token);
void	lexer_token_identifier(t_token *token);
void	lexer_tokenize_word(t_token *token, char *cmd, \
							int *i, t_lexer_flags *flags);
void	lexer_tokenize_operator(t_token *token, char *cmd, \
								int *i, t_lexer_flags *flags);
int		lexer_tokenize(t_list **tokens, char *cmd_line);
int		lexer_value_append(t_token *token, char *value, int val_len);
int		lexer_is_operator_char(char c);

// parsing
t_token	**parse_append_arr(t_token **arr, t_token *redir);
void	parse_init_cmd(t_cmd *cmd);
void	parse_tokens(t_cmd *cmd_table, t_list **tokens);
void	parse_clear_cmd(t_cmd *cmd);
void	parse_clear_tok_arr(t_token **tok_arr);
int		parse_redir(t_cmd *cmd_table, t_list **tokens);

// expansion
char	*expand_relpath(char *relp);
char	*expand_parent_dir(t_list *envp);

// functions for expandign and setting env vars
void	env_init(char **envp, t_list **new_env);
void	env_setval(t_list **envp, const char *name, const char *val);
char	*env_getval(t_list *envp, const char *name);

// builtins
// unset and export should work for multiple vars!!!
// exit should return last exit code
void	builtin_exit(void);
int		builtin_export(t_list **envp, char *nameval);
int		builtin_unset(t_list **envp, char *name);
int		builtin_cd(char *path, t_list **envp);
int		builtin_pwd(void);
int		builtin_echo(char *str, int nflag);
int		builtin_env(t_list *envp);

#endif 
