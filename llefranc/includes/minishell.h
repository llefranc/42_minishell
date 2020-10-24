/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 12:28:57 by llefranc          #+#    #+#             */
/*   Updated: 2020/10/24 15:12:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <signal.h>

# include "libftprintf.h"

# define SUCCESS 0
# define FAILURE 1
# define WRONG_FILE 126
# define NOT_FOUND 127

# define F_PIPE -10
# define F_RIGHT -11
# define F_LEFT -12

# define INPUT 0
# define OUTPUT 1
# define OUTPUT_ADD 2
# define PIPE 3
# define EXEC 4

typedef struct			s_token
{
	int					type;
	char				**args;
	struct s_token		*next;
}						t_token;

int				save_stdin;
int				save_stdout;
int				cmd_is_running;
char			*global_path;
char			*global_home;
int				global_ret_value;
t_token			*first_token;
pid_t			pid;

//--------------------- BUILTINS ---------------------
int		builtin_echo(char **args);
int		builtin_env(char **args, char **env);
int		builtin_export(char **args, char ***env);
int     builtin_unset(char **args, char ***env);
int		builtin_pwd(char **args);
int		builtin_cd(char **args, char **env);
int		builtin_exit(char **args, char **env);

//--------------------- EXECUTION ---------------------
int		execve_part(char **args, char **env);
int		execution(t_token *tok, char ***env);
int		do_redirection(int type, char *file);
int		do_pipe(t_token *token, char ***env);

//--------------------- UTILS ---------------------
int		error_msg(char *msg, int return_value);
void	*error_msg_ptr(char *msg, void *ptr);
int		init_global_path(char **env);
int		init_global_home(char **env);
t_token	*create_token_list(char **cmd);
void	free_token_list(t_token *token);
void	handler_sigint(int signum);
void	handler_sigquit(int signum);

#endif