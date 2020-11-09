/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_backslash.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 23:54:40 by user42            #+#    #+#             */
/*   Updated: 2020/11/08 23:54:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cdminishell.h"

int		ft_count_backslash(char *line, int i)
{
	int j;

	j = 1;
	while (i - j >= 0 && line[i - j] == BSLASH)
		j++;
	j = j - 1;
	return (j);
}

int		ft_count_backslash2(char *line, int i)
{
	int j;

	j = 1;
	while (i - j >= 0 && (line[i - j] == BSLASH || line[i - j] == -5))
		j++;
	j = j - 1;
	return (j);
}
