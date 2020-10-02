#include "../includes/minishell.h"

/*
bash: export: -v: invalid option
export: usage: export [-nf] [name[=value] ...] or export -p
bash-3.2$

export solo >> trie ds ordre alphabetique en mettant declare -x devant

declare -x toto="====================================================10"

export toto >> cree la variable toto sans lui assigner de valeur

export peut export plusieurs variable qui n'ont pas forcement une valeur attribué

export test3= >> test3=""
export test2 >> test2
*/


/*
** Sorts the tmp_env tab and prints it on stdout. Then free the tmp_env.
*/
void	print_sort_env(char **tmp_env)
{
	int		i;
	int		ret;
	char	*tmp_swap;

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
** Reallocates a tab of *char (previous variables + new ones from export).
*/
int		create_new_env_tab(char ***env, int number_new_vars)
{
	char	**tmp_env;
	int		i;
	int		size;

	i = 0;
	while ((*env)[i])
		i++;
	size = i + number_new_vars; //future size of env tab
	if (!(tmp_env = malloc(sizeof(*env) * (size + 1))))
		return (1);
	i = -1;
	while ((*env)[++i])
		tmp_env[i] = (*env)[i]; //copying adresses of previous tab in new one
	while (i < size + 1)		//putting to NULL new ptr for new variables
		tmp_env[i++] = NULL;	//and null-terminating the tab
	free(*env);	//freeing previous tab of *char
	*env = tmp_env;
	return (0);
}

/*
** Duplicates a variable and add quotes (from toto=tata to toto="tata")
*/
char	*add_quotes(char *var)
{
	char	*var_quoted;
	int		size;
	int		begin;

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
** Duplicates and return a new environnement variable. Add quotes if there is
** an equal in the string.
*/
char	*add_new_variable(char *var)
{
	int		i;
	char	*new_var;
    
	i = 0;
	while (var[i] != '\0' && var[i] != '=')
		i++;
	if (var[i] == '=')	//if the variable contains an equal, we add quotes
	{
		if (!(new_var = add_quotes(var)))
			return (NULL);
	}
	else				//otherwise we just duplicate the new var
		if (!(new_var = ft_strdup(var)))
			return (NULL);
	return (new_var);
}		

int		builtin_export(char **args, char ***env)
{
	int		i;
	int		j;

	if (args && !args[1]) //if no arguments and only export cmd
	{
		print_sort_env(copy_env(*env, 0));
		return (0);
	}
	i = 1; //cause args[0] is export cmd
	while (args[i])
		i++;
	if (create_new_env_tab(env, i))
	{
		ft_printf("export : malloc failed\n");
		return (1);
	}
	i = 1;
	j = 0;
	while ((*env)[j]) //going to the end if the actual env var tab
		j++;
	while (args[i]) //adding each arguments to env var tab
	{
		if (!((*env)[j++] = add_new_variable(args[i++])))
		{
			ft_printf("export : malloc failed\n"); //REMPLACER PAR UNE FONCTION
			return (1);
		}
	}
	return (0);
}

reprendre un peu la fonction copy env avec les fonctions d'erreurs, rajouter des commentaires
et pareil dans export checker les foncitons de retour d'erreur