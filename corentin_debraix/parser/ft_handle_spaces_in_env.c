/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_spaces_in_env.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:07:48 by llefranc          #+#    #+#             */
/*   Updated: 2020/10/28 17:23:31 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cdminishell.h"

/*
** Returns 1 if the char SPACE_EXPORT is present (see minishell.h for its value)
** otherwise returns 0.
*/
int		there_is_spaces(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != SPACE_EXPORT)
		i++;
	if (str[i] == SPACE_EXPORT)
		return (1);
	return (0);
}

/*
** Splits the line (sh->command)[i], then reallocates a new **char and inserts
** at index i the new **char from split. Frees the previous sh->command.
*/
char	**create_new_array_with_spaces_split(t_sh *sh, int i)
{
	char	**split;
	char	**tmp;
	int		size_sh_cmd;
	int		size_split;
	int		j;

	size_split = 0;
	size_sh_cmd = 0;
	if (!(split = ft_split((sh->command)[i], SPACE_EXPORT))) //split env var with spaces
		return (NULL);
	while ((sh->command)[size_sh_cmd])
		size_sh_cmd++;
	while (split[size_split])
		size_split++;
	if (!(tmp = malloc(sizeof(*tmp) * (size_sh_cmd + size_split)))) //sh->command - line with spaces + new split
		return (NULL);
	tmp[size_sh_cmd + size_split - 1] = NULL;
	j = -1;
	while (++j < i)
		tmp[j] = (sh->command)[j]; //copying sh->command until line with spaces
	size_split = -1;
	while (split[++size_split])
		tmp[j++] = split[size_split]; //copying new split
	while ((sh->command)[++i])
		tmp[j++] = (sh->command)[i]; //copying sh->command after line with spaces
	free(split);
	free(sh->command);
	return (tmp);
}

/*
** When a command is launched with an env var containing spaces, splits those
** spaces inside the command to have different args (ex : TOTO="a   b", echo TOTO
** will print >> "a b"). Returns an error if redirections are used with env var
** containing spaces.
*/
int		ft_handle_spaces_in_env(t_sh *sh)
{
	int		i;
	
	i = -1;
	while ((sh->command)[++i])
	{
		if (there_is_spaces((sh->command)[i]))
		{
			if (i > 0 && ((sh->command)[i - 1][0] == F_RIGHT || //if '>' or '<' with $VAR_WITH_SPACES >> error
					(sh->command)[i - 1][0] == F_LEFT))
				return (global_ret_value = error_msg("ambigous redirect\n", FAILURE));
			if (!(sh->command = create_new_array_with_spaces_split(sh, i)))
				return (global_ret_value = error_msg("malloc failed\n", FAILURE));
			i = -1;
		}
	}
	return (SUCCESS);
}