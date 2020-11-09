/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cdsplit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentin <corentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 13:37:11 by corentin          #+#    #+#             */
/*   Updated: 2020/10/27 13:39:59 by corentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cdminishell.h"

static	int			issep(char c, char d)
{
	if (c == d || c == '\0')
		return (1);
	return (0);
}

static	int			wordsnbr(char const *s, char c)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (issep(s[i + 1], c) == 1
				&& issep(s[i], c) == 0)
			count++;
		i++;
	}
	return (count);
}

static	void		copynosep(char *dest, char const *src, char c)
{
	int		i;

	i = 0;
	while (issep(src[i], c) == 0)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

static	int			split_cut(char **split, char const *s, char c)
{
	int		i;
	int		j;
	int		w;

	w = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (issep(s[i], c) == 1)
			i++;
		else
		{
			j = 0;
			while (issep(s[i + j], c) == 0)
				j++;
			if (!(split[w] = malloc(sizeof(char) * j + 1)))
				return (w);
			copynosep(split[w], &s[i], c);
			i = i + j;
			w++;
		}
	}
	return (-1);
}

char				**ft_cdsplit(char const *s, char c)
{
	char	**split;
	int		count;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	count = wordsnbr(s, c);
	if (!(split = malloc(sizeof(char *) * (count + 1))))
		return (NULL);
	split[count] = 0;
	count = split_cut(split, s, c);
	if (count >= 0)
	{
		while (i < count)
			free(split[i++]);
		free(split);
		return (NULL);
	}
	return (split);
}
