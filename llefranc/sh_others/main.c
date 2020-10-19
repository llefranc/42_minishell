/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 12:28:41 by llefranc          #+#    #+#             */
/*   Updated: 2020/10/19 17:59:14 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


char	**copy_env(char **env, int add_quotes_bool);
int		find_var_in_env(char *var, char **env);

//gerer le cas ou le cd est a la fin d'un pipe 

//penser a ajouter fd_printf
//penser a mettre en variable globale le retour des fonctions et le ptr qui tient le tab de structs
// echo ok > text.txt salut

// t_token		**create_token_array(char **args, int size)
// {
// 	t_token **tok;
// 	int		i = -1;

// 	tok = malloc(sizeof(*tok) * (size + 1));
// 	tok[size] = NULL;
// 	while (++i < size)
// 		tok[i] = malloc(sizeof(**tok));
// 	tok[0]->ptr = args;
// 	tok[0]->type = EXEC;
// 	return (tok);
// }

// FONCTION TEST
// echo salut > test coucouo \\ | head | wc > > test2 < test3

// fd = dup(1)

// head test.txt | wc | cat

// fd[2]       >> fd[1] >> fd[0]
// pipe(fd);
// fork()


//         HEAD            |           WC              
//           close(fd[0])  |      close(fd[1])             
//                         |                           
//   dup2(1, fd[1])        |       dup2(0, fd[0])
//                         |                           
//                         |       dup2(1, SAUVEGARDE_STDOUT)         
//                         |       dup2(0, SAUVEGARDE_STDIN) 
//                         |                           
//                         |                           
//                         |                           
//                         |                           
//                         |                           
//                         |                           
//                         |                           
//                         |       

void	imite_fonction_corentin(char **cmd)
{
	int		i = -1;

	while (cmd[++i])
	{
		if (cmd[i][0] == '>' && cmd[i][1] == '\0')
			cmd[i][0] = F_RIGHT;
		else if (cmd[i][0] == '<' && cmd[i][1] == '\0')
			cmd[i][0] = F_LEFT;
		else if (cmd[i][0] == '|' && cmd[i][1] == '\0')
			cmd[i][0] = F_PIPE;
	}
}

void	print_list(t_token *first);


int main(int ac, char *av[], char *env[])
{
	int	ret_gnl = 1;
	char *line = NULL;
	char **cmd;
	char **env_shell; //copy of env
	// t_token **tok;
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
		ret_gnl = get_next_line(0, &line);
		if (!line[0])
		{
			free(line);
			continue ;
		}
		cmd = ft_split(line, ' ');
		imite_fonction_corentin(cmd);
		int i = -1;
		while (cmd[++i])
			ft_printf("%s\n", cmd[i]);
		ft_printf("\n\n-----------------\n\n");
		first_token = create_list(cmd);
		print_list(first_token);
		// tok = create_token_array(cmd, 1);
		// if (execution(tok, &env_shell))
		// 	ft_printf("sortie de exec_part sans aucune commande lancee\n");
		// system("leaks a.out");
		// ft_printf("ret_func = %d\n>>> ", ret_func);
		// ft_printf("minishel$ ");
		// free(line);
		// free_split(cmd);
		// free(tok[1]);
		// free(tok[0]);
		// free(tok);
		// line = NULL;
		// cmd = NULL;
	}
	return (0);
}

