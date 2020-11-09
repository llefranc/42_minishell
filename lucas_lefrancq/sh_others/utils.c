/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 12:28:48 by lucas          #+#    #+#             */
/*   Updated: 2020/10/26 18:11:10 by lucas         ###   ########.fr       */
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

/*
** frees a **char and prints an error msg.
*/
int		free_new_env(char **tmp_env)
{
	free_split(tmp_env);
	return (error_msg("utils: malloc failed\n", FAILURE));
}

/*
** Initiates a new environnement with 3 variables if no environnement is sent
** to this shell (with env -i). Sets PWD variable.
*/
int		create_new_env(t_sh *sh)
{
	char	**tmp;
	char	*path;
	int		i;

	i = 0;
	if (!(tmp = malloc(sizeof(*tmp) * 6)))
		return (FAILURE);
	while (i < 6)
		tmp[i++] = NULL;
	if (!(path = getcwd(NULL, 0)))
		return (error_msg("utils: getcwd failed\n", FAILURE));
	if (!(tmp[3] = ft_strjoin("PWD=", path))) //setting pwd and the path of current directory
	{
		free(path);
		return (error_msg("utils: malloc failed\n", FAILURE));
	}
	free(path);
	if (!(tmp[0] = ft_strdup("LESSCLOSE=/usr/bin/lesspipe %s %s")))
		return (free_new_env(tmp));
	if (!(tmp[1] = ft_strdup("LESSOPEN=/usr/bin/lesspipe %s")))
		return (free_new_env(tmp));
	if (!(tmp[2] = ft_strdup("OLDPWD")))
		return (free_new_env(tmp));
	if (!(tmp[4] = ft_strdup("SHLVL=1")))   //if one malloc failed, we free
		return (free_new_env(tmp));         //the previous malloc before return
	tmp[5] = NULL;
	sh->copyenv = tmp;
	return (SUCCESS);
}
