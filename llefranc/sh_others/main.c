/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 12:28:41 by llefranc          #+#    #+#             */
/*   Updated: 2020/10/21 15:16:35 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


char	**copy_env(char **env, int add_quotes_bool);
int		find_var_in_env(char *var, char **env);

//gerer le cas ou le cd est a la fin d'un pipe 
//mettre le home en variable globale pour cd
//checker le cas de pwd dans un fichier efface si j'unset pwd
//penser a bien chercker que tout est free
//checker le cas de ls=ls

//penser a mettre en variable globale le retour des fonctions et le ptr qui tient le tab de structs

// FONCTION TEST
// echo salut > test coucouo \\ | head | wc > > test2 < test3
// echo ok > text.txt salut
// echo salut > test coucouo \\ | head | wc > > test2 < test3 > test6 > test7 > > test8 < test9 salut ok hello > test10 | bonjour ok | < lol > mdr programme
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

void	print_list(t_token *first)
{
	while (first)
	{
		first->type == PIPE ? ft_printf("PIPE (%d)\n", first->type) : 0;
		first->type == EXEC ? ft_printf("EXEC (%d)\n", first->type) : 0;
		first->type == INPUT ? ft_printf("INPUT (%d)\n", first->type) : 0;
		first->type == OUTPUT ? ft_printf("OUTPUT (%d)\n", first->type) : 0;
		first->type == OUTPUT_ADD ? ft_printf("OUTPUT_ADD (%d)\n", first->type) : 0;
		
		if (first->type == OUTPUT_ADD || first->type == OUTPUT || first->type == INPUT)
			ft_printf("file = %s\n", (first->args)[0]);
		else if (first->type == PIPE)
			ft_printf("NULL\n");
		else
		{
			int 	i = -1;
			while ((first->args)[++i])
				ft_printf("%s ", (first->args)[i]);
			ft_printf("\n");
		}
		first = first->next;
	}
}

int main(int ac, char *av[], char *env[])
{
	int	ret_gnl = 1;
	char *line = NULL;
	char **cmd;
	char **env_shell; //copy of env
	(void)av;

	if (!(env_shell = copy_env(env, 0)))
		return (error_msg("main: malloc failed\n", FAILURE));
	if (ac != 1)
	{
		ft_printf("just launch minishell exe, without any argument\n");
		exit(EXIT_FAILURE);
	}
	save_stdin = dup(STDIN_FILENO);
	save_stdout = dup(STDOUT_FILENO);
	if (init_global_path(env_shell) || init_global_home(env_shell))
	{
		free_split(env_shell);
		free(global_home);
		free(global_path);
		return (error_msg("main: malloc failed\n", FAILURE));
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
		// int i = -1;
		// while (cmd[++i])								//print le split de corentin
		// 	ft_printf("%s\n", cmd[i]);
		first_token = create_token_list(cmd);
		// print_list(first_token);						//print la liste chainee
		// ft_printf("\n\n-----------------\n\n");
		free(line);
		free_split(cmd);
		do_pipe(first_token, &env_shell);
		// if (execution(first_token, &env_shell))
		// 	ft_printf("sortie de exec_part sans aucune commande lancee\n");
		free_token_list(first_token);
		line = NULL;
		cmd = NULL;
		// ft_printf("ret fonction : %d\n", global_ret_value);
		system("leaks a.out");
		ft_printf("minishel$ ");
	}
	return (0);
}

