/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 15:34:05 by llefranc          #+#    #+#             */
/*   Updated: 2020/10/08 17:02:47 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//checker si c'est un directory et s'il existe bien
//cd sans rien utilise la varible HOME pour revenir a ce dossier
//penser aussi a gerer le tilde <> HOME >> si elle est unset on ne peut plus faire cd sans arguments
//variable OLDPWD >> dernier pwd connu avant de changer
//mettre a jour la variable PWD >> si elle est unset, cd marche encore et ne s'en occupe plus
//gerer le ./..

//quand cd est appelé il met a jour les valeurs de PWD et OLDPWD si celles ci existent

//gerer chemin relatif et chemin absolu
//gerer le cas ou le cd est a la fin d'un pipe 

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

int		builtin_cd(char **args, char **env)
{
	char	*oldpwd;	//for updating OLDPWD env var
	char	*path;		//path will be send to chdir func
	
	if (args && !args[1]) //if no arg, cd use HOME environnement variable
	{
		if (!(path = copy_home_var(env)))
			return (error_msg("minishell: cd: HOME not set\n", 1));
	}
	else if (!(path = getcwd(NULL, 0)))
		return (error_msg("minishell: cd: getcwd failed\n", 1));
	if (!(oldpwd = getcwd(NULL, 0)))
	{
		free(path);
		return (error_msg("minishell: cd: getcwd failed\n", 1));
	}
	
	REPRENDRE ICI
	ft_printf("path = |%s|, oldpwd = |%s|\n", path, oldpwd);
	free(path);
	free(oldpwd);
	return (0);
}