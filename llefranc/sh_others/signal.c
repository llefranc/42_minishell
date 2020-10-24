/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:40:51 by llefranc          #+#    #+#             */
/*   Updated: 2020/10/24 15:23:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handler_sigint(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", 1);
	if (!cmd_is_running)
		ft_putstr_fd("minishel$ ", 1);
}

void	handler_sigquit(int signum)
{
	(void)signum;
	if (!cmd_is_running)
		ft_putstr_fd("\b\b  \b\b", 1);
	else
		ft_putstr_fd("Quit: core dumped\n", 2);
}