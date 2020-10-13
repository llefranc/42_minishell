/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_part.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 11:44:05 by llefranc          #+#    #+#             */
/*   Updated: 2020/10/13 15:43:22 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		len_var_name(char *var);
int		find_var_in_env(char *var, char **env);
char	*copy_home_var(char **env, char *cmd);
int		error_no_file(char *arg, char **env, char *path, char *cmd);
char	*add_absolute_path_to_relative(char *pwd, char *arg);
int		init_global_path(char **env);
char	*remove_dots(char *path);
int		remove_multiple_slash(char *path);

//gerer le tilde, les differentes path (ni . ni / ni ~), le relatif
//gerrer le cas de juste execve le . .. ou le ~
//gerer le cas d'execve d'un directory

// /../../../../../llefranc/Rendu/.vscode/../../../..///////////////////////////////////////////////////////////////////bin: exe: No such file or directory
// cd //../../../../../llefranc/Rendu/.vscode/../../../..///////////////////////////////////////////////////////////////////bin >>devrait pas marcher masi se lance
// a checker
int		add_absolute_path_with_path_var(char **args, char **env)
{
	int		i;

	(void)args;
	i = find_var_in_env("PATH", env);
	if (!env[i])
		return (SUCCESS); //PATH isn't set so only absolute path will be effective, we don't change the relative
	
	//remove multiple dots
	//remove multiple slash
	return (SUCCESS);
}
		// add_absolute_path_with_path_var(args, env);

//execute abvec absolute path >>>>> termine
int		execute_absolute_path(char **args, char **env)
{
	pid_t	pid;
	int		status;
	struct stat	info_file;

	pid = fork();
	if (!pid) //child process
	{
		if (stat(args[0], &info_file) == -1) //checking if path exist
		{
			ft_printf("minishell: %s: exe: No such file or directory\n", args[0]);
			exit(NOT_FIND);
		}
		if (S_ISDIR(info_file.st_mode))
		{
			ft_printf("minishell: %s: exe: is a directory\n", args[0]);
			exit(IS_A_DIREC);
		}
		if (execve(args[0], args, env) == -1)
			ft_printf("minishell: %s: exe: No such file or directory\n", args[0]);
		exit(NOT_FIND); //error code when execve doesn't find file
	}
	else if (pid < 0)
		return (error_msg("minishell: exe: fork failed\n", FAILURE));
	else //parent process
	{
		waitpid(pid, &status, 0);
		global_ret_value = WEXITSTATUS(status);
	}
	return (SUCCESS);
}

//rajoute le chemin d'acces devant en focntion de si c'est un tilde ou . / ..
int		execute_relative_path(char **args, char **env)
{
	char	*path;
	int		i;

	path = NULL;
	i = 0;
	if (args[0][0] == '~')
	{
		if (!(path = copy_home_var(env, "exe")))
			return (global_ret_value = FAILURE);
		if (args[0][1] != '/' && args[0][1] != '\0') //case ~ without / (ex : ~Dir >> error)
		{
			ft_printf("minishell: %s: command not found\n", args[0]);
			return (global_ret_value = NOT_FIND);
		}
		i = (args[0][1] == '/' && path[1] != '\0') ? 1 : 0; //for execve ~/ with $HOME=/
		if (!(path = add_absolute_path_to_relative(path, &args[0][0] + i + 1))) //joins $HOME value and arg without tilde
			return (global_ret_value = error_msg("minishell: exe: malloc failed\n", FAILURE));
		ft_printf("path = |%s|\n", path);
	}
	else
	{
		if (!(path = ft_strdup(global_path)) || !(path = add_absolute_path_to_relative(path, args[0])))
			return (global_ret_value = error_msg("minishell: exe: malloc failed\n", FAILURE));
	}
	if (!remove_multiple_slash(path) && !(path = remove_dots(path))) //modifying path for use in lstat / chdir functions
		return (global_ret_value = error_msg("minishell: cd: malloc failed\n", FAILURE));
	free(args[0]);
	args[0] = path;
	ft_printf("path = |%s|\n", path);

	execute_absolute_path(args, env);
	return (SUCCESS);
}

int		execve_part(char **args, char **env)
{
	if (init_global_path(env))
		return (global_ret_value = error_msg("minishell: cd: malloc failed\n", FAILURE));
	if (args && args[0] && args[0][0] != '/' && (args[0][0] != '.' && (args[0][1] != '.'
			&& args[0][1] != '/')) && args[0][0] != '~' && env[find_var_in_env("PATH", env)])
		ft_printf("relativepath with path var\n");
		// return (execute_relative_path_with_path_var(args, env));
	else if (args && args[0] && ((args[0][0] == '.' && (args[0][1] == '.'
			|| args[0][1] == '/')) || args[0][0] == '~'))
		return (execute_relative_path(args, env));
	else //peut etre rajouter ici les tildes . .. sans backslash
		return (execute_absolute_path(args, env));
	return (SUCCESS);
}