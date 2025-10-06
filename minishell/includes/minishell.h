/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 11:27:52 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/06 10:01:05 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <ctype.h>
# include <signal.h>
# include "libft.h"

// --- Tokenizer Structures ---

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

// --- Parser/Executor Structures ---

typedef struct s_redir
{
	t_token_type	type;
	char			*filename;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	char			**envp;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

// --- Signal Handling ---
void			setup_interactive_signals(void);
void			setup_exec_signals(void);

// --- Function Prototypes ---

// Lexer
t_token			*lexer(char *line);
t_token_type	get_metachar_type(char c, char next);
t_token			*get_metachar_token(char **line_ptr);
t_token			*get_word_token(char **line_ptr);
int				find_closing_quote(const char *str, char quote);

// Parser
t_cmd			*parser(t_token *tokens, char **envp);
void			free_cmd_list(t_cmd *cmd_list);
t_cmd			*new_cmd(void);

// Executor
int				executor(t_cmd *cmd_list);
char			*find_cmd_path(char *cmd, char **envp);
int				execute_cd(t_cmd *cmd);
int				execute_echo(t_cmd *cmd);
int				execute_pwd(t_cmd *cmd);
int				execute_export(t_cmd *cmd);
int				execute_unset(t_cmd *cmd);
int				execute_exit(t_cmd *cmd);
int				execute_env(t_cmd *cmd);

// Builtin Dispatcher
int				is_builtin(t_cmd *cmd);
int				execute_builtin(t_cmd *cmd);
void			print_all_env_vars(char **envp);
int				export_single_var(t_cmd *cmd, char *arg);
int				find_env_index(char **env, char *name);

// Utils
void			free_tokens(t_token *tokens);
t_token			*new_token(char *value, t_token_type type);
int				ft_isspace(int c);
void			print_tokens(t_token *tokens);
const char		*token_type_to_string(t_token_type type);
void			free_split(char **arr);
char			*remove_quotes(char *str);
char			**copy_env(char **envp);
void			remove_env_var(t_cmd *cmd, char *name);
char			*get_env_value(char **envp, char *name);
void			update_pwd_after_cd(t_cmd *cmd);
void			handle_redirections(t_cmd *cmd, int *in_fd, int *out_fd);
void			execute_command(t_cmd *cmd, char **envp);
void			child_process(t_cmd *cmd, char **envp,
					int in_fd, int pipefd[2]);
void			manage_parent_fds(int *in_fd, int pipefd[2],
					t_cmd *current_cmd);
char			*generate_prompt(void);

#endif
