/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_and_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 23:54:20 by user42            #+#    #+#             */
/*   Updated: 2020/11/08 23:54:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cdminishell.h"

void	ft_cdsplit_and_free(t_sh *sh, char *semicolon)
{
	char	**tmp;
	int		k;

	k = -1;
	tmp = NULL;
	tmp = sh->command;
	sh->command = ft_cdsplit(semicolon, -2);
	if (tmp != NULL)
	{
		while (tmp[++k])
			free(tmp[k]);
		free(tmp);
	}
}
