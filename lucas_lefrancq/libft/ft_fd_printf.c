/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd_printf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 16:28:27 by lucas          #+#    #+#             */
/*   Updated: 2020/10/19 11:24:37 by lucas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Lance la fonction check de la chaine. Si aucune erreur, lance le print
** de la chaine.
*/

int		ft_fd_printf(int fd, const char *str, ...)
{
	va_list	ap;
	int		count;

	va_start(ap, str);
	if (!str_check(str))
		return (-1);
	count = fd_str_print(fd, str, ap);
	va_end(ap);
	return (count);
}

/*
** Avance le long de la chaine et remplit le buffer au fur et a mesure si
** ce sont des chars normaux ou double %%. Si conversion, appelle la fonc
** conv. Reset et print le buffer a chaque fois que l'on arrive a la fin
** de celui-ci ou juste avant de sortir de la boucle quand on arrive a la
** fin de str.
*/

int		fd_str_print(int fd, const char *str, va_list ap)
{
	int		s;
	t_elem	par;

	s = 0;
	init_struct(&par, 1);
	while (str[s])
	{
		if (str[s] == '%')
			str_conv(str, &par, ap, &s);
		else
		{
			(par.b_wri)[(par.bw)++] = str[s++];
			par.count++;
		}
		if (par.bw == BUFF_SIZE || (!str[s] && par.bw))
			fd_buf_pri_res(fd, &par);
	}
	return (par.count);
}

/*
** Permet de write le buffer, le memset de '\0' et de remettre l'index
** au debut de la chaine.
*/

void	fd_buf_pri_res(int fd, t_elem *par)
{
	write(fd, par->b_wri, par->bw);
	ft_memset(par->b_wri, 0, BUFF_SIZE + 1);
	par->bw = 0;
}
