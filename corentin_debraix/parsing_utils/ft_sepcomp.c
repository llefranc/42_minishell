/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sepcomp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentin <corentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 13:50:03 by corentin          #+#    #+#             */
/*   Updated: 2020/10/27 13:50:04 by corentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cdminishell.h"

int		ft_sepcomp(char c, char *s2, unsigned int n)
{
	unsigned int i;

	i = 0;
	while (s2[i])
	{
		if (c == '\0' || s2[i] == '\0')
			break ;
		if (c == s2[i])
			return (1);
		i++;
	}
	if (i + 1 > n)
		return (0);
	return (0);
}
