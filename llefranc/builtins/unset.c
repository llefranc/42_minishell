/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 17:42:10 by llefranc          #+#    #+#             */
/*   Updated: 2020/10/06 18:44:17 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// bash-3.2$ unset tutu=5
// bash: unset: `tutu=5': not a valid identifier

/*
** Reallocates a tab of *char (previous variables + new ones from export).
*/
int     reduce_env_tab(char ***env, char *old_var)
{
    char    **tmp_env;
    int     i;
    int     j;

    i = 0;
    while ((*env)[i])
        i++;
    if (!(tmp_env = malloc(sizeof(*env) * i)))
        return (1);
    tmp_env[i - 1] = NULL;
    i = 0;
    j = 0;
    while ((*env)[i] && ft_strcmp((*env)[i], old_var))
    {
        tmp_env[j] = (*env)[i]; //copying adresses of previous tab in new one
        i++;
        j++;
    }
    free((*env)[i++]); //var that needs to be unset
    while ((*env)[i])
    {
        tmp_env[j] = (*env)[i]; //copying adresses of previous tab in new one
        i++;
        j++;
    }
    free(*env); //freeing previous tab of *char
    *env = tmp_env;
    return (0);
}

/*
** Checks if the variable's name is correct (first charac must be alpha,
** all the others ones until '\0' must be alphanum).
*/
int		check_name_var_unset(char *var)
{
	int		i;
	
	if (!ft_isalpha(var[0]))
		return (1);
	i = 0;
	while (var[i] && var[i] != '=' && ft_isalnum(var[i]))
		i++;
	if (var[i] == '\0')
		return (0);
	return (1);
}

int     builtin_unset(char **args, char ***env)
{
    int     i;
	int		ret_value;
    
    if (args && !args[1]) //if no arguments and only unset cmd >> nothing
        return (0);
    if (args[1][0] == '-') //our unset doesn't handle options
        return (error_msg("bash: unset: no options are allowed\n", 1));
	i = 0;
	ret_value = 0;
    while (args[++i]) //first i is 1, cause args[0] is export cmd
    {
		if (check_name_var_unset(args[i]))	//if name of variable isn't correct >> we don't export
		{									// and we set return value to error code (1)
			ret_value = 1;
			ft_printf("bash: export: `%s': not a valid identifier\n", args[i]);
		}
        else if (!new_variable(args[i], *env))		//if the variable exist in the environnement
        {											//and there is no '=' inside
            if (reduce_env_tab(env, args[i]))
                return (error_msg("bash: unset: malloc failed\n", 1));
        }
    }
    return (ret_value);
}
