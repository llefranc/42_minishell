/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 23:51:32 by user42            #+#    #+#             */
/*   Updated: 2020/11/08 23:51:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cdminishell.h"

/*
**	si j'ai un separateur qui n'est pas séparé par des espaces.
**	je mets des -2 entre le separateur pour mon split.
*/

char	*ft_lexer_manage_sep(char *line, int i)
{
	char *newstr;

	newstr = NULL;
	newstr = malloc(sizeof(char) * ft_cdstrlen(line) + 2 + 1);
	newstr = ft_cdstrncpy(newstr, line, i);
	newstr = ft_strcat_char(newstr, -2);
	newstr = ft_strcat_char(newstr, line[i]);
	newstr = ft_strcat_char(newstr, -2);
	newstr = ft_cdstrcat(newstr, line + (i + 1));
	return (newstr);
}

/*
**	gère les syntax errors en plein milieu d'une commande.
*/

void	ft_lexer_sep_errors(t_sh *sh, char *line, int i)
{
	char	*str;
	int		k;

	str = "|;<>";
	if (line[i + 1] == SPACE)
	{
		k = i + 1;
		while (line[k] == SPACE)
			k++;
		if (line[k] == '|' || line[k] == ';')
			ft_putsyntax_fd("bash: syntax error_lexer 1", sh, 2);
	}
	if ((line[i] == '>' && line[i + 1] == '>') ||
			(line[i] == '<' && line[i + 1] == '<'))
	{
		k = -1;
		while (str[++k])
			if (line[i + 2] == str[k])
				ft_putsyntax_fd("bash: syntax error_lexer 2", sh, 2);
	}
	if (line[i + 1] == '|' || line[i + 1] == ';')
		ft_putsyntax_fd("bash: syntax error_lexer 3", sh, 2);
}

/*
**	Sert a savoir si on se trouve dans des simples quotes.
**	Transforme la simple quote en -6.
*/

char	*ft_lexer_squotes(int i, char *line, t_sh *sh)
{
	int nb_bsl;

	nb_bsl = 0;
	if (i > 0 && line[i - 1] == BSLASH && sh->sqflag != 1)
	{
		nb_bsl = ft_count_backslash(line, i);
		if (nb_bsl % 2 == 0)
		{
			line[i] = -6;
			sh->sqflag++;
		}
	}
	else
	{
		line[i] = -6;
		sh->sqflag++;
	}
	if (sh->sqflag == 2)
		sh->sqflag = 0;
	return (line);
}

/*
**	Sert a savoir si on se trouve dans des doubles quotes.
**	Transforme la double quote en -7.
*/

char	*ft_lexer_dquotes(int i, char *line, t_sh *sh)
{
	int nb_bsl;

	nb_bsl = 0;
	if (i > 0 && line[i - 1] == BSLASH)
	{
		nb_bsl = ft_count_backslash(line, i);
		if (nb_bsl % 2 == 0)
		{
			line[i] = -7;
			sh->dqflag++;
		}
	}
	else
	{
		line[i] = -7;
		sh->dqflag++;
	}
	if (sh->dqflag == 2)
		sh->dqflag = 0;
	return (line);
}

/*
**	Verifie des syntax error basiques dès le début.
*/

void	ft_lexer_syntax_start(char *line, t_sh *sh)
{
	int k;
	int nb_bsl;

	k = 0;
	nb_bsl = 0;
	if (line[0] == ';' || line[0] == '|')
		ft_putsyntax_fd("bash: syntax error_lexer 3.1", sh, 2);
	else
	{
		while (line[k] && line[k] == SPACE)
			k++;
		if (line[k] == ';' || line[k] == '|')
		{
			if (k > 0 && line[k - 1] == BSLASH)
			{
				nb_bsl = ft_count_backslash(line, k);
				if (nb_bsl % 2 == 0)
					ft_putsyntax_fd("bash: syntax error_lexer 3.2", sh, 2);
			}
			else
				ft_putsyntax_fd("bash: syntax error_lexer 3.3", sh, 2);
		}
	}
}
