/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 15:21:55 by llefranc          #+#    #+#             */
/*   Updated: 2020/10/20 16:29:58 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		redirection(int type, char *file)
{
	int	new_fd;

	if (type == INPUT)
		if (((new_fd = open(file, O_RDONLY)) == -1) &&
				ft_fd_printf(STDERR_FILENO, "minishell: %s: No such file or directory\n", file))
			return (FAILURE);
	if (type == OUTPUT)
		if (((new_fd = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
				&& ft_fd_printf(STDERR_FILENO, "minishell: %s: file opening failed\n", file))
			return (FAILURE);
	if (type == OUTPUT_ADD)
		if (((new_fd = open(file, O_RDWR | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
				 &&ft_fd_printf(STDERR_FILENO, "minishell: %s: file opening failed\n", file))
			return (FAILURE);
	if (type == INPUT)
		dup2(new_fd, STDIN_FILENO);
	else if (type == OUTPUT || type == OUTPUT_ADD)
		dup2(new_fd, STDOUT_FILENO);
	close(new_fd);
	return (SUCCESS);
}