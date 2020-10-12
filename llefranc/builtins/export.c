/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 12:28:51 by llefranc          #+#    #+#             */
/*   Updated: 2020/10/12 15:21:57 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Sorts the tmp_env array and prints it on stdout. Then free the tmp_env.
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
    while (var[begin] && var[begin] != '=')
        begin++;
	if (var[begin] == '\0') //no need to add quotes if no '='
	{
		if (!(var_quoted = ft_strdup(var)))
			return (NULL);
		return (var_quoted);
	}
    size = ft_strlen(var) + 2; //for quotes
    if (!(var_quoted = malloc(size + 1))) //+1 for '\0'
        return (NULL);
    var_quoted[size] = '\0';
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
    if (!(tmp = malloc(sizeof(*tmp) * (i + 1)))) //+1 because env array is NULL terminated
        return (NULL);
    tmp[i] = NULL;
    i = -1;
    while (env[++i])
    {
        if (add_quotes_bool) //adds quotes for each var of env array
        {
            if (!(tmp[i] = add_quotes(env[i])))
                return (NULL);
        }
        else                //otherwise just duplicates env array
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
** Duplicates and returns a new environnement variable. Add quotes if there is
** '=' in the string.
*/
char    *add_new_variable(char *var)
{
    int     i;
    char    *new_var;
    
    i = 0;
    while (var[i] != '\0' && var[i] != '=' && !(var[i] == '+' && var[i + 1] == '='))
        i++;
	if (var[i] == '+')	//if it's 'toto+=2', we erase the '+' to have 'toto=2'
		ft_strlcpy(var + i, var + i + 1, ft_strlen(var + i + 1) + 1);
	if (!(new_var = ft_strdup(var))) //we duplicate the new var
		return (NULL);
    return (new_var);
}       

/*
** Reallocates an array of *char (previous variables + new ones from export).
*/
int     create_new_env_array(char ***env, int number_new_vars)
{
    char    **tmp_env;
    int     i;
    int     size;

    i = 0;
    while ((*env)[i])
        i++;
    size = i + number_new_vars; //future size of env array
    if (!(tmp_env = malloc(sizeof(*env) * (size + 1))))
        return (1);
    i = -1;
    while ((*env)[++i])
        tmp_env[i] = (*env)[i]; //copying adresses of previous array in new one
    while (i < size + 1)        //putting to NULL new ptr for new variables
        tmp_env[i++] = NULL;    //and null-terminating the array
    free(*env); //freeing previous array of *char
    *env = tmp_env;
    return (0);
}

/*
** Returns the lenght of the variable's name (the part before the '=' / '+=').
*/
int		len_var_name(char *var)
{
	int		i;

	i = 0;
	while (var[i] && var[i] != '=' && !(var[i] == '+' && var[i + 1] == '='))
		i++;
	return (i);
}

/*
** Returns 1 if *var doesn't exist in the environnement, 0 otherwise.
*/
int     is_it_new_variable(char *var, char **env)
{
    int     i;
    int     var_len; //size of the variable before '=' sign (ex toto=ta >> var_len = 4)

    i = 0;
    var_len = 0;
    while(var[var_len] && var[var_len] != '=' && var[var_len] != '+')
        var_len++;
    while (env[i] && (ft_strncmp(var, env[i], var_len) || 
			len_var_name(var) != len_var_name(env[i]))) //until we match an existing variable
        i++;
    if (!(env[i])) //if we reached end of env array, the variable doesn't exist
        return (1);
    return (0);
}

/*
** Adds = after the variable.
*/
int		add_equal(char **env, int i)
{
	int		j;
	int		len;
	char	*tmp;

	j = 0;
	len = ft_strlen(env[i]);
	while (env[i][j] && env[i][j] != '=')
		j++;
	if (env[i][j] == '=') //no need to change anything
		return (0);
	if (!(tmp = malloc(len + 2))) //+1 for = and +1 for '\0'
		return (1);
	tmp[len + 1] = '\0';
	ft_strlcpy(tmp, env[i], len + 1);
	tmp[len] = '=';
	free(env[i]);
	env[i] = tmp;
	return (0);
}

/*
** Joins the previous value and the new in the case of '+='.
*/
int		concatenate_values(char *var, char **env, int i)
{
	int		j;
	int		size_new_var;
	int		size_prev_var;
	char	*tmp;

	j = 0;
	while (var[j] && var[j] != '=')
		j++;
	size_new_var = (int)ft_strlen(&var[j + 1]);
	if (add_equal(env, i)) //adding '=' if that's not already the case
		return (1);
	size_prev_var = (int)ft_strlen(env[i]);
	if (!(tmp = malloc(size_new_var + size_prev_var + 1)))
		return (1);
	ft_strlcpy(tmp, env[i], size_prev_var + 1); //copying previous var
	ft_strlcpy(tmp + size_prev_var, &var[j + 1], size_new_var + 1); //copying new var's value (after =)
	free(env[i]);
	env[i] = tmp;
	return (0);
}

/*
** Frees the previous variable and adds the new one if there is '='.
** Join previous value and new one if there is '+='.
*/
int     update_variable(char *var, char **env)
{
    int     i;
    int     var_len; //size of the variable before sign '=' (ex toto=ta >> var_len = 4)

    i = 0;
    var_len = 0;
    while(var[var_len] && var[var_len] != '=' && var[var_len] != '+')
        var_len++;
    if (var[var_len] == '\0') //if just toto without '=', no need to update
        return (0);
    while (env[i] && ft_strncmp(var, env[i], var_len)) //until we match an existing variable
        i++;
	if (var[var_len] == '=') //if we just need to change the value
	{
		free(env[i]); //freeing previous variable
		if (!(env[i] = ft_strdup(var)))
			return (1);
	}
	else if (concatenate_values(var, env, i)) //in the case of '+='
		return (1);
    return (0);
}

/*
** Returns 0 if the variable's name is correct, 1 otherwise (first charac must be alpha,
** all the others ones until null-terminated / '=' / '+=' must be alphanum. '_' is authorized).
*/
int		check_name_var(char *var)
{
	int		i;
	
	if (!(ft_isalpha(var[0]) || var[0] == '_'))
		return (1);
	i = 0;
	while (var[i] && var[i] != '=' && var[i] != '+' && (ft_isalnum(var[i]) || var[i] == '_'))
		i++;
	if (var[i] == '\0' || var[i] == '=' || (var[i] == '+' && var[i + 1] == '='))
		return (0);
	return (1);
}

/*
** If no arguments, prints all the variables sorted by alphabetical order on
** stdout. If arguments, adds the new variables to the environnement / or
** update their values if they already exist. Doesn't take any options.
** Returns 0 if success, 1 if failure.
*/
int     builtin_export(char **args, char ***env)
{
    int     i;
    int     j;
	int		ret_value;

	ret_value = 0;
    if (args && !args[1]) //if no arguments and only export cmd >> prints env
    {
        print_sort_env(copy_env(*env, 1));
        return (0);
    }
    if (args[1][0] == '-') //our export doesn't handle options
        return (error_msg("minishell: export: no options are allowed\n", 1));
    i = 0;
    while (args[++i]) //first i is 1, cause args[0] is export cmd
    {
		if (check_name_var(args[i]))	//if name of variable isn't correct >> we don't export
		{								// and we set return value to error code (1)
			ret_value = 1;
			ft_printf("minishell: export: `%s': not a valid identifier\n", args[i]);
		}
        else if (is_it_new_variable(args[i], *env)) //if the variable doesn't exist in the environnement
        {
            if (create_new_env_array(env, 1)) //add one *char to the end of env array for new var
                return (error_msg("minishell: export: malloc failed\n", 1));
            j = 0;
            while ((*env)[j]) //going to the end of the actual env array
                j++;
            if (!((*env)[j] = add_new_variable(args[i])))
                return (error_msg("minishell: export: malloc failed\n", 1));
        }
        else        //args[i] already exist in the environnement, so we just update the value
            if (update_variable(args[i], *env))
                return (error_msg("minishell: export: malloc failed\n", 1));
    }
    return (ret_value);
}