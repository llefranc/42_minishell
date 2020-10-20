/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 12:28:48 by llefranc          #+#    #+#             */
/*   Updated: 2020/10/20 12:23:15 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Prints an error message on stdout and returns the error value.
*/
int		error_msg(char *msg, int return_value)
{
	ft_fd_printf(STDERR_FILENO, "minishell: %s", msg);
	return (return_value);
}

/*
** Prints an error message on stdout and returns NULL.
*/
void	*error_msg_ptr(char *msg, void *ptr)
{
	ft_fd_printf(STDERR_FILENO, "minishell: %s", msg);
	return (ptr);
}

/*
** Takes a **char cmd to add a new argument to the command. Returns a new
** **char copy_cmd and frees the previous **char cmd.
*/
char	**add_new_arg_to_cmd(char **cmd, char *new_arg)
{
	char	**copy;
	int		i;
	
	i = 0;
	while (cmd[i]) //number of args
		i++;
	if (!(copy = malloc(sizeof(*copy) * (i + 2)))) //+2 because cmd array is NULL terminated and new arg to add
		return (NULL);
	i = -1;
	while (cmd[++i])
		copy[i] = cmd[i]; //copying previous args
	copy[i] = new_arg;
	copy[i + 1] = NULL;
	free(cmd);
	return (copy);
}

/*
** Creates a new element.
*/
t_token	*ft_lstnew(int type, char *content)
{
	t_token	*new;

	if (!(new = malloc(sizeof(*new))))
		return (NULL);
	if (!(new->args = malloc(sizeof(*(new->args)) * 2))) //first argument + NULL terminated
		return (NULL);
	new->args[0] = content;
	new->args[1] = NULL;
	new->type = type;
	new->next = NULL;
	return (new);
}

/*
** Adds one element to the front of the chain list.
*/
void	ft_lstadd_front(t_token **first, t_token *new)
{
	if (!first || !new)
		return ;
	if (!(*first))
		*first = new;
	else
	{
		new->next = *first;
		*first = new;
	}
}

/*
** Adds one element to the back of the chain list.
*/
void	ft_lstadd_back(t_token **first, t_token *new)
{
	if (!first)
		return ;
	if (!(*first))
		*first = new;
	else
	{
		while ((*first)->next)
			first = &(*first)->next;
		(*first)->next = new;
	}
}

/*
** Creates a new token element and initializes his type / content.
*/
t_token	*create_new_token(char **cmd, int *i)
{
	t_token	*new_token;

	new_token = NULL;
	if (cmd[*i][0] == F_LEFT) // < input_file.txt
		new_token = ft_lstnew(INPUT, cmd[(*i)++ + 1]);
	else if (cmd[*i][0] == F_RIGHT && cmd[*i + 1][0] != F_RIGHT) // > output_file.txt
		new_token = ft_lstnew(OUTPUT, cmd[(*i)++ + 1]);
	else if (cmd[*i][0] == F_RIGHT) // >> output_file_append.txt
	{
		new_token = ft_lstnew(OUTPUT_ADD, cmd[*i + 2]);
		*i += 2;
	}
	else if (cmd[*i][0] == F_PIPE) // | pipe
		new_token = ft_lstnew(PIPE, NULL);
	else							// command
		new_token = ft_lstnew(EXEC, cmd[*i]);
	if (!new_token) // if malloc failed
		return (NULL);
	return (new_token);
}

t_token	*create_list(char **cmd)
{
	int		i;
	t_token *token;
	t_token	*tmp;
	
	if (!cmd)
		return (NULL);
	i = -1;
	while (cmd[++i])
	{
		tmp = NULL;
		if (!i) //if first line of **char
		{
			if (!(first_token = create_new_token(cmd, &i)))
				return (NULL);
			token = first_token;
		}
		else
		{
			if (cmd[i][0] != F_PIPE && cmd[i][0] != F_LEFT && cmd[i][0] != F_RIGHT) //si c'est un arg d'une commande
			{
				if (token->type == PIPE) //si on est sur un pipe, on se positionne au bout de la chaine pour creer le new
					while (token->next)  //token arg (car on a peut etre deja ajoute avec lst_addback des tokens redirections)
						token = token->next;
				if (token->type != EXEC) //si on est pas sur un token commande
				{
					if (!(token->next = create_new_token(cmd, &i))) //on cree new token avec la ligne arg
						return (NULL);
					token = token->next; //et on se place sur le new token cree
				}
				else if (!(token->args = add_new_arg_to_cmd(token->args, cmd[i])))	//si on est sur un token commande on
					return (NULL);													//ajoute juste un arg
			}
			else if (cmd[i][0] == F_PIPE) //si on arrive sur une ligne pipe dans cmd
			{
				while (token->next) //le token pipe se trouvera toujours a la fin de la liste chainee actuelle
					token = token->next;
				if (!(token->next = create_new_token(cmd, &i))) //on cree un new token pipe
					return (NULL);
				token = token->next; //on se place sur le new token pipe >> si c'est un arg, il va du coup creer un new token
			}						 //si c'est une redirection il ajoute a la fin donc good aussi en theorie
			else //sinon c'est un token redirection, on le met a la fin
			{
				if (!(tmp = create_new_token(cmd, &i)))
					return (NULL);
				ft_lstadd_back(&first_token, tmp);
			}
		}
	}
	return (first_token);
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