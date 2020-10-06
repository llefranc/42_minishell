/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 12:35:53 by llefranc          #+#    #+#             */
/*   Updated: 2020/10/06 12:43:32 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Prints all the environnement variables of the shell on stdout.
** Doesn't take arguments neither options.
*/
int		builtin_env(char **args, char **env)
{
	if (*(args + 1)) //expected only env in **args >> so args[1] should be NULL (args is **char NULL terminated)
		return (error_msg("env: doesn't take options or arguments\n", 1));
	while (env && *env)
	{
		ft_printf("%s\n", *env); //print each env variable on stdout;
		env++;
	}
	return (0);
}