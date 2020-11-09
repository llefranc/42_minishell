/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 11:29:09 by lucas          #+#    #+#             */
/*   Updated: 2020/02/05 19:31:55 by lucas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*strcpy;
	size_t	len;

	strcpy = NULL;
	len = 0;
	while (s1[len])
		len++;
	if (!(strcpy = malloc(sizeof(*s1) * (len + 1))))
		return (NULL);
	len = 0;
	while (s1[len])
	{
		strcpy[len] = s1[len];
		len++;
	}
	strcpy[len] = '\0';
	return (strcpy);
}
