/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amesmar <amesmar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:53:04 by xhuang            #+#    #+#             */
/*   Updated: 2025/01/21 15:52:03 by amesmar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// includes
# include "../libft/libft.h"
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <errno.h>
# include <sys/stat.h>

// macros
# define PROMPT "\002\001\e[0m\e[32m\002 Minishell>$ \001\e[0m\002"

// token types
# define SPACES 1
# define WORD 2
# define VAR 3
# define PIPE 4
# define REDIRECT_IN 5
# define REDIRECT_OUT 6
# define HEREDOC 7
# define APPEND 8
# define END 9

// quoting status
# define DEFAULT 0
# define SQUOTE 1
# define DQUOTE 2

// global varibale
extern int			global_exit_code;

// structs
typedef struct s_token
{
	char			*input;
	char			*input_backup;
	bool			var_check;
	int				type;
	int				status;
	bool			joined;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_pipe
{
	char			*infile;
	char			*outfile;
	char			*heredoc_delimiter;
	bool			heredoc_quotes;
	int				fd_in;
	int				fd_out;
	int				stdin_backup;
	int				stdout_backup;
}					t_pipe;

typedef struct s_cmd
{
	char			*cmd;
	char			*cmd_path;
	char			**arg;
	bool			pipe_out;
	int				*pipe_fd;
	t_pipe			*pipe;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct s_shell
{
	char			**envp;
	t_cmd			*command;
	t_token			*token;
	pid_t			pid;
	char			*input;
	char			*cur_dir;
	char			*old_dir;
}					t_shell;

// functions

// init
bool				init_shell(t_shell *data, char **envp);

// run
void				run_minishell(t_shell *minishell,char **argv);

// exit
void				terminate_shell(t_shell *data, int exit_code);
int					exit_builtin(t_shell *data, char **args);

// free
void				free_shell(t_shell *data, bool clear_history);
void				free_ptr(void *ptr);
void				free_array(char **arr);
void				close_fds(t_cmd *cmds, bool close_backups);


// envp
int					envp_index(char **env, char *var);
int					envp_count(char **env);
char				*envp_value(char **env, char *var);
bool	set_env_var(t_shell *data, char *key, char *value);

// pipe
bool				re_pipe(t_pipe *io);
void				close_pipe_fds(t_cmd *cmds, t_cmd *skip_cmd);
void				free_io(t_pipe *io);
bool				check_infile_outfile(t_pipe *io);
bool				redirect_io(t_pipe *io);
bool				restore_io(t_pipe *io);
bool				set_pipe_fds(t_cmd *cmds, t_cmd *c);
bool				create_pipes(t_shell *data);

// signal
void				set_signals(void);
void				ignore_sigquit(void);
void				set_signals_noninteractive(void);

// execute builtins
int					execute_command(t_shell *data, t_cmd *cmd);
int					execute(t_shell *data,char **argv);
int					execute_builtin(t_shell *data, t_cmd *cmd);
int	cd_builtin(t_shell *data, char **args);


// parsing
bool				parse_input(t_shell *data);
int					handle_quotes(t_shell *data);
int					delete_quotes(t_token **token_node);
void				parse_str(t_cmd **cmd, t_token **token_lst, t_shell *minishell);
char				*get_cmd_path(t_shell *data, char *name);

// tokens
int					tokenization(t_shell *data, char *str);
int					check_token_list(t_token **token_lst);

// token_utils
int					set_status(int status, char *str, int i);
int					word_or_sep(int *i, char *str, int start, t_shell *data);

// check
int					check_token_list(t_token **token_lst);
int					check_if_var(t_token **token_lst);
bool				var_valid(char c);

// token_list.c
t_token				*new_tkn(char *str, char *str_backup, int type, int status);
void				add_back_tkn(t_token **alst, t_token *new_node);
void				delone_tkn(t_token *lst, void (*del)(void *));
void				clear_tkn(t_token **lst, void (*del)(void *));
t_token				*insert_tkn(t_token **head, t_token *to_del,
						t_token *insert);

// expander
int					var_expander(t_shell *data, t_token **token_lst);
int					var_length(char *str);
void				copy_var(char *str, char *value, int *j);
char				*new_token(char *oldstr, char *value, int newstr_size,
						int index);
int					replace_var(t_token **token_node, char *var_value, int n);
char				*retrieve_var(t_token *token, char *str, t_shell *data);
char				*identify_var(char *str);

// commands
int					echo_builtin(t_shell *data, char **args);
void				handle_commands(t_shell *data, t_token *token);

// cmd list
t_cmd				*new_cmd(bool value);
void				add_back_cmd(t_cmd **alst, t_cmd *new_node);
t_cmd				*last_cmd(t_cmd *cmd);
void				delone_cmd(t_cmd *lst, void (*del)(void *));
void				clear_cmd(t_cmd **lst, void (*del)(void *));
void				clear_token(t_token **lst, void (*del)(void *));
void				delone_token(t_token *lst, void (*del)(void *));


// arguments
int					handle_args(t_token **token_node, t_cmd *last_cmd);
void				remove_empty(t_token **tokens);
int					add_args_echo(t_token **token_node, t_cmd *last_cmd);
int					create_args_echo(t_token **token_node, t_cmd *last_cmd);

//error 
int					errmsg_cmd(char *command, char *detail, char *error_message, int error_nb);
void				errmsg(char *errmsg, char *detail, int quotes);


#endif