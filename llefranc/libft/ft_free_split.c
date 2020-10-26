/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 08:55:49 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/21 08:56:11 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
** Free properly the **char created by a split.
*/
void	free_split(char **split)
{
	int i;

	i = 0;
	while (split[i]) //ft_split end the **char by a NULL ptr
		free(split[i++]);
	free(split);
}
