/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amesmar <amesmar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:53:04 by xhuang            #+#    #+#             */
/*   Updated: 2025/01/15 19:38:03 by amesmar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


//includes
# include "../libft/libft.h"
# include <stdbool.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

//macros
# define PROMPT "\002\001\e[0m\e[32m\002 Minishell>$ \001\e[0m\002"
//token types
#define SPACES 1
#define WORD 2
#define VAR 3
#define PIPE 4
#define INPUT 5
#define TRUNC 6
#define HEREDOC 7
#define APPEND 8
#define END 9

//quoting status
#define DEFAULT 0
#define SQUOTE 1
#define DQUOTE 2

//global varibale
extern int	global_exit_code;


//structs
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



//functions

//init
bool	init_shell(t_shell *data, char **envp);
//run
void	run_minishell(t_shell *data);
//exit
void	terminate_shell(t_shell *data, int exit_code);
//free
void	free_shell(t_shell *data, bool clear_history);
void	free_ptr(void *ptr);
void	free_array(char **arr);
void	close_fds(t_cmd *cmds, bool close_backups);
//envp
int		envp_index(char **env, char *var);
int		envp_count(char **env);
char	*envp_value(char **env, char *var);
//pipe
bool	re_pipe(t_pipe *io);
void	close_pipe_fds(t_cmd *cmds, t_cmd *skip_cmd);
//signal
void	set_signals(void);
void		ignore_sigquit(void);
//builtins
int		exit_builtin(t_shell *data, char **args);
// parse_user_input.c
bool		parse_input(t_shell *data);
// tokenization.c
int			tokenization(t_shell *data, char *str);
// tokenization_utils.c
int			save_word_or_sep(int *i, char *str, int start, t_shell *data);
int			set_status(int status, char *str, int i);
int			is_separator(char *str, int i);
int			save_word(t_token **token_lst, char *str, int index, int start);
int			save_separator(t_token **token_lst, char *str, int index, int type);

// check_pipe.c
int			check_consecutives(t_token **token_lst);

// variable_check.c
int			check_if_var(t_token **token_lst);

// token_list.c
t_token		*lst_new_token(char *str, char *str_backup, int type, int status);
void		lst_add_back_token(t_token **alst, t_token *new_node);
void		lstdelone_token(t_token *lst, void (*del)(void *));
void		lstclear_token(t_token **lst, void (*del)(void *));
t_token		*insert_lst_between(t_token **head, t_token *to_del,
				t_token *insert);

/* ------------------------ EXPANSION ---------------------------------------*/
//var_expander.c
int			var_expander(t_shell *data, t_token **token_lst);


#endif