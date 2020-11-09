/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 13:48:53 by corentin          #+#    #+#             */
/*   Updated: 2020/11/03 17:54:53 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cdminishell.h"

//pour shlvl >> on recup valeur d'env et on rajoute +1
//si shlvl negatif et on ouvre new bash >> shlvl=0
//si shlvl est du texte et on ouvre un new bash >>shlvl=1
//si --4 >> shlvl=1
//si shlvl="" >> shlvl=1
//si shlvl unset >> shlvl=1
//si shlvl=999 >> shlvl=1 + msg : bash avertissement niveau de shell trop eleve

int		find_var_in_env(char *var, char **env);

/*
** Adds SHLVL variable to environment with a value of 1 if this one doesn't
** exist. Frees the previous env.
*/
int		create_shlvl_value(t_sh *sh, char **tmp_env)
{
	int		i;

	i = 0;
	while (tmp_env[i])
		i++;
	if (!(tmp_env = malloc(sizeof(*tmp_env) * (i + 2)))) //+2 for new var and NULL terminated
		return (error_msg("shlvl: malloc failed\n", FAILURE));
	i = -1;
	while ((sh->copyenv)[++i])
		tmp_env[i] = (sh->copyenv)[i];
	if (!(tmp_env[i] = ft_strdup("SHLVL=1")))
		return (error_msg("shlvl: malloc failed\n", FAILURE));
	tmp_env[i + 1] = NULL;
	free(sh->copyenv); //freeing previous **char
	sh->copyenv = tmp_env;
	return (SUCCESS);
}

/*
** If SHLVL is set but without a value, sets SHLVL to value.
*/
int		reinitialize_shlvl_value(int index, char **env, int value)
{
	free(env[index]);
	if (value == 1 && !(env[index] = ft_strdup("SHLVL=1")))
		return (error_msg("shlvl: malloc failed\n", FAILURE));
	if (value == 0 && !(env[index] = ft_strdup("SHLVL=0")))
		return (error_msg("shlvl: malloc failed\n", FAILURE));
	return (SUCCESS);
}

int		increment_shlvl_value(int index, char **env)
{
	int		shlvl_value;
	char	*tmp;

	shlvl_value = ft_atoi(&env[index][6]) + 1;
	if (!(tmp = ft_itoa(shlvl_value)))
		return (error_msg("shlvl: malloc failed\n", FAILURE));
	free(env[index]);
	if (!(env[index] = ft_strjoin("SHLVL=", tmp)))
		return (error_msg("shlvl: malloc failed\n", FAILURE));
	free(tmp);
	return (SUCCESS);
}

int		init_shlvl_value(t_sh *sh, char **env)
{
	int		i;

	i = find_var_in_env("SHLVL", env);
	if (!env[i]) //if SHLVL doesn't exist
		return (create_shlvl_value(sh, env));
	else if (env[i][5] == '\0' || (env[i][5] == '=' &&
			env[i][6] == '\0'))
		return (reinitialize_shlvl_value(i, env, 1));
	else if (!((env[i][6] == '+' || env[i][6] == '-' || ft_isdigit(env[i][6])) && ft_strisdigit(&(env[i][7]))))
		return (reinitialize_shlvl_value(i, env, 1));
	else if ((env[i][6] != '+' && env[i][6] != '-') && !ft_strisdigit(&(env[i][6])))
		return (reinitialize_shlvl_value(i, env, 1));
	else if (env[i][6] == '-')
		return (reinitialize_shlvl_value(i, env, 0));
	else if ((ft_strlen(&env[i][6]) > 4) || ft_atoi(&env[i][6]) >= 999)
	{
		ft_fd_printf(1, "minishell: avertissement: niveau de shell trop eleve,"
		" initialisation a 1", &env[i][6]);
		return(reinitialize_shlvl_value(i, env, 1));
	}
	else
		return (increment_shlvl_value(i, env));
	return (SUCCESS);
	
}

/*
** Realloc and copy of **env in sh->copyenv
** Then easy to free
*/

void	ft_copy_env(char **env, t_sh *sh)
{
	int i;

	i = 0;
	while (env[sh->envlen])
		sh->envlen++;
	sh->copyenv = malloc(sizeof(*sh->copyenv) * (sh->envlen + 1));
	i = -1;
	while (env[++i])
		sh->copyenv[i] = ft_cdstrdup(env[i]);
	sh->copyenv[i] = NULL;
	init_shlvl_value(sh, sh->copyenv);
}
