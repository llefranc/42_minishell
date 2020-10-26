/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:59:06 by llefranc          #+#    #+#             */
/*   Updated: 2020/03/09 13:12:29 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

void	*ft_memset_gnl(void *b, int c, size_t len)
{
	size_t		i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

int		initchain(t_list **first, t_list *fdelem, char **line, int fd)
{
	char	buffer[BUFFER_SIZE + 1];

	ft_memset_gnl(buffer, 0, BUFFER_SIZE + 1);
	if (BUFFER_SIZE < 1 || !line || read(fd, buffer, 0) == -1)
		return (-1);
	fdelem = *first;
	if (!(*first))
	{
		if (!read(fd, buffer, BUFFER_SIZE))
			return (0);
		*first = ft_lstnew_gnl(fd, ft_strdup_gnl(buffer, BUFFER_SIZE));
		return (1);
	}
	while (fdelem->next && fdelem->fd != fd)
		fdelem = fdelem->next;
	if (fdelem->fd == fd)
		return (1);
	if (!read(fd, buffer, BUFFER_SIZE))
		return (0);
	fdelem->next = ft_lstnew_gnl(fd, ft_strdup_gnl(buffer, BUFFER_SIZE));
	return (1);
}

int		findline(t_list *elem, char **line, size_t len)
{
	char	*tmp;

	while (1)
	{
		len = 0;
		while (elem->content[len] != '\n' && elem->content[len] != '\0')
			len++;
		if (!(*line = ft_strjoin_gnl(*line, ft_substr_gnl(elem->content, 0, len))))
			return (-1);
		if (elem->content[len] == '\n')
		{
			if (!(tmp = ft_substr_gnl(elem->content, len + 1, BUFFER_SIZE)))
				return (-1);
			free(elem->content);
			elem->content = tmp;
			return (1);
		}
		else
		{
			ft_memset_gnl(elem->content, 0, BUFFER_SIZE + 1);
			if (!read(elem->fd, elem->content, BUFFER_SIZE))
				return (0);
		}
	}
	return (1);
}

void	ft_delone_gnl(t_list **first, t_list *elem)
{
	t_list *tmp;

	tmp = *first;
	if (*first == elem)
	{
		*first = elem->next;
		free(elem->content);
		free(elem);
		return ;
	}
	while (tmp && tmp->next != elem)
		tmp = tmp->next;
	tmp->next = elem->next;
	free(elem->content);
	free(elem);
}

int		get_next_line(int fd, char **line)
{
	static t_list	*first;
	t_list			*fdelem;
	int				readret;
	size_t			len;

	len = 0;
	fdelem = NULL;
	readret = initchain(&first, fdelem, line, fd);
	if (readret == 0)
	{
		if (!(*line = malloc(sizeof(*line) * 1)))
			return (-1);
		(*line)[0] = 0;
		return (readret);
	}
	else if (readret == -1)
		return (-1);
	*line = NULL;
	fdelem = first;
	while (fdelem && fdelem->fd != fd)
		fdelem = fdelem->next;
	readret = findline(fdelem, line, len);
	if (readret < 1)
		ft_delone_gnl(&first, fdelem);
	return (readret);
}
