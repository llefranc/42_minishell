/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 12:28:48 by llefranc          #+#    #+#             */
/*   Updated: 2020/10/20 15:13:58 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Prints an error message on stdout and returns NULL.
*/
void	*error_msg_ptr(char *msg, void *ptr)
{
	ft_fd_printf(STDERR_FILENO, "minishell: %s", msg);
	return (ptr);
}

/*
** Prints an error message on stdout and returns the error value.
*/
int		error_msg(char *msg, int return_value)
{
	ft_fd_printf(STDERR_FILENO, "minishell: %s", msg);
	return (return_value);
}