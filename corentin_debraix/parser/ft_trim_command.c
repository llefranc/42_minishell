/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 23:08:28 by corentindeb       #+#    #+#             */
/*   Updated: 2020/11/08 23:45:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cdminishell.h"

/*
** Check si il y a un plus d'un $ dans la chaine
*/

void	ft_onemore_dollar(t_sh *sh, int z)
{
	int i;

	i = 0;
	while (sh->command[z][i] && sh->command[z][i] != '$')
		i++;
	if (sh->command[z][i] == '$')
		i++;
	while (sh->command[z][i])
	{
		if (sh->command[z][i] == '$')
			sh->onemoredollar = 1;
		i++;
	}
}

/*
**	Incremente j dans la fonction ft_trim_command.
*/

void	ft_trim_incre_j(int z, int *j, t_sh *sh)
{
	if (sh->onemoredollar == 1)
	{
		while (sh->command[z][*j] && sh->command[z][*j] != '$')
			(*j)++;
		(*j)++;
	}
	if (sh->onemoredollar == 0)
		while (sh->command[z][*j] && sh->command[z][*j] != '='
			&& sh->command[z][*j] != -7 && sh->command[z][*j] != -6)
			(*j)++;
	if (sh->onemoredollar == 1)
		while (sh->command[z][*j] && sh->command[z][*j] != '$'
			&& sh->command[z][*j] != '=' && sh->command[z][*j] != -7
				&& sh->command[z][*j] != -6)
			(*j)++;
}

/*
** Trim the command line if the $PATH does not exist in ENV.
*/

void	ft_trim_command(t_sh *sh, int z, int len)
{
	char	*tmp;
	char	*newstr;
	int		j;

	tmp = NULL;
	newstr = NULL;
	j = 0;
	sh->onemoredollar = 0;
	ft_onemore_dollar(sh, z);
	newstr = malloc(sizeof(char)
		* ((ft_cdstrlen(sh->command[z]) - (len + 1) + 1)));
	while (sh->command[z][j] && sh->command[z][j] != '$')
		j++;
	newstr = ft_cdstrncpy(newstr, sh->command[z], j);
	ft_trim_incre_j(z, &j, sh);
	newstr = ft_cdstrcat(newstr, sh->command[z] + j);
	tmp = sh->command[z];
	sh->command[z] = newstr;
	free(tmp);
}
