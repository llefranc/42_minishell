/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cdstrchr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentin <corentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 13:37:27 by corentin          #+#    #+#             */
/*   Updated: 2020/10/27 13:40:10 by corentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cdminishell.h"

char		*ft_cdstrchr(char *s, int c)
{
	char *tab;

	tab = (char *)s;
	while (*tab)
	{
		if (*tab == (char)c)
		{
			return (tab);
		}
		tab++;
	}
	if (*tab == '\0' && (char)c == '\0')
		return (tab);
	return (NULL);
}
