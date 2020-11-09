/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_doublearray.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentin <corentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 13:49:10 by corentin          #+#    #+#             */
/*   Updated: 2020/10/27 13:49:12 by corentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cdminishell.h"

void	ft_free_doublearray(char **semicolon)
{
	int i;

	i = -1;
	while (semicolon[++i])
		free(semicolon[i]);
	free(semicolon);
}
