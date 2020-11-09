/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 23:51:56 by user42            #+#    #+#             */
/*   Updated: 2020/11/08 23:52:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cdminishell.h"

/*
**	Si >>> ou plus sur une ligne, renvoie syntax error.
*/

void	ft_lexer_syntax_chevron(int i, char *line, t_sh *sh)
{
	int nb_bsl;

	nb_bsl = 0;
	if (i > 0 && line[i - 1] == BSLASH)
	{
		nb_bsl = ft_count_backslash(line, i);
		if (nb_bsl % 2 == 0)
			if (line[i + 1] == '>' && line[i + 2] == '>')
				ft_putsyntax_fd("bash: syntax error_lexer 4", sh, 2);
	}
	else if (line[i + 1] == '>' && line[i + 2] == '>')
		ft_putsyntax_fd("bash: syntax error_lexer 5", sh, 2);
}

/*
**	si separator en fin de line alors syntax error.
*/

void	ft_lexer_syntax_end(char *line, t_sh *sh)
{
	int nb_bsl;

	nb_bsl = 0;
	if (ft_cdstrlen(line) - 1 > 0 && line[ft_cdstrlen(line) - 2] == BSLASH)
	{
		nb_bsl = ft_count_backslash(line, ft_cdstrlen(line) - 1);
		{
			if (nb_bsl % 2 == 0)
				ft_putsyntax_fd("bash: syntax error_lexer 6", sh, 2);
		}
	}
	else
		ft_putsyntax_fd("bash: syntax error_lexer 7", sh, 2);
}

/*
**	check des syntax error en plein milieu d'une commande.
*/

void	ft_lexer_syntax_middle(int i, char *line, t_sh *sh)
{
	int nb_bsl;

	nb_bsl = 0;
	if (i > 0 && line[i - 1] == BSLASH)
	{
		nb_bsl = ft_count_backslash(line, i);
		if (nb_bsl % 2 == 0)
			ft_lexer_sep_errors(sh, line, i);
	}
	else
		ft_lexer_sep_errors(sh, line, i);
}

/*
**	si nb impair de bslash avant un $ alors
**	je le tranforme pour pas mettre la path.
*/

char	*ft_lexer_escape_dollar(int i, char *line)
{
	int nb_bsl;

	nb_bsl = 0;
	if (i > 0 && line[i - 1] == BSLASH)
	{
		nb_bsl = ft_count_backslash(line, i);
		if (nb_bsl % 2 == 1)
			line[i] = -4;
	}
	return (line);
}

/*
**	Si space non echappé alors transfo en -2.
*/

char	*ft_lexer_nonescape_space(int i, char *line)
{
	int nb_bsl;

	nb_bsl = 0;
	if (i > 0 && line[i - 1] == BSLASH)
	{
		nb_bsl = ft_count_backslash(line, i);
		if (nb_bsl % 2 == 0)
			line[i] = -2;
	}
	else
		line[i] = -2;
	return (line);
}
