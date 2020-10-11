/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 15:34:05 by llefranc          #+#    #+#             */
/*   Updated: 2020/10/11 14:53:04 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		len_var_name(char *var);
//>> cd sans rien utilise la varible HOME pour revenir a ce dossier
//>> penser aussi a gerer le tilde <> HOME >> si elle est unset on ne peut plus faire cd sans arguments

//variable OLDPWD >> dernier pwd connu avant de changer

//>> gerer chemin relatif et chemin absolu >> commence par un / ou non
//>> gerer le ./.. >> .. on enleve le /xxx/ precedent, . on enleve /./

//checker si c'est un directory et s'il existe bien
//appeler la commande pour changer de repertoire
//mettre a jour la variable PWD >> si elle est unset, cd marche encore et ne s'en occupe plus

//quand cd est appelé il met a jour les valeurs de PWD et OLDPWD si celles ci existent

//gerer le cas ou le cd est a la fin d'un pipe 

//>>gerer le cas de cd ""

//gerer le cas de cd //Users etc >> le double slash >>implementer global_path a la place de path

//rajouter le tilde dans cd

// bash-3.2$ cd s
// bash: cd: s: No such file or directory
// bash-3.2$ touch test
// bash-3.2$ cd test
// bash: cd: test: Not a directory

// Change the current working directory to directory. If directory is not supplied, the value of the HOME
// shell variable is used. Any additional arguments following directory are ignored.
// If ‘..’ appears in directory, it is processed by removing the immediately preceding pathname component,
// back to a slash or the beginning of directory.
// The return status is zero if the directory is successfully changed, non-zero otherwise.

// PENSER A TESTER >> les leaks, les unset de pwd oldpwd alterné entre eux, le fait
//que oldpwd s'appuie bine sur pwd quand celui-ci est present, les messages d'erreur.
//Bien tester le comportement de cd

//voir aussi le cas des liens symboliques, bien actualiser cd et pwd

/*
** Searches for HOME environnement variable and returns a *char with only the
** path. If HOME isn't set, returns NULL.
*/
char	*copy_home_var(char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env[i] && ft_strncmp("HOME", env[i], 4))
		i++;
	if (!env[i])	//HOME variable doesn't exist
		return (NULL);
	if (!(tmp = ft_strdup(env[i])))
		return (NULL);
	i = 0;
	while (tmp[i] && tmp[i] != '"')
		i++;
	ft_strlcpy(tmp, tmp + i + 1, ft_strlen(tmp + i + 1)); //removing HOME=" and the last "
	return (tmp);
}

/*
** Transforms the relative path into absolute path.
*/
char	*add_absolute_path_to_relative(char *arg)
{
	char	*pwd;
	char	*tmp;

	if (!(pwd = getcwd(NULL, 0)))
		return (NULL);
	tmp = pwd;
	if (!(pwd = ft_strjoin(pwd, "/")))
		return (NULL);
	free(tmp);
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
void	remove_multiple_slash(char *path)
{
	int		i;

	if (!path[0]) //case cd ""
		return ;
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
}

/*
** Transforms path into something that can be used by chdir function. Handles
** '.', '..' and multiple slashs. Also transforms relative path into absolute
** path.
*/
char	*treat_relative_path(char *arg)
{
	char	*path;

	path = NULL;
	if (arg[0] != '/') //if relative path
	{
		if (!(path = add_absolute_path_to_relative(arg)))
			return (NULL);
	}
	else if (!(path = ft_strdup(arg))) //if absolute
		return (NULL);
	remove_multiple_slash(path);
	if (!(path = remove_dots(path)))
		return (NULL);
	return (path);
}

/*
** Prints an error message with either path or $HOME, and returns 1.
*/
int		error_no_file(char *arg, char **env, char *path)
{
	int		i;

	i = 0;
	arg ? ft_printf("minishell: cd: %s: No such file or directory\n", arg) : 0;
	if (!arg)
	{
		while (env[i] && (ft_strncmp("HOME", env[i], 4) || 
			len_var_name("HOME") != len_var_name(env[i]))) //until we match an existing variable
			i++;
		ft_printf("minishell: cd: %s: No such file or directory\n", env[i] + 5);
	}
	free(path);
	return (FAILURE);
}

/*
** Prints an error message with either path or $HOME, and returns 1.
*/
int		error_not_dir(char *arg, char **env, char *path)
{
	int		i;

	i = 0;
	arg ? ft_printf("minishell: cd: %s: Not a directory\n", arg) : 0;
	if (!arg)
	{
		while (env[i] && (ft_strncmp("HOME", env[i], 4) || 
			len_var_name("HOME") != len_var_name(env[i]))) //until we match an existing variable
			i++;
		ft_printf("minishell: cd: %s: Not a directory\n", env[i] + 5);
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
	return (SUCESS);
}

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

int		update_env_pwd_oldpwd(char *path, char **env)
{
	int		i;
	int		j;
	char	*oldpwd;

	i = find_var_in_env("PWD", env);
	j = find_var_in_env("OLDPWD", env);
	//OLDPWD
	if (env[j] && env[i] && update_env("OLDPWD=", &env[i][4], env, j)) //copying $PWD in $OLDPWD if both exist
		return (FAILURE);
	else if (env[j] && !env[i]) //$PWD missing
	{
		if (!(oldpwd = getcwd(NULL, 0)))
			return (FAILURE);
		if (update_env("OLDPWD=", oldpwd, env, j))
		{
			free(oldpwd);
			return (FAILURE);
		}
		free(oldpwd);
	}
	//PWD
	//peut etre fiare ici avec getcwd
	i = 0;
	while (path[i])
		i++;
	if (i > 2 && path[i - 1] == '/')	//removing the shlash at the end if it exist
		path[i - 1] = '\0';				//except when path is '/' or '//
	i = find_var_in_env("PWD", env);
	if (env[i] && update_env("PWD=", path, env , i)) //if $HOME var exists we update it
		return (FAILURE);
	i = 0;
	return (SUCESS);
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
	return (SUCESS);
}

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
		if (!(path = copy_home_var(env)))
			return (error_msg("minishell: cd: HOME not set\n", FAILURE));
	}
	else if (!(path = treat_relative_path(args[1]))) //modifying path for use in lstat / chdir functions
		return (error_msg("minishell: cd: malloc failed\n", FAILURE));
	ft_printf("path = |%s|\n", path);
	if (lstat(path, &info_file) == -1) //checking if path exist
		return (error_no_file(args[1], env, path));
	// if ((info_file.st_mode & S_IFMT) != S_IFDIR) //checking if the file is a directory
	// 	return (error_not_dir(args[1], env, path));
	if (chdir(path) == -1)
		return (error_not_dir(args[1], env, path));
	if (update_env_pwd_oldpwd(path, env))
		return (cd_error_need_free("minishell: cd: malloc failed\n", path));

	free(path);
	return (SUCESS);
}