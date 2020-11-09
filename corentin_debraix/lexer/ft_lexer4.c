/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 23:52:22 by user42            #+#    #+#             */
/*   Updated: 2020/11/08 23:52:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cdminishell.h"

/*
**	Si semicolon non echappé alors transfo en -3.
*/

char	*ft_lexer_nonescape_semicolon(int i, char *line)
{
	int nb_bsl;

	nb_bsl = 0;
	if (i > 0 && line[i - 1] == BSLASH)
	{
		nb_bsl = ft_count_backslash(line, i);
		if (nb_bsl % 2 == 0)
			line[i] = -3;
	}
	else
		line[i] = -3;
	return (line);
}

/*
**	Si separator non escape, transfo en negatif (define).
**	Puis transfo autour du separator en -2 pour découper.
*/

char	*ft_lexer_transfo_sep(int i, char *line)
{
	char *tmp;

	tmp = NULL;
	if (line[i] == '|')
		line[i] = F_PIPE;
	else if (line[i] == '>')
		line[i] = F_RIGHT;
	else
		line[i] = F_LEFT;
	tmp = line;
	line = ft_lexer_manage_sep(line, i);
	free(tmp);
	return (line);
}

/*
**	Si non escape, lance la fonction ft_lexer_transo_sep
*/

char	*ft_lexer_nonescape_sep(int *i, char *line)
{
	int nb_bsl;
	int k;

	k = *i;
	nb_bsl = 0;
	if (k > 0 && line[k - 1] == BSLASH)
	{
		nb_bsl = ft_count_backslash(line, k);
		if (nb_bsl % 2 == 0)
		{
			line = ft_lexer_transfo_sep(k, line);
			*i += 2;
		}
	}
	else
	{
		line = ft_lexer_transfo_sep(k, line);
		*i += 2;
	}
	return (line);
}
