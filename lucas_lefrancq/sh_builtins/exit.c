/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 15:34:05 by lucas          #+#    #+#             */
/*   Updated: 2020/10/21 16:50:29 by lucas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Exits wtih exit_value as exit code, and prints an exit message on stdout.
*/
void	exit_with_msg(char **env, char *msg, unsigned char exit_value)
{
	free(global_path);
	free(global_home);
	free_split(env);
	(void)msg;
	ft_fd_printf(STDOUT_FILENO, "%s", msg);
	free_token_list(first_token);
	exit(exit_value);
}

/*
** Returns SUCCESS if the string is only made of digit, FAILURE otherwise.
*/
int		string_is_num(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		if (!(ft_isdigit(str[i])))
			return (FAILURE);
	return (SUCCESS);
}

void	ft_swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

/*
** Puts all the empty args at the end of char **args. Exit builtin will treat
** all normal args and stop when it will meet an empty argument.
*/
void	sort_args_exit(char **args)
{
	int		i;
	int		j;

	i = 1;
	while (args[i])
	{
		if (args[i][0] == '\0')
		{
			j = i + 1;
			while (args[j] && args[j][0] == '\0')
				j++;
			if (!args[j]) //args[i] and all the following arguments are empty
				i = j;
			else
			{
				ft_swap(&args[i], &args[j]);
				i = 0;
			}
		}
		else
			i++;
	}
}

/*
** If more than 2 arguments, returns FAILURE and doesn't exit. If no argument,
** exits with SUCCESS. If argument is not numeric or bigger than a long, exits
** with 255 as exit code. Otherwise exits with argument cast in unsigned char
** as exit code. Frees all the *ptr previously allocated ands restores the fd
** for STDIN / STDOUT.
*/
int		builtin_exit(char **args, char **env)
{
	long	i;

	sort_args_exit(args);
	if (args && !args[1]) //case just exit without argument
		exit_with_msg(env, "exit\n", SUCCESS);
	else if (args[1] && args[1][0] != '\0' && (ft_strlen(args[1]) > 20  //long max is 19 characters long
			|| ((args[1][0] != '-' && args[1][0] != '+' && !ft_isdigit(args[1][0])) //case first charac is '-'
			|| string_is_num(&args[1][1])) || ((args[1][0] == '-' || args[1][0] == '+') && args[1][1] == '\0') //case arg is only '-'
			|| (args[1][0] != '-' && ft_atoi(args[1]) < 0) //if args[1] > long max, it will produce an overflow
			|| (args[1][0] == '-' && ft_atoi(args[1]) > 0))) //if args[1] < long min, it will produce an overflow
	{
		free(global_path);
		free(global_home);
		free_split(env);
		ft_fd_printf(STDERR_FILENO, "exit\nminishell: exit: %s: numeric argument required\n", args[1]);
		free_token_list(first_token); //needs to be free after last use of **args
		exit(2);
	}
	else if (args && args[1] && (args[2] && args[2][0] != '\0'))
	{
		ft_fd_printf(STDERR_FILENO, "exit\nminishell: exit: too many arguments\n");
		return (FAILURE);
	}
	i = ft_atoi(args[1]);
	exit_with_msg(env, "exit\n", (unsigned char)i);
	return (SUCCESS);
}
