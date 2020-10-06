/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 12:28:48 by llefranc          #+#    #+#             */
/*   Updated: 2020/10/06 14:50:32 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Prints an error message on stdout and returns the error value.
*/
int		error_msg(char *msg, int return_value)
{
	ft_printf("%s", msg);
	return (return_value);
}

// /*
// ** Compares n characters between two strings. Returns an integer greater than,
// ** equal to, or less than 0, according as the string s1 is greater than, equal
// ** to, or less than the string s2.
// */
// int     ft_strncmp(char *s1, char *s2, unsigned int n)
// {
// 	unsigned int    i;
// 	int				j;

// 	i = 0;
// 	j = 0;
// 	while (s1[i] != '\0' && s2[i] != '\0' && i < n)
// 	{
// 		if (s1[i] > s2[i])
// 			return (j = s1[i] - s2[i]);
// 		if (s1[i] < s2[i])
// 			return (j = s1[i] - s2[i]);
// 		i++;
// 	}
// 	if (s1[i] != '\0' && s2[i] == '\0' && i < n)
// 		return (j = s1[i] - s2[i]);
// 	if (s1[i] == '\0' && s2[i] != '\0' && i < n)
// 		return (j = s1[i] - s2[i]);
// 	return (0);
// }