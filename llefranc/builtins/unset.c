/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 17:42:10 by llefranc          #+#    #+#             */
/*   Updated: 2020/10/06 17:46:33 by llefranc         ###   ########.fr       */
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
    // int      size;

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
    free((*env)[i++]);
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

int     builtin_unset(char **args, char ***env)
{
    int     i;
    int     j;
    
    if (args && !args[1]) //if no arguments and only unset cmd >> nothing
        return (0);
    if (args[1][0] == '-') //our unset doesn't handle options
        return (error_msg("bash: unset: no options are allowed\n", 1));
	i = 0;
    while (args[++i]) //first i is 1, cause args[0] is export cmd
    {
        j = 0;
        while (args[i][j] && args[i][j] != '=')
            j++;
        if (args[i][j] != '=' && !new_variable(args[i], *env))  //if the variable exist in the environnement
        {                                                       //and there is no '=' inside
            if (!(reduce_env_tab(env, args[i])))
                return (error_msg("bash: unset: malloc failed\n", 1));
        }
    }
    return (0);
}
