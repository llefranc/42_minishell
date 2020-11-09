/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_target_bslash.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 23:47:49 by user42            #+#    #+#             */
/*   Updated: 2020/11/08 23:48:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cdminishell.h"

/*
**	Check si on est dans des simple quotes.
*/

void	ft_target_squotes(int i, int j, t_sh *sh)
{
	int nb_bsl;

	nb_bsl = 0;
	if (j > 0 && (sh->command[i][j - 1] == BSLASH
		|| sh->command[i][j - 1] == -5) && sh->sqflag != 1)
	{
		nb_bsl = ft_count_backslash2(sh->command[i], j);
		if (nb_bsl % 2 == 0)
			sh->sqflag++;
	}
	else
		sh->sqflag++;
	if (sh->sqflag == 2)
		sh->sqflag = 0;
}

/*
**	Check si on est dans des doubles quotes.
*/

void	ft_target_dquotes(int i, int j, t_sh *sh)
{
	int nb_bsl;

	nb_bsl = 0;
	if (j > 0 && (sh->command[i][j - 1] == BSLASH
		|| sh->command[i][j - 1] == -5) && sh->dqflag != 1)
	{
		nb_bsl = ft_count_backslash2(sh->command[i], j);
		if (nb_bsl % 2 == 0)
			sh->dqflag++;
	}
	else
		sh->dqflag++;
	if (sh->dqflag == 2)
		sh->dqflag = 0;
}

/*
**	Target les backslash en negatif si on est pas
**	entre des quotes.
*/

void	ft_target_noquotes(int i, int *j, t_sh *sh)
{
	int b;

	b = *j;
	while (sh->command[i][b] == BSLASH)
	{
		sh->command[i][b] = -5;
		b += 2;
	}
	b = b - *j;
	*j += b;
	*j = *j - 1;
}

/*
**	Target les backslash en negatif si on est
**	entre des doubles quotes.
*/

void	ft_target_in_dquotes(int i, int *j, t_sh *sh)
{
	int b;

	b = *j;
	while (sh->command[i][b] == BSLASH)
	{
		if (sh->command[i][b + 1] == BSLASH || sh->command[i][b + 1] == '$'
			|| sh->command[i][b + 1] == -4 || sh->command[i][b + 1] == DQUOTES
				|| sh->command[i][b + 1] == -7)
			sh->command[i][b] = -5;
		b += 2;
	}
	b = b - *j;
	*j += b;
	*j = *j - 1;
}

/*
**	Target les backslash en negatif.
*/

void	ft_target_bslash(t_sh *sh)
{
	int i;
	int j;

	i = -1;
	sh->sqflag = 0;
	sh->dqflag = 0;
	while (sh->command[++i])
	{
		j = 0;
		while (j < ft_cdstrlen(sh->command[i]) && sh->command[i][j])
		{
			if ((sh->command[i][j] == -6 || sh->command[i][j] == SQUOTES)
				&& sh->dqflag == 0)
				ft_target_squotes(i, j, sh);
			if ((sh->command[i][j] == -7 || sh->command[i][j] == DQUOTES)
				&& sh->sqflag == 0)
				ft_target_dquotes(i, j, sh);
			if (sh->command[i][j] == BSLASH && sh->sqflag == 0
				&& sh->dqflag == 0)
				ft_target_noquotes(i, &j, sh);
			if (sh->command[i][j] == BSLASH && sh->dqflag != 0)
				ft_target_in_dquotes(i, &j, sh);
			j++;
		}
	}
}
