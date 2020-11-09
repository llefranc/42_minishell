/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cditoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codebrai <codebrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 14:43:03 by codebrai          #+#    #+#             */
/*   Updated: 2020/10/28 14:45:56 by codebrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cdminishell.h"

static	int			getdigits(long n)
{
	int		dig;

	dig = 0;
	if (n == 0)
		dig++;
	if (n < 0)
	{
		n = n * -1;
		dig++;
	}
	while (n > 0)
	{
		n = n / 10;
		dig++;
	}
	return (dig);
}

char				*ft_cditoa(int n)
{
	char	*str;
	long	nb;
	int		i;

	nb = n;
	i = getdigits(nb);
	if (!(str = (char*)malloc(sizeof(char) * i + 1)))
		return (NULL);
	str[i--] = '\0';
	if (nb == 0)
	{
		str[0] = 48;
		return (str);
	}
	if (nb < 0)
	{
		str[0] = '-';
		nb = nb * -1;
	}
	while (nb > 0)
	{
		str[i--] = 48 + (nb % 10);
		nb = nb / 10;
	}
	return (str);
}
