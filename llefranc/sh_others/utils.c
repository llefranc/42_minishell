/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 12:28:48 by llefranc          #+#    #+#             */
/*   Updated: 2020/10/20 17:29:12 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		find_var_in_env(char *var, char **env); //export.c

/*
** Prints an error message on stdout and returns NULL.
*/
void	*error_msg_ptr(char *msg, void *ptr)
{
	ft_fd_printf(STDERR_FILENO, "minishell: %s", msg);
	return (ptr);
}

/*
** Prints an error message on stdout and returns the error value.
*/
int		error_msg(char *msg, int return_value)
{
	ft_fd_printf(STDERR_FILENO, "minishell: %s", msg);
	return (return_value);
}

/*
** Allow to keep tracks of $PWD even if $PWD is unset. Needed for the case of
** //tmp because getcwd function will return /tmp, it's the only way to save //.
*/
int		init_global_path(char **env)
{
	int		i;

	i = 0;
	if (!global_path) //if global_path == NULL, global_path need to be initialize
	{
		i = find_var_in_env("PWD", env);
		if (!env[i]) //if $PWD is unset
		{
			if (!(global_path = getcwd(NULL, 0)))
				return (FAILURE);
		}
		else if (!(global_path = ft_strdup(&env[i][4]))) //starting after PWD=
			return (FAILURE);
	}
	return (SUCCESS);
}

/*
** Allow to keep tracks of $HOME even if $HOME is unset. Needed for the case of
** cd ~, because it works even if $HOME is unset.
*/
int		init_global_home(char **env)
{
	int		i;

	i = 0;
	if (!global_home) //if global_home == NULL, global_home need to be initialize
	{
		i = find_var_in_env("HOME", env);
		if (!env[i]) //if $HOME is unset
		{
			if (!(global_home = ft_strdup("/")))
				return (FAILURE);
		}
		else if (!(global_home = ft_strdup(&env[i][5]))) //starting after HOME=
			return (FAILURE);
	}
	return (SUCCESS);
}