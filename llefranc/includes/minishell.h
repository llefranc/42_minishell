/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 12:28:57 by llefranc          #+#    #+#             */
/*   Updated: 2020/10/08 15:29:39 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/errno.h>

# include "libftprintf.h"

//--------------------- UTILS ---------------------
int		error_msg(char *msg, int return_value);

//--------------------- BUILTINS ---------------------
int		builtin_echo(char **args);

int		builtin_env(char **args, char **env);

int		len_var_name(char *var);
int     is_it_new_variable(char *var, char **env);
char	**copy_env(char **env, int add_quotes_bool);
int		builtin_export(char **args, char ***env);

int     builtin_unset(char **args, char ***env);

int		builtin_pwd(char **args);

#endif