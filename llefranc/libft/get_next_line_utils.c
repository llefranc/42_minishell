/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:09:37 by llefranc          #+#    #+#             */
/*   Updated: 2020/03/09 13:13:06 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

void	ft_lstadd_back_gnl(t_list **alst, t_list *new)
{
	if (!alst)
		return ;
	if (!(*alst))
		*alst = new;
	else
	{
		while ((*alst)->next)
			alst = &(*alst)->next;
		(*alst)->next = new;
	}
}

t_list	*ft_lstnew_gnl(int fd, char *content)
{
	t_list	*new;

	if (!(new = malloc(sizeof(*new))))
		return (NULL);
	new->fd = fd;
	new->content = content;
	new->next = NULL;
	return (new);
}

char	*ft_strdup_gnl(char *s1, size_t len)
{
	char	*strcpy;

	strcpy = NULL;
	if (!(strcpy = malloc(sizeof(*s1) * (len + 1))))
		return (NULL);
	len = 0;
	while (s1[len])
	{
		strcpy[len] = s1[len];
		len++;
	}
	strcpy[len] = '\0';
	return (strcpy);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		len;
	int		temp;
	int		i;
	char	*str;

	len = 0;
	temp = 0;
	i = 0;
	while (s1 != NULL && s1[len])
		len++;
	while (s2 != NULL && s2[temp])
		temp++;
	len += temp;
	if ((s1 == NULL && s2 == NULL) || !(str = malloc(sizeof(*str) * (len + 1))))
		return (NULL);
	temp = -1;
	while ((++temp + i) < len && s1 != NULL && s1[temp])
		str[temp] = s1[temp];
	i--;
	while ((temp + ++i) < len && s2 != NULL && s2[i])
		str[temp + i] = s2[i];
	str[temp + i] = 0;
	free(s1);
	free(s2);
	return (str);
}

char	*ft_substr_gnl(char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	lentemp;

	i = 0;
	lentemp = 0;
	if (!s)
		return (NULL);
	while (s[i])
		i++;
	i = (i < start) ? 1 : 0;
	while (!i && s[start + lentemp] && lentemp < len)
		lentemp++;
	if (!(str = malloc(sizeof(*str) * (len + 1))))
		return (NULL);
	ft_memset_gnl(str, 0, len + 1);
	i = 0;
	while (i < lentemp && s[(size_t)start + i])
	{
		str[i] = s[(size_t)start + i];
		i++;
	}
	str[i] = 0;
	return (str);
}
