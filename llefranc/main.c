#include "includes/minishell.h"

//echo >>> output
//cd
//pwd >>> output
//export
//unset
//env >> output
//exit

/*
** Copies all the environnement variable in a **char to manipulate them after
** in our shell (so we can set new variables / unset some variables).
*/
char	**copy_env(char **env, int add_quotes_bool)
{
	char	**tmp;
	int		i;

// (void)add_quotes_bool;
	i = 0;
	while (env[i]) //number of environnement variable
		i++;
	if (!(tmp = malloc(sizeof(*tmp) * (i + 1))))
		return (NULL);
	tmp[i] = NULL;
	i = -1;
	while (env[++i])
	{
		if (add_quotes_bool)
			tmp[i] = add_quotes(env[i]);
		else
		{
			if (!(tmp[i] = malloc(ft_strlen(env[i]) + 1)))
			{
				free_split(tmp); //if malloc failed, we free all tmp[i] previously allocated + tmp
				return (NULL);
			}
			ft_strlcpy(tmp[i], env[i], ft_strlen(env[i]) + 1); //copying env[i] in tmp[i]
		}
	}
	return (tmp);
}

int		find_builtin(char **args, char ***env, int *ret_func)
{
	int ret;
	
	(void)env;
	ret = 0;
	if (!args)
		return (ret);
	// ft_printf("args 0 = %s\n", args[0]);
	!ft_strcmp("echo", args[0]) && (ret = 1) ? *ret_func = builtin_echo(args) : 0; //if args[0] match one builtin, put ret value to 0 and launch the appropriate builtin
	// !ft_strcmp("cd", args[0]) && (ret = 1) ? ft_printf("salut\n") : 0;
	// !ft_strcmp("pwd", args[0]) && (ret = 1) ? ft_printf("salut\n") : 0;
	!ft_strcmp("export", args[0]) && (ret = 1) ? *ret_func = builtin_export(args, env) : 0;
	// !ft_strcmp("unset", args[0]) && (ret = 1) ? ft_printf("salut\n") : 0;
	!ft_strcmp("env", args[0]) && (ret = 1) ? *ret_func = builtin_env(args, *env) : 0;
	// !ft_strcmp("exit", args[0]) && (ret = 1) ? ft_printf("salut\n") : 0;
	//echo int cd int pwd
	// ft_printf("---------\n", ret);
	return (ret);
}


int main(int ac, char *av[], char *env[])
{
	int ret_func = 0;
	int	ret_gnl = 1;
	char *line = NULL;
	char **cmd;
	char **env_shell;

	(void)av;
	if (!(env_shell = copy_env(env, 1)))
		return (1);
	if (ac != 1)
	{
		ft_printf("just launch minishell exe, without any argument\n");
		exit(EXIT_FAILURE);
	}
	// PARSEUR QUI DOIT RENVOYER UN DOUBLE TABLEAU DE CHAR (**ARGV) TERMINE PAR NULL
	ft_printf("bash-3.2$ ");
	while (ret_gnl)
	{
		ret_gnl = get_next_line(1, &line);
		if (!line[0])
		{
			free(line);
			continue ;
		}

		cmd = ft_split(line, ' ');
		if (!find_builtin(cmd, &env_shell, &ret_func))
			ft_printf("this command isn't a builtin command\n");
		// ft_printf("ret_func = %d\n>>> ", ret_func);
		ft_printf("bash-3.2$ ", ret_func);
		free(line);
		free_split(cmd);
		line = NULL;
		cmd = NULL;
	}
	return (0);
}

