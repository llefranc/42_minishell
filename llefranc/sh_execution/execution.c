/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 11:23:44 by llefranc          #+#    #+#             */
/*   Updated: 2020/10/23 15:38:56 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** If args[0] matches a builtin, launches the proper builtin and sets
** global_ret_value with the builtin return value. Returns 1 if it launched a
** builtin, 0 otherwise.
*/
int		find_builtin(char **args, char ***env)
{
	int ret;
	
	ret = 0;
	if (!args)
		return (ret);
	!ft_strcmp("echo", args[0]) && (ret = 1) ? global_ret_value = builtin_echo(args) : 0;
	!ft_strcmp("cd", args[0]) && (ret = 1) ? global_ret_value = builtin_cd(args, *env) : 0;
	!ft_strcmp("pwd", args[0]) && (ret = 1) ? global_ret_value = builtin_pwd(args) : 0;
	!ft_strcmp("export", args[0]) && (ret = 1) ? global_ret_value = builtin_export(args, env) : 0;
	!ft_strcmp("unset", args[0]) && (ret = 1) ? global_ret_value = builtin_unset(args, env) : 0;
	!ft_strcmp("env", args[0]) && (ret = 1) ? global_ret_value = builtin_env(args, *env) : 0;
	!ft_strcmp("exit", args[0]) && (ret = 1) ? global_ret_value = builtin_exit(args, *env) : 0;
	return (ret);
}

/*
** Opens the file and changes STDIN with the new fd value if type == INPUT
** or changes STDOUT with new fd value if type == OUTPUT || OUTPUT_ADD.
** Returns FAILURE if open failed.
*/
int		do_redirection(int type, char *file)
{
	int	new_fd;

	if (type == INPUT)
		if (((new_fd = open(file, O_RDONLY)) == -1) &&
				ft_fd_printf(STDERR_FILENO, "minishell: %s: No such file or directory\n", file))
			return (FAILURE);
	if (type == OUTPUT)
		if (((new_fd = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
				&& ft_fd_printf(STDERR_FILENO, "minishell: %s: file opening failed\n", file))
			return (FAILURE);
	if (type == OUTPUT_ADD)
		if (((new_fd = open(file, O_RDWR | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
				 &&ft_fd_printf(STDERR_FILENO, "minishell: %s: file opening failed\n", file))
			return (FAILURE);
	if (type == INPUT)
		dup2(new_fd, STDIN_FILENO);
	else if (type == OUTPUT || type == OUTPUT_ADD)
		dup2(new_fd, STDOUT_FILENO);
	close(new_fd);
	return (SUCCESS);
}

/*
** Does all the redirections until a pipe / semicolons / end of the command,
** and then exec the builtin / command.
*/
int		execution(t_token *token, char ***env)
{
	t_token	*tmp;

	tmp = token;
	while (tmp && tmp->type != PIPE) //we treat all the redirections between pipes / semicolons
	{
		if (tmp->type == INPUT || tmp->type == OUTPUT || tmp->type == OUTPUT_ADD)
			if (do_redirection(tmp->type, (tmp->args)[0]))
				return (global_ret_value = FAILURE);
		tmp = tmp->next;
	}
	tmp = token;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == EXEC) //there is only one token EXEC between pipes / semicolons
			if (!find_builtin(tmp->args, env))
				execve_part(tmp->args, *env);
		tmp = tmp->next;
	}
	dup2(save_stdin, STDIN_FILENO);		//restore back stdin and stdout
	dup2(save_stdout, STDOUT_FILENO);
	return (SUCCESS);
}