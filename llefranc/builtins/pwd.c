/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 15:24:22 by llefranc          #+#    #+#             */
/*   Updated: 2020/10/12 11:18:09 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Prints the current working directory on stdout, using getcwd command.
*/
int		builtin_pwd(char **args)
{
	if (args && args[1] && args[1][0] == '-') //our pwd doesn't handle options
        return (error_msg("minishell: pwd: no options are allowed\n", 1));
	if (!global_path && !(global_path = getcwd(NULL, 0)))
        return (error_msg("minishell: pwd: getcwd command failed\n", 1));
	ft_printf("%s\n", global_path);
	return (0);
}