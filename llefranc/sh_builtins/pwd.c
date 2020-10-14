/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 15:24:22 by llefranc          #+#    #+#             */
/*   Updated: 2020/10/14 16:59:08 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Prints the current working directory on stdout, using getcwd command.
*/
int		builtin_pwd(char **args)
{
	if (args && args[1] && args[1][0] == '-') //our pwd doesn't handle options
        return (error_msg("minishell: pwd: no options are allowed\n", FAILURE));
	if (!global_path && !(global_path = getcwd(NULL, 0)))
        return (error_msg("minishell: pwd: getcwd command failed\n", FAILURE));
	ft_printf("%s\n", global_path);
	return (SUCCESS);
}