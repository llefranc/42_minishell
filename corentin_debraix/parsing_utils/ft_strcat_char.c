/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 13:50:35 by corentin          #+#    #+#             */
/*   Updated: 2020/11/04 20:02:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cdminishell.h"

char		*ft_strcat_char(char *dest, char c)
{
	int i;

	i = 0;
	while (dest[i])
		i++;
	dest[i] = c;
	dest[i + 1] = '\0';
	return (dest);
}
