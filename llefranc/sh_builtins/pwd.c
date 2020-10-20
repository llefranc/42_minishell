/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 15:24:22 by llefranc          #+#    #+#             */
/*   Updated: 2020/10/20 17:27:44 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Prints the current working directory on stdout, using getcwd command.
*/
int		builtin_pwd(char **args)
{
	if (args && args[1] && args[1][0] == '-') //our pwd doesn't handle options
        return (error_msg("pwd: no options are allowed\n", FAILURE));
	ft_fd_printf(STDOUT_FILENO, "%s\n", global_path);
	return (SUCCESS);
}