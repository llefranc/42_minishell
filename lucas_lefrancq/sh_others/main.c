/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 12:28:41 by lucas          #+#    #+#             */
/*   Updated: 2020/10/27 14:43:47 by lucas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


char	**copy_env(char **env, int add_quotes_bool);
int		find_var_in_env(char *var, char **env);


void	ft_init_sh(t_sh *sh)
{
	sh->onemoredollar = 0;
	sh->envlen = 0;
	sh->cmpvar = 0;
	sh->syntaxerror = 0;
	sh->sqflag = 0;
	sh->dqflag = 0;
	sh->command = NULL;
	sh->copyenv = NULL;
}

int main(int ac, char *av[], char *env[])
{
	int	ret_gnl = 1;
	char *line = NULL;
	char	**semicolon;
	t_sh	sh;

	(void)av;
	if (signal(SIGINT, &handler_sigint) == SIG_ERR ||
			signal(SIGQUIT, &handler_sigquit) == SIG_ERR)
		exit(error_msg("signal: signal handler failed\n", FAILURE));
	if (ac != 1)
	{
		ft_fd_printf(1, "just launch minishell exe, without any argument\n");
		exit(EXIT_FAILURE);
	}
	save_stdin = dup(STDIN_FILENO);
	save_stdout = dup(STDOUT_FILENO);
	
	semicolon = NULL;
	ft_init_sh(&sh);
	if (env && env[0])
		ft_copy_env(env, &sh);
	else if (create_new_env(&sh))
		return (FAILURE);

	if (init_global_path(sh.copyenv) || init_global_home(sh.copyenv))
	{
		free_split(sh.copyenv);
		free(global_home);
		free(global_path);
		return (error_msg("main: malloc failed\n", FAILURE));
	}

	ft_fd_printf(0, "minishel$ ");
	while (ret_gnl)
	{
		sh.sqflag = 0;
		sh.dqflag = 0;
		sh.syntaxerror = 0;
		
		cmd_is_running = 0;
		ret_gnl = get_next_line(0, &line);
		if (!line[0] && ret_gnl) //if no text
		{
			free(line);
			free(global_home);
			free(global_path);
			ft_fd_printf(0, "minishel$ ");
			continue ;
		}
		else if (!line[0] && !ret_gnl) //handling Ctrl-D
		{
			free(line);
			free(global_home);
			free(global_path);
			ft_fd_printf(1, "exit\n");
			exit(SUCCESS);
		}
		cmd_is_running = 1;
		
		line = ft_lexer(line, &sh);
		if (sh.syntaxerror == 0)
		{
			semicolon = (ft_cdsplit(line, -3));
			ft_parser(semicolon, &sh);
		}
		free(line);
		if (sh.syntaxerror == 0)
			ft_free_doublearray(semicolon);
		line = NULL;
		ft_fd_printf(0, "minishel$ ");
	}
	return (0);
}

