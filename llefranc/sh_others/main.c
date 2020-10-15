/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 12:28:41 by llefranc          #+#    #+#             */
/*   Updated: 2020/10/15 12:39:02 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


char	**copy_env(char **env, int add_quotes_bool);
int		find_var_in_env(char *var, char **env);

//echo >>> output
//cd
//pwd >>> output
//export
//unset
//env >> output
//exit
//gerer le cas ou le cd est a la fin d'un pipe 

//penser a ajouter fd_printf
//penser a mettre en variable globale le retour des fonctions et le ptr qui tient le tab de structs
// echo ok > text.txt salut

t_token		**create_token_array(char **args)
{
	t_token **tok;
	int		i = -1;

	tok = malloc(sizeof(*tok) * 2);
	tok[1] = NULL;
	while (tok[++i])
		tok[i] = malloc(sizeof(**tok));
	tok[0]->ptr = args;
	tok[0]->type = EXEC;
	return (tok);
}

int main(int ac, char *av[], char *env[])
{
	int	ret_gnl = 1;
	char *line = NULL;
	char **cmd;
	char **env_shell; //copy of env
	t_token **tok;

	(void)av;
	if (!(env_shell = copy_env(env, 0)))
		return (1);
	if (ac != 1)
	{
		ft_printf("just launch minishell exe, without any argument\n");
		exit(EXIT_FAILURE);
	}
	// PARSEUR QUI DOIT RENVOYER UN DOUBLE TABLEAU DE CHAR (**ARGV) TERMINE PAR NULL
	ft_printf("minishel$ ");
	while (ret_gnl)
	{
		ret_gnl = get_next_line(1, &line);
		if (!line[0])
		{
			free(line);
			continue ;
		}

		cmd = ft_split(line, ' ');
		tok = create_token_array(cmd);
		if (execution(tok, &env_shell))
			ft_printf("sortie de exec_part sans aucune commande lancee\n");
		// ft_printf("ret_func = %d\n>>> ", ret_func);
		ft_printf("minishel$ ");
		free(line);
		free_split(cmd);
		line = NULL;
		cmd = NULL;
	}
	return (0);
}

