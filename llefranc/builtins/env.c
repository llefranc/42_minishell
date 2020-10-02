#include "../includes/minishell.h"

/*
** Prints all the environnement variables of the shell on stdout.
** Doesn't take arguments neither options.
*/
int		builtin_env(char **args, char **env)
{
	if (*(args + 1)) //expected only env in **args >> so args[1] should be NULL
	{				 //(args is **char NULL terminated)
		ft_printf("env : doesn't take options or arguments\n");
		return (1); //error
	}
	while (env && *env)
	{
		ft_printf("%s\n", *env); //print each env variable on stdout;
		env++;
	}
	return (0);
}