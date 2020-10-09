/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 12:28:57 by llefranc          #+#    #+#             */
/*   Updated: 2020/10/09 17:10:30 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <sys/stat.h>

# include "libftprintf.h"

//--------------------- UTILS ---------------------
int		error_msg(char *msg, int return_value);

//--------------------- BUILTINS ---------------------
int		builtin_echo(char **args);
int		builtin_env(char **args, char **env);
int		builtin_export(char **args, char ***env);
int     builtin_unset(char **args, char ***env);
int		builtin_pwd(char **args);
int		builtin_cd(char **args, char **env);

#endif