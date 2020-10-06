/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 12:28:51 by llefranc          #+#    #+#             */
/*   Updated: 2020/10/06 18:05:34 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Sorts the tmp_env tab and prints it on stdout. Then free the tmp_env.
*/
void    print_sort_env(char **tmp_env)
{
    int     i;
    int     ret;
    char    *tmp_swap;

    i = 0;
    ret = 0;
    while (tmp_env[i] && tmp_env[i + 1])
    {
        if (ft_strcmp(tmp_env[i], tmp_env[i + 1]) > 0) //we switch if next str is greater
        {
            tmp_swap = tmp_env[i];
            tmp_env[i] = tmp_env[i + 1];
            tmp_env[i + 1] = tmp_swap;
            i = -1; //then we start again from the beginning of tmp_env
        }
        i++;
    }
    i = 0;
    while(tmp_env[i]) //printing each variable
        ft_printf("declare -x %s\n", tmp_env[i++]);
    free_split(tmp_env);
}

/*
** Duplicates a variable and add quotes (from toto=tata to toto="tata")
*/
char    *add_quotes(char *var)
{
    char    *var_quoted;
    int     size;
    int     begin;

    begin = 0;
    size = ft_strlen(var) + 2; //for quotes
    if (!(var_quoted = malloc(size + 1))) //+1 for '\0'
        return (NULL);
    var_quoted[size] = '\0';
    while (var[begin] != '=')
        begin++;
    begin++;
    ft_strlcpy(var_quoted, var, begin + 1); //copying firsrt part until '='
    var_quoted[begin] = '\"';
    ft_strlcpy(var_quoted + begin + 1, var + begin, ft_strlen(var + begin - 1)); //copying part after '='
    var_quoted[size - 1] = '\"';
    return (var_quoted);
}

/*
** Copies all the environnement variable in a **char to manipulate them after
** in our shell (so we can set new variables / unset some variables). If
** add_quotes_bool is set to 1, add quotes for each line after the '='.
** toto=tata >> toto="tata"
*/
char    **copy_env(char **env, int add_quotes_bool)
{
    char    **tmp;
    int     i;

    i = 0;
    while (env[i]) //number of environnement variable
        i++;
    if (!(tmp = malloc(sizeof(*tmp) * (i + 1)))) //+1 because env tab is NULL terminated
        return (NULL);
    tmp[i] = NULL;
    i = -1;
    while (env[++i])
    {
        if (add_quotes_bool) //adds quotes for each var of env tab
        {
            if (!(tmp[i] = add_quotes(env[i])))
                return (NULL);
        }
        else                //otherwise just duplicates env tab
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

/*
** Duplicates and return a new environnement variable. Add quotes if there is
** an equal in the string.
*/
char    *add_new_variable(char *var)
{
    int     i;
    char    *new_var;
    
    i = 0;
    while (var[i] != '\0' && var[i] != '=')
        i++;
    if (var[i] == '=')  //if the variable contains an equal, we add quotes
    {
        if (!(new_var = add_quotes(var)))
            return (NULL);
    }
    else                //otherwise we just duplicate the new var
        if (!(new_var = ft_strdup(var)))
            return (NULL);
    return (new_var);
}       

/*
** Reallocates a tab of *char (previous variables + new ones from export).
*/
int     create_new_env_tab(char ***env, int number_new_vars)
{
    char    **tmp_env;
    int     i;
    int     size;

    i = 0;
    while ((*env)[i])
        i++;
    size = i + number_new_vars; //future size of env tab
    if (!(tmp_env = malloc(sizeof(*env) * (size + 1))))
        return (1);
    i = -1;
    while ((*env)[++i])
        tmp_env[i] = (*env)[i]; //copying adresses of previous tab in new one
    while (i < size + 1)        //putting to NULL new ptr for new variables
        tmp_env[i++] = NULL;    //and null-terminating the tab
    free(*env); //freeing previous tab of *char
    *env = tmp_env;
    return (0);
}

/*
** Returns 1 if *var doesn't exist in the environnement, 0 otherwise.
*/
int     new_variable(char *var, char **env)
{
    int     i;
    int     var_len; //size of the variable before '=' sign (ex toto=ta >> var_len = 4)

    i = 0;
    var_len = 0;
    while(var[var_len] && var[var_len] != '=')
        var_len++;
    while (env[i] && ft_strncmp(var, env[i], var_len)) //until we match an existing variable
        i++;
    if (!(env[i])) //if we reached end of env tab, the variable doesn't exist
        return (1);
    return (0);
}

/*
** Frees the previous variable and adds the new one.
*/
int     update_variable(char *var, char **env)
{
    int     i;
    int     var_len; //size of the variable before sign '=' (ex toto=ta >> var_len = 4)
    char    *tmp;

    i = 0;
    var_len = 0;
    while(var[var_len] && var[var_len] != '=')
        var_len++;
    if (var[var_len] == '\0') //if just toto without '=', no need to update
        return (0);
    while (env[i] && ft_strncmp(var, env[i], var_len)) //until we match an existing variable
        i++;
    free(env[i]); //freeing previous variable
    if (!(tmp = ft_strdup(var)))
        return (1);
    if (!(env[i] = add_quotes(tmp)))
        return (1);
    free(tmp);
    return (0);
}

/*
** Checks if the variable's name is correct (first charac must be alpha,
** all the others ones until '\0' or '=' must be alphanum).
*/
int		check_name_var(char *var)
{
	int		i;
	
	if (!ft_isalpha(var[0]))
		return (1);
	i = 0;
	while (var[i] && var[i] != '=' && ft_isalnum(var[i]))
		i++;
	if (var[i] == '\0' || var[i] == '=')
		return (0);
	return (1);
}

/*
** If no arguments, prints all the variables sorted by alphabetical order on
** stdout. If arguments, adds the new variables to the environnement / or
** update their values if they already exist. Doesn't take any options.
*/
int     builtin_export(char **args, char ***env)
{
    int     i;
    int     j;
	int		ret_value;

	ret_value = 0;
    if (args && !args[1]) //if no arguments and only export cmd >> prints env
    {
        print_sort_env(copy_env(*env, 0));
        return (0);
    }
    if (args[1][0] == '-') //our export doesn't handle options
        return (error_msg("bash: export: no options are allowed\n", 1));
    i = 0;
    while (args[++i]) //first i is 1, cause args[0] is export cmd
    {
		if (check_name_var(args[i]))	//if name of variable isn't correct >> we don't export
		{								// and we set return value to error code (1)
			ret_value = 1;
			ft_printf("bash: export: `%s': not a valid identifier\n", args[i]);
		}
        else if (new_variable(args[i], *env)) //if the variable doesn't exist in the environnement
        {
            if (create_new_env_tab(env, 1)) //add one *char to the end of env tab for new var
                return (error_msg("bash: export: malloc failed\n", 1));
            j = 0;
            while ((*env)[j]) //going to the end of the actual env tab
                j++;
            if (!((*env)[j] = add_new_variable(args[i])))
                return (error_msg("bash: export: malloc failed\n", 1));
        }
        else        //args[i] already exist in the environnement, so we just update the value
            if (update_variable(args[i], *env))
                return (error_msg("bash: export: malloc failed\n", 1));
    }
    return (ret_value);
}