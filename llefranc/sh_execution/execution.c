/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 11:23:44 by llefranc          #+#    #+#             */
/*   Updated: 2020/10/21 15:14:38 by llefranc         ###   ########.fr       */
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
	!ft_strcmp("echo", args[0]) && (ret = 1) ? global_ret_value = builtin_echo(args) : 0; //if args[0] match one builtin, put ret value to 0 and launch the appropriate builtin
	!ft_strcmp("cd", args[0]) && (ret = 1) ? global_ret_value = builtin_cd(args, *env) : 0;
	!ft_strcmp("pwd", args[0]) && (ret = 1) ? global_ret_value = builtin_pwd(args) : 0;
	!ft_strcmp("export", args[0]) && (ret = 1) ? global_ret_value = builtin_export(args, env) : 0;
	!ft_strcmp("unset", args[0]) && (ret = 1) ? global_ret_value = builtin_unset(args, env) : 0;
	!ft_strcmp("env", args[0]) && (ret = 1) ? global_ret_value = builtin_env(args, *env) : 0;
	!ft_strcmp("exit", args[0]) && (ret = 1) ? global_ret_value = builtin_exit(args, *env) : 0;
	return (ret);
}


int		execution(t_token *token, char ***env)
{
	t_token	*tmp;

	tmp = token;
	if (tmp)
		// ft_fd_printf(STDERR_FILENO, "tmp type = %d et tmp->content = %s\n", tmp->type, (tmp->args)[0]);
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == INPUT || tmp->type == OUTPUT || tmp->type == OUTPUT_ADD)
			if (do_redirection(tmp->type, (tmp->args)[0]))
				return (global_ret_value = FAILURE);
		tmp = tmp->next;
	}
	tmp = token;
	if (tmp)
		// ft_fd_printf(STDERR_FILENO, "tmp type = %d et tmp->content = %s\n", tmp->type, (tmp->args)[0]);
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == EXEC) //there is only one token EXEC between pipes / semicolons
		{
			// ft_fd_printf(STDERR_FILENO, "on exec ce token tmp type = %d et tmp->content = %s\n", tmp->type, (tmp->args)[0]);
			if (!find_builtin(tmp->args, env))
				execve_part(tmp->args, *env);
		}
		// if (tmp)
		// 	ft_fd_printf(STDERR_FILENO, "tmptype = %d\n", tmp->type);
		tmp = tmp->next;
	}
	dup2(save_stdin, STDIN_FILENO);		//restore back stdin and stdout
	dup2(save_stdout, STDOUT_FILENO);
	// ft_fd_printf(STDERR_FILENO, "retour fonction = %d\n", global_ret_value);
	return (SUCCESS);
}
// tok        tmp
// |          |
// echo salut | wc
// echo salut

int		is_it_last_instruction(t_token *token)
{
	while (token && token->type != PIPE) //on cherche le prochain pipe
		token = token->next;
	if (!token)
		return (1);
	else
		return (0);
}

int		pipe_exec_son(t_token *token, char ***env, int fdpipe[2])
{
	close(fdpipe[0]);
	dup2(fdpipe[1], STDOUT_FILENO);
	execution(token, env);
	close(fdpipe[1]);
	exit(SUCCESS);
}

int		do_pipe(t_token *token, char ***env)
{
	t_token		*tmp;
	pid_t		pid;
	int			fdpipe[2];
	int			fd_in;
	int			status;

	fd_in = STDIN_FILENO;
	tmp = token;
	while (tmp && tmp->type != PIPE)
		tmp = tmp->next;
	if (!tmp)
		execution(token, env);
	else
	{
		while (token)
		{
			pipe(fdpipe);
			pid = fork();
			if (pid == -1)
				return (global_ret_value = error_msg("pipe: fork failed\n", FAILURE));
			else if (!pid)
			{
				close(fdpipe[0]);
				dup2(fd_in, STDIN_FILENO); //on met le dernier fdin sauvegarde
				if (tmp) //si il reste une commande
					dup2(fdpipe[1], STDOUT_FILENO);
				execution(token, env);
				close(fd_in);
				close(fdpipe[1]);
				exit(SUCCESS);
			}
			else
			{
				close(fdpipe[1]);
				waitpid(pid, &status, 0);
				fd_in = fdpipe[0];
				while (token && token->type != PIPE)
					token = token->next;
				if (token && token->type == PIPE)
					token = token->next;
				tmp = token; //pour savoir si il reste une prochaine commande a executer
				while (tmp && tmp->type != PIPE)
					tmp = tmp->next;
			}
		}
	}
	global_ret_value = WEXITSTATUS(status);
	return (SUCCESS);
}