/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 15:34:05 by llefranc          #+#    #+#             */
/*   Updated: 2020/10/13 13:49:44 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Exits wtih exit_value as exit code, and prints an exit message on stdout.
*/
void	exit_with_msg(char *msg, unsigned char exit_value)
{
	ft_printf("%s", msg);
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

/*
** If more than 2 arguments, returns FAILURE and doesn't exit. If no argument,
** exits with SUCCESS. If argument is not numeric or bigger than a long, exits
** with 255 as exit code. Otherwise exits with argument cast in unsigned char
** as exit code. Frees all the *ptr previously allocated.
*/
int		builtin_exit(char **args, char **env)
{
	long	i;

	i = -1;
	if (args && args[1] && args[2])
		return (error_msg("exit\nminishell: exit: too many arguments\n", FAILURE));
	free(global_path);
	free_split(env);
	if (args && !args[1]) //case just exit without argument
		exit_with_msg("exit\n", SUCCESS);
	else if (i == SUCCESS)
		exit_with_msg("exit\n", SUCCESS);
	else if (args[1] && (args[1][0] == '\0' || ft_strlen(args[1]) > 20  //long max is 19 characters long
			|| ((args[1][0] != '-' && !ft_isdigit(args[1][0])) //case first charac is '-'
			|| string_is_num(&args[1][1])) || (args[1][0] == '-' && args[1][1] == '\0') //case arg is only '-'
			|| (args[1][0] != '-' && ft_atoi(args[1]) < 0) //if args[1] > long max, it will produce an overflow
			|| (args[1][0] == '-' && ft_atoi(args[1]) > 0))) //if args[1] < long min, it will produce an overflow
	{
		ft_printf("exit\nminishell: exit: %s: numeric argument required\n", args[1]);
		exit(255);
	}
	i = ft_atoi(args[1]);
	ft_printf("exit\n"); //normal exit with exit code
	exit((unsigned char)i);
}