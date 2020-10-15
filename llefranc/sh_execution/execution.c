/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 11:23:44 by llefranc          #+#    #+#             */
/*   Updated: 2020/10/15 17:03:08 by llefranc         ###   ########.fr       */
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

int		execution(t_token **tok, char ***env)
{
	int		i;

	i = -1;
	while (tok[++i])
	{
		if (tok[i]->type == EXEC)
			if (!find_builtin((char **)((tok[i])->ptr), env))
				execve_part((char **)(tok[i]->ptr), *env);
	}
	ft_printf("retour fonction = %d\n", global_ret_value);
	return (SUCCESS);
}