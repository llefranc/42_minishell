/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 23:51:12 by user42            #+#    #+#             */
/*   Updated: 2020/11/08 23:51:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cdminishell.h"

/*
**	La magnifique forêt de if...
**	L'important c'est que ca fonctionne (lol)
*/

char	*ft_lexer_forest(int i, char *line, t_sh *sh)
{
	if (line[i] == SQUOTES && sh->dqflag == 0)
		line = ft_lexer_squotes(i, line, sh);
	if (line[i] == DQUOTES && sh->sqflag == 0)
		line = ft_lexer_dquotes(i, line, sh);
	if (sh->sqflag == 0 && sh->dqflag == 0)
		ft_lexer_syntax_start(line, sh);
	if (line[i] == '>' && sh->sqflag == 0 && sh->dqflag == 0)
		ft_lexer_syntax_chevron(i, line, sh);
	if ((ft_sepcomp(line[ft_cdstrlen(line) - 1], "|<>()\\", 6) == 1)
		&& sh->sqflag == 0 && sh->dqflag == 0 && sh->syntaxerror == 0)
		ft_lexer_syntax_end(line, sh);
	if ((ft_sepcomp(line[i], "|<>;", 4) == 1) && sh->sqflag == 0
		&& sh->dqflag == 0 && sh->syntaxerror == 0)
		ft_lexer_syntax_middle(i, line, sh);
	if (line[i] == '$' && sh->sqflag != 0)
		line[i] = -4;
	return (line);
}

/*
** Le lexer analyse la chaine et la prepare pour le parser.
*/

char	*ft_lexer(char *line, t_sh *sh)
{
	int i;

	i = -1;
	while (line[++i] && sh->syntaxerror == 0)
	{
		line = ft_lexer_forest(i, line, sh);
		if (line[i] == '$' && sh->sqflag == 0 && sh->dqflag == 0)
			line = ft_lexer_escape_dollar(i, line);
		if (line[i] == '$' && sh->dqflag != 0)
			line = ft_lexer_escape_dollar(i, line);
		if (line[i] == SPACE && sh->sqflag == 0 && sh->dqflag == 0)
			line = ft_lexer_nonescape_space(i, line);
		if (line[i] == SEMICOLON && sh->sqflag == 0 && sh->dqflag == 0)
			line = ft_lexer_nonescape_semicolon(i, line);
		if ((ft_sepcomp(line[i], "|<>", 3) == 1)
			&& sh->sqflag == 0 && sh->dqflag == 0)
			line = ft_lexer_nonescape_sep(&i, line);
	}
	if (sh->sqflag == 1 || sh->dqflag == 1)
	{
		ft_putsyntax_fd("bash: syntax error_lexer 8", sh, 2);
		return (NULL);
	}
	else
		return (line);
}
