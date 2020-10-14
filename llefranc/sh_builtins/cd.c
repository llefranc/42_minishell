/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 15:34:05 by llefranc          #+#    #+#             */
/*   Updated: 2020/10/14 17:12:42 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		len_var_name(char *var);

/*
** Returns the index of var in environnement array.
*/
int		find_var_in_env(char *var, char **env)
{
	int		i;

	i = 0;
	while (env[i] && (ft_strncmp(var, env[i], ft_strlen(var)) || 
		len_var_name(var) != len_var_name(env[i]))) //until we match an existing variable
		i++;
	return (i);
}

/*
** Prints an error message with either path or $HOME, frees path and returns 1.
*/
int		error_no_file(char *arg, char **env, char *path, char *cmd)
{
	int		i;

	i = 0;
	arg ? ft_printf("minishell: %s: %s: No such file or directory\n", cmd, arg) : 0;
	if (!arg)
	{
		i = find_var_in_env("HOME", env);
		ft_printf("minishell: %s: %s: No such file or directory\n", cmd, env[i] + 5);
	}
	free(path);
	return (FAILURE);
}

/*
** Prints an error message with either path or $HOME, frees path and returns 1.
*/
int		error_not_dir(char *arg, char **env, char *path, char *cmd)
{
	int		i;

	i = 0;
	arg ? ft_printf("minishell: %s: %s: Not a directory\n", cmd, arg) : 0;
	if (!arg)
	{
		i = find_var_in_env("HOME", env);
		ft_printf("minishell: %s: %s: Not a directory\n", cmd, env[i] + 5);
	}
	free(path);
	return (FAILURE);
}

/*
** Prints an error message, frees path and returns 1.
*/
int		cd_error_need_free(char *str_error, char *path)
{
	ft_printf("%s", str_error);
	free(path);
	return (FAILURE);
}

/*
** Searches for HOME environnement variable and returns a *char with only the
** path. If HOME isn't set, returns NULL.
*/
char	*copy_home_var(char **env, char *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	i = find_var_in_env("HOME", env);
	if (!env[i] || (env[i] && ft_strncmp(env[i], "HOME=", 5)))	//HOME variable doesn't exist
	{
		ft_printf("minishell: %s: malloc failed\n", cmd);
		return (NULL);
	}
	if (!(tmp = ft_strdup(env[i])))
	{
		ft_printf("minishell: %s: malloc failed\n", cmd);
		return (NULL);
	}
	ft_strlcpy(tmp, tmp + 5, ft_strlen(tmp + 5) + 1); //removing HOME=
	return (tmp);
}

/*
** Transforms the relative path into absolute path.
*/
char	*add_absolute_path_to_relative(char *pwd, char *arg)
{
	char	*tmp;

	tmp = pwd;
	if ((!(pwd[0] == '/' && pwd[1] == '\0') && !(pwd[0] == '/' && pwd[1]  //except for "cd /" or "cd //"
			== '/' && pwd[2] == '\0')) && !(pwd = ft_strjoin(pwd, "/")))
		return (NULL);
	!(pwd[0] == '/' && pwd[1] == '\0') && !(pwd[0] == '/' && pwd[1] == //except for "cd /" or "cd //"
			'/' && pwd[2] == '\0') ? free(tmp) : 0;
	tmp = pwd;
	if (!(pwd = ft_strjoin(pwd, arg)))
		return (NULL);
	free(tmp);
	return (pwd);
}

/*
** Returns a *char on the previous '/', or at the beginning of path if there
** isn't a previous '/'.
*/
int		find_prev_slash(char *path, int i)
{
	while (i > 0 && path[i] != '/')
		i--;
	if (i < 0)
		i = 0;
	return (i);
}

/*
** Ends the path with '/'.
*/
char	*add_end_slash(char *path)
{
	char	*tmp;
	int		i;

	i = 0;
	while (path[i])
		i++;
	if (!(tmp = malloc(i + 2)))
		return (NULL);
	tmp[i + 1] = '\0';
	ft_strlcpy(tmp, path, i + 1);
	tmp[i] = '/';
	free(path);
	path = tmp;
	return (path);
}

/*
** Removes . and .. from the path. For each .., removes also the directory before it.
*/
char	*remove_dots(char *path)
{
	int		i;
	int		prev_slash;

	i = -1;
	while (path[++i])
	{
		if (path[i] == '.' && path[i - 1] == '/' && (path[i + 1] == '\0' || path[i + 1] == '/'))	//remove '/.'
		{
			if (path[i + 1] == '\0' && !(path = add_end_slash(path))) //adds a '/' if /. is at the end of path
				return (NULL);
			ft_strlcpy(&path[i - 1], &path[i + 1], ft_strlen(&path[i + 1]) + 1);
			i--;
		}
	}
	i = -1;
	while (path[++i])
	{
		if (path[i] == '.' && path[i + 1] == '.' && path[i - 1] == '/' &&	//remove '/..' and the part until previous '/'
				(path[i + 2] == '\0' || path[i + 2] == '/'))
		{
			if (path[i + 2] == '\0' && !(path = add_end_slash(path))) //adds a '/' if /.. is at the end of path
				return (NULL);
			prev_slash = find_prev_slash(path, i - 2); // if /tmp/../ > returns the position of '/' before tmp
			ft_strlcpy(&path[prev_slash], &path[i + 2], ft_strlen(&path[i + 2]) + 1);
			i = prev_slash - 1;
		}
	}
	return (path);
}

/*
** Removes all the multiple slash, except for the beginning of the path : it
** be double but double only. More slash will lead to just one slash.
** Ex : //tmp > //tmp, ///tmp > /tmp.
*/
int		remove_multiple_slash(char *path)
{
	int		i;

	if (!path[0]) //case cd ""
		return (SUCCESS);
	i = 0;
	if (path[i] == '/' && path[i + 1] == '/' && path[i + 2] == '/') //if there is at least 3 slashs at beginning of path >> we keep only one
		i = -1;														//otherwise we do not treat first '/' because it can be double (only the first one !)
	while (path[++i])
	{
		if (path[i] == '/' && path[i + 1] == '/')
		{
			ft_strlcpy(&path[i], &path[i + 1], ft_strlen(&path[i + 1]) + 1);
			i--;
		}
	}
	return (SUCCESS);
}

/*
** Transforms path into something that can be used by chdir function. Handles
** '.', '..' and multiple slashs. Also transforms relative path (including ~/)
** into absolute path.
*/
char	*treat_relative_path(char *arg, char **env)
{
	int		i;
	char	*path;

	path = NULL;
	if (arg[0] != '/' && arg[0] != '~') //if relative path
	{

		if (!(path = ft_strdup(global_path)) || !(path = add_absolute_path_to_relative(path, arg)))
			return (error_msg_ptr("minishell: cd: malloc failed\n", NULL));
	}
	else if (arg[0] == '~')
	{
		if (!(path = copy_home_var(env, "cd"))) //path = $HOME
			return (NULL);
		if (arg[1] != '/' && arg[1] != '\0') //case ~ without / (ex : ~Dir >> error)
		{
			error_no_file(arg, env, path, "cd");
			return (NULL);
		}
		i = (arg[1] == '/' && path[1] != '\0') ? 1 : 0; //for cd ~/ with $HOME=/
		if (!(path = add_absolute_path_to_relative(path, arg + i + 1))) //joins $HOME value and arg without tilde
			return (error_msg_ptr("minishell: cd: malloc failed\n", NULL));
	}
	else if (!(path = ft_strdup(arg))) //if absolute
		return (error_msg_ptr("minishell: cd: malloc failed\n", NULL));
	return (path);
}

/*
** Joins var and path to create a new env variable and update env array
** (for $PWD / $OLDPWD).
*/
int		update_env(char *var, char *path, char **env, int i)
{
	char *tmp;

	if (!(tmp = ft_strjoin(var, path)))
		return (FAILURE);
	free(env[i]);
	env[i] = tmp;
	return (SUCCESS);
}

/*
** Updates $PWD and $OLDPWD if they exist.
*/
int		update_env_pwd_oldpwd(char *path, char **env)
{
	int		i;

	i = find_var_in_env("OLDPWD", env);
	if (env[i] && update_env("OLDPWD=", global_path, env, i)) //copying global_path (previous $PWD) in $OLDPWD
		return (FAILURE);	
	i = 0;
	while (path[i])
		i++;
	if (i > 2 && path[i - 1] == '/')	//removing the shlash at the end if it exist
		path[i - 1] = '\0';				//except when path is '/' or '//
	i = find_var_in_env("PWD", env);
	if (env[i] && update_env("PWD=", path, env , i)) //if $HOME var exists we update it
		return (FAILURE);
	return (SUCCESS);
}

/*
** Allow to keep tracks of $PWD even if $PWD is unset. Needed for the case of
** //tmp because getcwd function will return /tmp, it's the only way to save //.
*/
int		init_global_path(char **env)
{
	int		i;

	i = 0;
	if (!global_path) //if global_path == NULL, first launch of cd, global_path need to be initialize
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
** If no arguments, changes the working directory to $HOME if it exists.
** Otherwise changes the working directory using first argument (and ignoring
** the other ones). Handles absolute path, relative path (also with ~).
** Doesn't take any options. Returns 0 if success, 1 if failure.
*/
int		builtin_cd(char **args, char **env)
{
	char	*path;		//path will be send to chdir func
	struct stat	info_file;
	
	if (init_global_path(env))
		return (error_msg("minishell: cd: malloc failed\n", FAILURE));
	if (args && args[1] && args[1][0] == '-') //our cd doesn't handle options
        return (error_msg("minishell: cd: no options are allowed\n", FAILURE));
		
	if (args && !args[1]) //if no arg, cd use HOME environnement variable
	{
		if (!(path = copy_home_var(env, "cd")))
			return (FAILURE);
	}
	else if (!(path = treat_relative_path(args[1], env))) //we treat the argument for updating $PWD
		return (FAILURE);
	if (stat(path, &info_file) == -1) //checking if file's path / directory's path exists
		return (error_no_file(args[1], env, path, "cd"));
	if (chdir(path) == -1) //using path and not args[1] because cd can be use without argument
		return (error_not_dir(args[1], env, path, "cd"));
	if (!remove_multiple_slash(path) && !(path = remove_dots(path))) //modifying path for updating $PWD
		return (error_msg("minishell: cd: malloc failed\n", FAILURE));
	if (update_env_pwd_oldpwd(path, env))
		return (cd_error_need_free("minishell: cd: malloc failed\n", path));
	free(global_path);
	global_path = path;
	return (SUCCESS);
}