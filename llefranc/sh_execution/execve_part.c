/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_part.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 11:44:05 by llefranc          #+#    #+#             */
/*   Updated: 2020/10/26 17:07:02 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		find_var_in_env(char *var, char **env);                //cd.c
char	*copy_home_var(char **env, char *cmd);                 //cd.c
char	*add_absolute_path_to_relative(char *pwd, char *arg);  //cd.c

/*
** Returns 1 if there is a '/' in the string, 0 otherwise.
*/
int		there_is_a_slash(char *arg)
{
	int		i;

	i = 0;
	while (arg[i] && arg[i] != '/')
		i++;
	if (arg[i] == '/')
		return (1);
	return (0);
}

/*
** If a new sh is launched, activates a boolean that will prevent the execution
** of CTRL+C and CTRL+backslash. Reactivates the signals when sh son exits.
*/
void	new_sh_launched(char *arg)
{
	int			i;

	i = 0;
	if (new_sh_bool)
	{
		new_sh_bool = 0;
		return ;
	}
	while(arg[i])
		i++;
	while (i > 0 && arg[i - 1] != '/') //analyzing last part of exe path
		i--;
	if (!ft_strcmp(&arg[i], "minishell") || !!ft_strcmp(&arg[i], "bash"))
		new_sh_bool = 1;
}

/*
** Forks the process, and launches execve. Returns the exit code of the forked process.
*/
int		execute_absolute_path(char **args, char **env)
{
	int		status;
	int		ret_value;
	struct stat	info_file;

	pid = fork();
	ret_value = 0;
	if (!pid) //child process
	{
		if (stat(args[0], &info_file) == -1 &&
				ft_fd_printf(STDERR_FILENO, "minishell: exe: %s: No such file or directory\n", args[0]))
			exit(NOT_FOUND); //checking if path exist
		if (S_ISDIR(info_file.st_mode) &&
				ft_fd_printf(STDERR_FILENO, "minishell: exe: %s: is a directory\n", args[0]))
			exit(WRONG_FILE); //checking if it's a directory or not
		if (!(info_file.st_mode & S_IXUSR) &&
				ft_fd_printf(STDERR_FILENO, "minishell: exe: %s: Permission denied\n", args[0]))
			exit(WRONG_FILE);
		if (execve(args[0], args, env))
			exit(error_msg("exe: execve failed\n", NOT_FOUND));
	}
	else if (pid < 0) //fork failed
		return (error_msg("exe: fork failed\n", FAILURE));
	else //parent process
	{
		new_sh_launched(args[0]); //desactivating signals in parent if new sh is launched
		waitpid(pid, &status, 0); //wait until process previously created exits
		ret_value = WIFSIGNALED(status)?
			(WCOREDUMP(status) ? 131 : 130) : WEXITSTATUS(status); //130 for CTRL+C, 131 for CTRL+backslash
		new_sh_launched(args[0]); //reactivating signals
	}
	return (ret_value);
}

/*
** Launches execve for executing the command. If the relative path starts with
** ~, joins the relative path with $HOME variable if it exists before execve. 
** Returns the exit code of the forked process after execve use.
*/
int		execute_path(char **args, char **env)
{
	char	*path;
	int		i;

	path = NULL;
	i = 0;
	if (args[0][0] == '~')
	{
		if (!(path = copy_home_var(env, "exe")))
			return (FAILURE);
		if (args[0][1] != '/' && args[0][1] != '\0' && there_is_a_slash(args[0]) && //case ~ without / (ex : ~Dir >> error)
				ft_fd_printf(STDERR_FILENO, "minishell: exe: %s: No such file or directory\n", args[0]))
			i = NOT_FOUND;
		else if (args[0][1] != '/' && args[0][1] != '\0' && env[find_var_in_env("PATH", env)]
				&& (int)ft_strlen(env[find_var_in_env("PATH", env)]) > 5
				&& ft_fd_printf(STDERR_FILENO, "minishell: exe: %s: command not found\n", args[0]))
			i = NOT_FOUND;
		else if (args[0][1] != '/' && args[0][1] != '\0'
				&& ft_fd_printf(STDERR_FILENO, "minishell: exe: %s: No such file or directory\n", args[0]))
			i = NOT_FOUND;
		i == NOT_FOUND ? free(path) : 0;
		if (i == NOT_FOUND) //if error we exit the function
			return (i);
		i = (args[0][1] == '/' && path[1] != '\0') ? 1 : 0; //for execve ~/ with $HOME=/
		if (!(path = add_absolute_path_to_relative(path, &args[0][0] + i + 1))) //joins $HOME value and arg without tilde
			return (error_msg("exe: malloc failed\n", FAILURE));
		free(args[0]);
		args[0] = path;
	}
	i = execute_absolute_path(args, env); //executes the command
	return (i);
}

/*
** Tests each possible path with $PATH variable. Returns the correct one, or
** NULL if none is working.
*/
char	*get_path(char **path, char *arg, int *j)
{
	char		*full_path;
	char		*tmp;
	struct stat	info_file;

	while (path[++(*j)]) //testing each possible path
	{
		if (!(full_path = ft_strjoin(path[*j], "/")))
			return (error_msg_ptr("exe: malloc failed\n", NULL));
		tmp = full_path;
		if (!(full_path = ft_strjoin(full_path, arg)))
			return (error_msg_ptr("exe: malloc failed\n", NULL));
		free(tmp);
		if (!stat(full_path, &info_file)) //if stat == 0 the path is correct
			return (full_path);
		free(full_path);
	}
	return (NULL);
}
		
/*
** Tries all the different possibily of $PATH + argument. Executes the first
** correct path (tries from the left to the right of PATH variable).
*/
int		execute_with_path_variable(char **args, char **env)
{
	int		i;
	int		j;
	char	*full_path;
	char	**path;

	i = find_var_in_env("PATH", env); //we already checked in execve_part that $PATH existed
	j = 0;
	while (env[i][j] && env[i][j] != '=')
		j++;
	env[i][j] != '=' ? j += 1 : 0; //we split after PATH=
	if (!(path = ft_split(&env[i][j], ':')))
		return (error_msg("exe: malloc failed\n", FAILURE));
	j = -1;
	if ((full_path = get_path(path, args[0], &j))) //if one possibility of $PATH is working
	{
		free(args[0]);
		args[0] = full_path;
		global_ret_value = execute_absolute_path(args, env);
	}
	else if (!path[j] &&
			ft_fd_printf(STDERR_FILENO, "minishell: %s: command not found\n", args[0]))
		global_ret_value = NOT_FOUND;//full_path is NULL and j reached end of env >> no full_paths worked in get_path
	else
		global_ret_value = FAILURE; //case malloc failed
	free_split(path);
	return (global_ret_value);
}

/*
** Launches execve with absolute path /relative path or with $PATH + args[0]
** joined together, if one path of $PATH is correct. If $PATH is unset or
** $PATH="", only executes execve with absolute path / relative path.
*/
int		execve_part(char **args, char **env)
{
	if (args && args[0] && args[0][0] != '/' && !(args[0][0] == '.' &&
			(args[0][1] == '/' || (args[0][1] == '.' && args[0][2] == '/')))
			&& args[0][0] != '~' && env[find_var_in_env("PATH", env)]
			&& (int)ft_strlen(env[find_var_in_env("PATH", env)]) > 5
			&& !there_is_a_slash(args[0]))
		return (global_ret_value = execute_with_path_variable(args, env));
	return (global_ret_value = execute_path(args, env));
}