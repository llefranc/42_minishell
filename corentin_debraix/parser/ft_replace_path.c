/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 23:49:11 by user42            #+#    #+#             */
/*   Updated: 2020/11/08 23:49:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cdminishell.h"

/*
**	Manage the return value in ft_compare_var.
*/

void	ft_compare_returnvalue(int i, int c, t_sh *sh)
{
	char *tmp;
	char *newstr;
	char *itoachar;

	tmp = NULL;
	newstr = NULL;
	itoachar = NULL;
	if (sh->command[i][c] == '$' && sh->command[i][c + 1] == '?')
	{
		sh->cmpvar = 1;
		itoachar = ft_cditoa(global_ret_value);
		newstr = malloc(sizeof(char) * (ft_cdstrlen(itoachar)
				+ ft_strlen(sh->command[i]) - 2 + 1));
		newstr = ft_cdstrncpy(newstr, sh->command[i], c);
		newstr = ft_cdstrcat(newstr, itoachar);
		newstr = ft_cdstrcat(newstr, sh->command[i] + c + 2);
		tmp = sh->command[i];
		sh->command[i] = newstr;
		free(tmp);
		free(itoachar);
	}
}

/*
**	Faut bien normer dans ft_compare_var.
*/

void	ft_compare_var_cut(int i, int c, int *len, t_sh *sh)
{
	if (sh->command[i][c] == '$' && ft_isalpha(sh->command[i][c + 1])
		== 0 && sh->command[i][c + 1] != '_')
	{
		sh->command[i][c] = -4;
		sh->cmpvar = 1;
	}
	if (sh->command[i][c] == '$')
	{
		c++;
		while (sh->command[i][c] && sh->command[i][c] != '='
			&& sh->command[i][c] != -7 && sh->command[i][c] != -6
			&& sh->command[i][c] != '$' && sh->command[i][c] != SPACE
			&& sh->command[i][c] != '/' && sh->command[i][c] != -5)
		{
			c++;
			(*len)++;
		}
	}
}

/*
** This function checks if the $PATH exists in ENV.
** If the variable exists in sh->copyenv, we replace the $PATH.
** if it doesnt exist, we trim the $PATH.
*/

void	ft_compare_var(int i, int j, t_sh *sh)
{
	int k;
	int c;
	int len;

	k = -1;
	c = 0;
	len = 0;
	sh->cmpvar = 0;
	while (sh->command[i][c] && sh->command[i][c] != '$')
		c++;
	ft_compare_returnvalue(i, c, sh);
	ft_compare_var_cut(i, c, &len, sh);
	while (sh->copyenv[++k] && sh->cmpvar == 0)
		if (ft_cdstrncmp(sh->command[i] + (j + 1), sh->copyenv[k], len) == 0
			&& sh->copyenv[k][len] == '=' && sh->cmpvar == 0)
			ft_take_env_path(sh, i, k);
	if (ft_cdstrlen(sh->command[i]) == 1 && sh->command[i][0] == '$')
	{
		sh->command[i][0] = -4;
		sh->cmpvar = 1;
	}
	if (sh->cmpvar == 0)
		ft_trim_command(sh, i, len);
}

/*
** Check if there is a "$" in the command line.
** If it is true, we need to compare it with our copy of ENV.
*/

void	ft_replace_path(t_sh *sh)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (sh->command[i])
	{
		j = 0;
		while (sh->command[i][j])
		{
			if (sh->command[i][j] == '$')
			{
				ft_compare_var(i, j, sh);
				j = -1;
			}
			j++;
		}
		i++;
	}
}
