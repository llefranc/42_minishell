/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 23:50:07 by user42            #+#    #+#             */
/*   Updated: 2020/11/08 23:50:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cdminishell.h"

void	ft_env_spacex(t_sh *sh)
{
	int i;
	int j;
	int k;

	i = -1;
	while (sh->copyenv[++i])
	{
		j = -1;
		while (sh->copyenv[i][++j])
		{
			if (sh->copyenv[i][j] == '=')
			{
				k = j - 1;
				while (sh->copyenv[i][++k])
				{
					if (sh->copyenv[i][k] == SPACE)
						sh->copyenv[i][k] = SPACE_EXPORT;
					else if (sh->copyenv[i][k] == SPACE_EXPORT)
						sh->copyenv[i][k] = SPACE;
				}
			}
		}
	}
}

void	ft_parser(char **semicolon, t_sh *sh)
{
	int	i;

	i = 0;
	while (semicolon[i])
	{
		ft_cdsplit_and_free(sh, semicolon[i]);
		ft_target_bslash(sh);
		ft_env_spacex(sh);
		ft_replace_path(sh);
		ft_env_spacex(sh);
		if (ft_handle_spaces_in_env(sh))
			return ;
		ft_trim_quotes(sh);
		ft_transfo_dollars(sh);
		first_token = create_token_list(sh->command);
		do_pipe(first_token, &(sh->copyenv));
		free_token_list(first_token);
		i++;
	}
}
