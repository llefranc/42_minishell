/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_chainlist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 15:13:01 by lucas          #+#    #+#             */
/*   Updated: 2020/10/26 18:11:04 by lucas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_list(t_token *token);


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
	if (!(copy[i] = ft_strdup(new_arg)))
		return (NULL);
	copy[i + 1] = NULL;
	free(cmd);
	return (copy);
}

/*
** Creates a new element, initializes his type / content and puts his next *ptr
** to NULL.
*/
t_token	*ft_lstnew(int type, char *content)
{
	t_token	*new;

	if (!(new = malloc(sizeof(*new))))
		return (NULL);
	new->type = type;
	new->next = NULL;
	if (!content) //if PIPE, content is NULL so no need to malloc a **char
		new->args = NULL;
	else
	{
		if (!(new->args = malloc(sizeof(*(new->args)) * 2))) //first argument + NULL terminated
			return (NULL);
		if (!(new->args[0] = ft_strdup(content)))
			return (NULL);
		new->args[1] = NULL;
	}
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
** Creates a new token element and initializes his type / content. Moves the
** index i in char **cmd if necessary (for >, >> and <). Returns the new token,
** and NULL if malloc failed.
*/
t_token	*create_token(char **cmd, int *i)
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
	else                            // command
		new_token = ft_lstnew(EXEC, cmd[*i]);
	if (!new_token) // if malloc failed
		return (NULL);
	return (new_token);
}

/*
** If *token isn't on a exec token, it creates a new one and put *token on it.
** Otherwise just adds cmd[i] to token->args. Returns NULL if malloc failed.
*/
t_token	*create_token_exec(t_token **token, char **cmd, int *i)
{
	t_token		*tmp;

	if ((*token)->type == PIPE) //if the actual token is a PIPE, we go to the end of the chainlist to create a new
		while ((*token)->next)  //token arg (because we may have add some token redirections at the back og the chainlist)
			*token = (*token)->next;
	if ((*token)->type != EXEC) //if not on a command token, we create a new one
	{
		if (!(tmp = create_token(cmd, i)))
			return (NULL);
		tmp->next = (*token)->next; //putting the new token after the actual and before others if actual token is not the last
		(*token)->next = tmp;
		*token = (*token)->next; //and we select the new token
	}
	else if (!((*token)->args = add_new_arg_to_cmd((*token)->args, cmd[*i]))) //if we already are on a command token
		return (NULL);                                                        //we just add a new arg to this one
	return (*token);
}

/*
** Puts *token at the end of the chainlist and add a pipe token.
*/
t_token	*create_token_pipe(t_token **token, char **cmd, int *i)
{
	while ((*token)->next) //pipe token will always be at the end of the actual chain list
		*token = (*token)->next;
	if (!((*token)->next = create_token(cmd, i)))
		return (NULL);
	*token = (*token)->next; //we select the new token pipe, because redirec / exec tokens to come
	return (*token);         //will all be add after this one
}

/*
** Adds at the end of the chain list a redirection token.
*/
t_token	*create_token_redirection(char **cmd, int *i)
{
	t_token	*tmp;

	if (!(tmp = create_token(cmd, i)))
		return (NULL);
	ft_lstadd_back(&first_token, tmp);
	return (tmp);
}

/*
** Tranforms the **char cmd into a tokens chainlist (3 differents tokens : 
** execution, redirection and pipe). >, >> and < will lead to a redirection
** token with (token->args)[0] = file_name. | will lead to a pipe token with
** token->args == NULL. The rest of lines will all be add in token->args in
** execution tokens.
*/
t_token	*create_token_list(char **cmd)
{
	int		i;
	t_token *token;
	t_token	*control_malloc;
	
	if (!cmd)
		return (NULL);
	control_malloc = NULL;
	i = -1;
	while (cmd[++i])
	{
		if (!i) //if first line of **char with all the tokens / arguments
		{
			if (!(first_token = create_token(cmd, &i)))	//we initialize *first_token global variable
				return (NULL);
			token = first_token;
		}
		else
		{
			if (cmd[i][0] != F_PIPE && cmd[i][0] != F_LEFT && cmd[i][0] != F_RIGHT)
				control_malloc = create_token_exec(&token, cmd, &i);    //if it's an argument of a command
			else if (cmd[i][0] == F_PIPE)
				control_malloc = create_token_pipe(&token, cmd, &i);    //if it's a pipe
			else
				control_malloc = create_token_redirection(cmd, &i);     //(i += 1 for > and <, i += 2 for >>)
			if (!control_malloc) //if a malloc failed
				return (NULL);
		}
	}
	return (first_token);
}

/*
** Frees the token chainlist.
*/
void	free_token_list(t_token *token)
{
	t_token		*tmp;
	
	while (token)
	{
		tmp = token->next;
		token->args ? free_split(token->args) : 0; //if PIPE token->args is NULL, no need to free
		free(token);
		token = tmp;
	}
}
