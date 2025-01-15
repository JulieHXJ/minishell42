/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amesmar <amesmar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:53:04 by xhuang            #+#    #+#             */
/*   Updated: 2025/01/15 16:56:19 by amesmar          ###   ########.fr       */
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


#endif