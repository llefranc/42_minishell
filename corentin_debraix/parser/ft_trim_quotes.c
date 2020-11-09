/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 23:48:44 by user42            #+#    #+#             */
/*   Updated: 2020/11/08 23:48:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cdminishell.h"

void	ft_trim_quotes(t_sh *sh)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (sh->command[i])
	{
		j = 0;
		while (sh->command[i][j])
		{
			if (ft_cdstrchr("\xfb\xfa\xf9", sh->command[i][j]))
			{
				ft_cdstrlcpy(sh->command[i] + j, sh->command[i] + j + 1,
								ft_cdstrlen(sh->command[i] + j + 1) + 1);
				j = -1;
			}
			j++;
		}
		i++;
	}
}
