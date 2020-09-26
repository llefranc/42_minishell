#include "includes/minishell.h"

int		find_builtin(char **av, int *ret_func)
{
	int ret;
	
	ret = 1;
	if (!av)
		return (ret);
	!ft_strcmp("echo", av[0]) ? ret = 0 && (*ret_func = ft_printf("builtin echo\n")) : 0; //if av[1] match one builtin, put ret value to 0 and launch the appropriate builtin
	// !ft_strcmp("cd", av[1]) ? ret = 0 && ft_printf("salut\n") : 0;
	// !ft_strcmp("pwd", av[1]) ? ret = 0 && ft_printf("salut\n") : 0;
	// !ft_strcmp("export", av[1]) ? ret = 0 && ft_printf("salut\n") : 0;
	// !ft_strcmp("unset", av[1]) ? ret = 0 && ft_printf("salut\n") : 0;
	// !ft_strcmp("env", av[1]) ? ret = 0 && ft_printf("salut\n") : 0;
	// !ft_strcmp("exit", av[1]) ? ret = 0 && ft_printf("salut\n") : 0;
	//echo int cd int pwd
	
	return (ret);
}


int main(int ac, char *av[], char *env[])
{
	int ret_func = 0;
	int	ret_gnl = 1;
	char *line = NULL;
	char **cmd;

	(void)env;
	(void)av;
	if (ac != 1)
	{
		ft_printf("just launch minishell exe, without any argument\n");
		exit(EXIT_FAILURE);
	}
	// PARSEUR QUI DOIT RENVOYER UN DOUBLE TABLEAU DE CHAR (**ARGV) TERMINE PAR NULL
	while (ret_gnl)
	{
		ret_gnl = get_next_line(1, &line);
		if (!line[0])
		{
			free(line);
			continue ;
		}

		cmd = ft_split(line, ' ');
		if (find_builtin(cmd, &ret_func))
			ft_printf("this command isn't a builtin command\n");
		ft_printf("ret_func = %d\n", ret_func);
		free(line);
		free_split(cmd);
		line = NULL;
		cmd = NULL;
	}
	return (0);
}

