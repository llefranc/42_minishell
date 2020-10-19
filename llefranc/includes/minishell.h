/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 12:28:57 by llefranc          #+#    #+#             */
/*   Updated: 2020/10/19 17:48:02 by llefranc         ###   ########.fr       */
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

char			*global_path;
int				global_ret_value;
t_token			*first_token;


//--------------------- UTILS ---------------------
int		error_msg(char *msg, int return_value);
void	*error_msg_ptr(char *msg, void *ptr);
t_token	*create_list(char **cmd);

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

int		execution(t_token **tok, char ***env);

#endif