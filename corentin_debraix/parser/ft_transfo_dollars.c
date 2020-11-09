/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_transfo_dollars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 23:49:40 by user42            #+#    #+#             */
/*   Updated: 2020/11/08 23:49:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cdminishell.h"

void	ft_transfo_dollars(t_sh *sh)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (sh->command[i])
	{
		j = 0;
		while (sh->command[i][j])
		{
			if (sh->command[i][j] == -4)
				sh->command[i][j] = '$';
			j++;
		}
		i++;
	}
}
