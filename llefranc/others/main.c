/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 12:28:41 by llefranc          #+#    #+#             */
/*   Updated: 2020/10/12 15:09:01 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


char	**copy_env(char **env, int add_quotes_bool);
int		find_var_in_env(char *var, char **env);

//echo >>> output
//cd
//pwd >>> output
//export
//unset
//env >> output
//exit
//gerer le cas ou le cd est a la fin d'un pipe 

//penser a mettre en variable globale le retour des fonctions et le ptr qui tient le tab de structs
#include <stdio.h>

int		find_builtin(char **args, char ***env, int *ret_func)
{
	int ret;
	
	ret = 0;
	if (!args)
		return (ret);
	!ft_strcmp("echo", args[0]) && (ret = 1) ? *ret_func = builtin_echo(args) : 0; //if args[0] match one builtin, put ret value to 0 and launch the appropriate builtin
	!ft_strcmp("cd", args[0]) && (ret = 1) ? *ret_func = builtin_cd(args, *env) : 0;
	!ft_strcmp("pwd", args[0]) && (ret = 1) ? *ret_func = builtin_pwd(args) : 0;
	!ft_strcmp("export", args[0]) && (ret = 1) ? *ret_func = builtin_export(args, env) : 0;
	!ft_strcmp("unset", args[0]) && (ret = 1) ? *ret_func = builtin_unset(args, env) : 0;
	!ft_strcmp("env", args[0]) && (ret = 1) ? *ret_func = builtin_env(args, *env) : 0;
	// !ft_strcmp("exit", args[0]) && (ret = 1) ? ft_printf("salut\n") : 0;
	// ft_printf("---------\n", ret);
	return (ret);
}

#include <stdio.h>
int main(int ac, char *av[], char *env[])
{
	int ret_func = 0;
	int	ret_gnl = 1;
	char *line = NULL;
	char **cmd;
	char **env_shell;

	(void)av;
	if (!(env_shell = copy_env(env, 0)))
		return (1);
	if (ac != 1)
	{
		ft_printf("just launch minishell exe, without any argument\n");
		exit(EXIT_FAILURE);
	}
	// PARSEUR QUI DOIT RENVOYER UN DOUBLE TABLEAU DE CHAR (**ARGV) TERMINE PAR NULL
	ft_printf("minishel$ ");
	while (ret_gnl)
	{
		ret_gnl = get_next_line(1, &line);
		if (!line[0])
		{
			free(line);
			continue ;
		}

		cmd = ft_split(line, ' ');
		if (!find_builtin(cmd, &env_shell, &ret_func))
			ft_printf("this command isn't a builtin command\n");
		// ft_printf("ret_func = %d\n>>> ", ret_func);
		ft_printf("minishel$ ", ret_func);
		free(line);
		free_split(cmd);
		line = NULL;
		cmd = NULL;
	}
	return (0);
}

