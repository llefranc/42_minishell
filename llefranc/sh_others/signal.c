/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:40:51 by llefranc          #+#    #+#             */
/*   Updated: 2020/10/23 14:06:08 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//ctrl c sigint
//ctrl \ sigquit
//
// - Essayez ctrl-C dans un prompt vide
// - Essayez ctrl-\ dans un prompt vide
// - Essayez ctrl-D dans un prompt vide
// - Essayez ctrl-C dans un prompt après que vous ayiez écrit des choses
// - Essayez ctrl-D dans un prompt après que vous ayiez écrit des choses
// - Essayez ctrl-\ dans un prompt après que vous ayiez écrit des choses
// - Essayez ctrl-C après avoir lancé une commande bloquante, comme cat ou grep sans argument
// - Essayez ctrl-\ après avoir lancé une commande bloquante, comme cat ou grep sans argument
// - Essayez ctrl-D après avoir lancé une commande bloquante, comme cat ou grep sans argument

void	handler_sigint(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", 1);
	// kill(0, SIGINT);
	// ft_putstr_fd("\b\b  \b\b", 1);
	// global_ret_value = 130;
	// if (signal(SIGINT, &handler_sigint) == SIG_ERR)
	// 	exit(error_msg("signal: signal handler failed\n", FAILURE));
}

void	handler_sigquit(int signum)
{
	(void)signum;
	signal(SIGQUIT, SIG_IGN);
	kill(0, SIGQUIT);
	// ft_putstr_fd("\b\b  \b\b", 1);
	// global_ret_value = 131;
	if (signal(SIGQUIT, &handler_sigquit) == SIG_ERR)
		exit(error_msg("signal: signal handler failed\n", FAILURE));
}