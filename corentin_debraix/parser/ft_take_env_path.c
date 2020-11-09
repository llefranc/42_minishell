/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_take_env_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 23:10:00 by corentindeb       #+#    #+#             */
/*   Updated: 2020/11/08 23:46:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cdminishell.h"

/*
**	Incremente k dans la fonction ft_take_env_path.
*/

void	ft_take_env_incre_k(int z, int *k, t_sh *sh)
{
	if (sh->onemoredollar == 1)
	{
		while (sh->command[z][*k] && sh->command[z][*k] != '$'
			&& sh->command[z][*k] != SPACE)
			(*k)++;
		(*k)++;
	}
	if (sh->onemoredollar == 1)
		while (sh->command[z][*k] && sh->command[z][*k] != '$'
			&& sh->command[z][*k] != '=' && sh->command[z][*k] != -7
			&& sh->command[z][*k] != -6 && sh->command[z][*k] != SPACE
			&& sh->command[z][*k] != '/' && sh->command[z][*k] != -5)
			(*k)++;
	if (sh->onemoredollar == 0)
		while (sh->command[z][*k] && sh->command[z][*k] != '='
			&& sh->command[z][*k] != -7 && sh->command[z][*k] != -6
			&& sh->command[z][*k] != SPACE && sh->command[z][*k] != '/'
			&& sh->command[z][*k] != -5)
			(*k)++;
}

/*
**	Incremente u dans la fonction ft_take_env_path.
*/

int		ft_take_env_incr_u(int z, t_sh *sh)
{
	int u;

	u = 0;
	while (sh->command[z][u] && sh->command[z][u] != '$')
		u++;
	return (u);
}

/*
**	free old command in ft_take_env_path.
*/

void	ft_take_env_free(int z, char *newstr, t_sh *sh)
{
	char *tmp;

	tmp = NULL;
	tmp = sh->command[z];
	sh->command[z] = newstr;
	free(tmp);
}

/*
** Replace the $PATH by the ENV PATH if it exists.
*/

void	ft_take_env_path(t_sh *sh, int z, int i)
{
	int		k;
	int		j;
	int		u;
	char	*newstr;

	j = 0;
	newstr = NULL;
	sh->onemoredollar = 0;
	sh->cmpvar = 1;
	ft_onemore_dollar(sh, z);
	u = ft_take_env_incr_u(z, sh);
	k = u;
	ft_take_env_incre_k(z, &k, sh);
	while (sh->copyenv[i][j] && sh->copyenv[i][j] != '=')
		j++;
	j++;
	newstr = malloc(sizeof(char) * (u + ((ft_cdstrlen(sh->command[z])) - k)
			+ ((ft_cdstrlen(sh->copyenv[i])) - j) + 1));
	newstr = ft_cdstrncpy(newstr, sh->command[z], u);
	newstr = ft_cdstrcat(newstr, sh->copyenv[i] + j);
	newstr = ft_cdstrcat(newstr, sh->command[z] + k);
	ft_take_env_free(z, newstr, sh);
}
