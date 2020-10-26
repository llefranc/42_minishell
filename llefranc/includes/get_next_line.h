/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:01:42 by llefranc          #+#    #+#             */
/*   Updated: 2020/03/09 13:11:05 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define BUFFER_SIZE 1024

typedef struct		s_list
{
	int				fd;
	char			*content;
	struct s_list	*next;
}					t_list;

void				*ft_memset_gnl(void *b, int c, size_t len);
int					initchain(t_list **first, t_list *fdelem,
							char **line, int fd);
int					findline(t_list *elem, char **line, size_t len);
int					get_next_line(int fd, char **line);
void				ft_delone_gnl(t_list **first, t_list *elem);

void				ft_lstadd_back_gnl(t_list **alst, t_list *new);
t_list				*ft_lstnew_gnl(int fd, char *content);
char				*ft_strdup_gnl(char *s1, size_t len);
char				*ft_strjoin_gnl(char *s1, char *s2);
char				*ft_substr_gnl(char *s, unsigned int start, size_t len);

#endif
