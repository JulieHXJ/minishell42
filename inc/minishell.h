/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:53:04 by xhuang            #+#    #+#             */
/*   Updated: 2025/02/13 21:13:28 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// includes
# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/stat.h>

// macros
# define PROMPT "\033[32mMinishell>$ \033[0m"

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

typedef struct s_redir
{
	char			*infile;
	char			*outfile;
	char			*heredoc_delimiter;
	bool			heredoc_quotes;
	int				fd_in;
	int				fd_out;
	int				stdin_backup;
	int				stdout_backup;
}					t_redir;

typedef struct s_cmd
{
	char			*cmd;
	char			*cmd_path;
	char			**args_list;
	bool			if_pipe;
	int				*pipe_fd;
	t_redir			*io;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct s_shell
{
	char			*input;
	char			**envp;
	t_token			*token_lst;
	t_cmd			*cmd_lst;
	pid_t			pid;
	char			*cur_dir;
	char			*old_dir;
}					t_shell;

// functions

// init
bool	init_shell(t_shell *mini, char **envp);

// signal
void	preset_signals(void);
void	signals_during_exec(void);

// exit
void				terminate_shell(t_shell *data, int exit_code);





// free
void				free_shell(t_shell *data, bool clear_history);
// void	reset_shell(t_shell *mini);
void				free_ptr(void *ptr);
void				free_arr(char **arr);
void				close_fds(t_cmd *cmds, bool close_backups);

// envp
int get_envp_index(char **env, char *var);
int	count_env(char **env);
char	*get_envp_value(char *str, char **envp);
bool	set_envp_var(t_shell *data, char *key, char *value);
bool				valid_envp(char *var);

// tokenizor
int	tokenize(t_shell *data, char *str);
int					check_token_list(t_token **token_lst);

// token_utils
int	set_quote_status(int status, char *str, int i);
int					word_or_sep(int *i, char *str, int start, t_shell *data);


// token_list.c
t_token	*new_token(char *str, char *str_backup, int type, int status);
void				add_token(t_token **alst, t_token *new_node);
void	remove_token(t_token *lst, void (*del)(void *));
void	free_token(t_token **lst, void (*del)(void *));
t_token	*insert_token(t_token **head, t_token *to_del, t_token *insert);





// check

int					check_if_var(t_token **token_lst);
bool				var_valid(char c);













// pipe
void				init_io(t_cmd *cmd);
bool				re_pipe(t_redir *io);
void				close_pipe_fds(t_cmd *cmds, t_cmd *skip_cmd);
void				free_io(t_redir *io);
bool				check_infile_outfile(t_redir *io);
bool				restore_io(t_redir *io);
bool				set_pipe_fds(t_cmd *cmds, t_cmd *c);
bool				create_pipes(t_shell *data);



// execute
int					execute_sys_bin(t_shell *data, t_cmd *cmd);
int					execute_local_bin(t_shell *data, t_cmd *cmd);
int					execute_command(t_shell *data, t_cmd *cmd);
int					execute(t_shell *data);
int					execute_builtin(t_shell *data, t_cmd *cmd);
int					cd_builtin(t_shell *data, char **args);
int					pwd_builtin(t_shell *data, char **args);
int					env_builtin(t_shell *data, char **args);
int					export_builtin(t_shell *data, char **args);
int					exit_builtin(t_shell *data, char **args);
bool				valid_envp(char *var);
char				**realloc_env_vars(t_shell *data, int size);
int					unset_builtin(t_shell *mini, char **args);

// parsing

int					handle_quotes(t_shell *data);
int					delete_quotes(t_token **token_node);
bool				remove_old_fd(t_redir *io, bool infile);
void				parse_str(t_cmd **cmd, t_token **token_lst,
						t_shell *minishell);
void				parse_redir_in(t_cmd **last_cmd, t_token **token_lst);
void				parse_redir_out(t_cmd **last_cmd, t_token **token_lst);
void				parse_append(t_cmd **last_node, t_token **token_lst);
char				*get_cmd_path(t_shell *data, char *name);



// expander
int					var_expander(t_shell *data, t_token **token_lst);
int					var_length(char *str);
void				copy_var(char *str, char *value, int *j);
char	*replace_token(char *oldstr, char *value, int newstr_size, int index);
int					replace_var(t_token **token_node, char *var_value, int n);
char				*retrieve_var(t_token *token, char *str, t_shell *data);
char				*identify_var(char *str);

// commands
int					echo_builtin(t_shell *data, char **args);
void				handle_commands(t_shell *data, t_token *token);

// cmd list
t_cmd				*new_cmd(bool value);
void				add_cmd(t_cmd **alst, t_cmd *new_node);
t_cmd				*last_cmd(t_cmd *cmd);
void	free_cmd(t_cmd **lst, void (*del)(void *));

// arguments
int					handle_args(t_token **token_node, t_cmd *last_cmd);
void				remove_empty(t_token **tokens);
int					add_args_echo(t_token **token_node, t_cmd *last_cmd);
int					create_args_echo(t_token **token_node, t_cmd *last_cmd);

// heredoc
bool				fill_heredoc(t_shell *data, t_redir *io, int fd);
char				*var_expander_hd(t_shell *data, char *str);
char				*replace_val_hd(char *str, char *var_value, int n);
void				parse_heredoc(t_shell *mini, t_cmd **last_node,
						t_token **token_lst);

// error
int					errmsg_cmd(char *command, char *detail, char *error_message,
						int error_nb);
void				errmsg(char *errmsg, char *detail, int quotes);

#endif