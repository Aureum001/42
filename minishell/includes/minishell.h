/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 11:27:52 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/17 12:29:00 by ancanale         ###   ########.fr       */
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
	int				heredoc_fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	char			**envp;
	t_redir			*redirs;
	int				last_status;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_var_info
{
	char	*name;
	char	*start;
	char	*end;
}	t_var_info;

typedef struct s_parse_ctx
{
	char	**envp;
	int		last_status;
}	t_parse_ctx;

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
t_cmd			*parser(t_token *tokens, char **envp, int last_status);
void			free_cmd_list(t_cmd *cmd_list);
t_cmd			*new_cmd(void);
t_cmd			*parse_single_command(t_token **tkns, char **envp, int st);
void			add_redir(t_cmd *cmd, t_token *redir, t_token *file);
int				count_args(t_token *tokens);
void			parse_command_token(t_cmd *cmd, t_token **tkns,
					int *i, t_parse_ctx *ctx);
char			*process_variable(char **result, char **search_pos,
					char **envp, int last_status);
void			find_var_end(t_var_info *info);
char			*build_replaced_string(char *before, char *val, char *after);
char			*perform_string_replacement(char **result_ptr,
					t_var_info *info, char *value);
char			*replace_and_rebuild(char **result_ptr, t_var_info *info,
					char **envp, int last_status);

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
void			print_env_vars(char **envp);
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
void			add_entries(t_cmd *cmd, char *new_entry);
void			update_env_var(t_cmd *cmd, char *name, char *value);
int				is_valid_identifier(char *name);
void			update_pwd_after_cd(t_cmd *cmd);
void			handle_redirections(t_cmd *cmd, int *in_fd, int *out_fd);
void			execute_command(t_cmd *cmd, char **envp);
void			child_process(t_cmd *cmd, int in_fd, int pipefd[2]);
void			manage_parent_fds(int *in_fd, int pipefd[2],
					t_cmd *current_cmd);
char			*generate_prompt(void);
char			*expand_and_remove_quotes(char *value, char **envp,
					int last_status);
char			*expand_variables(char *str, char **envp, int last_status);
int				has_unclosed_quote(const char *line);
int				has_leading_pipe(const char *line);
int				has_trailing_pipe(const char *line);
char			*join_with_newline(char *s1, char *s2);
int				process_line(char *input, char ***envp_ptr, int last_status);
char			*read_multiline_input(char *initial_input);
void			process_all_heredocs(t_cmd *cmd_list);

// Builtin Utils
char			*get_cd_path(t_cmd *cmd);

#endif
