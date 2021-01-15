/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 17:20:08 by lucas          #+#    #+#             */
/*   Updated: 2020/10/24 12:27:04 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Executes the redirections and the command. Frees all the variables allocated
** and then exits the process.
*/
int		pipe_exec_son(t_token *token, t_token *tmp, char ***env, int fdpipe[2], int fd_in)
{
	dup2(fd_in, STDIN_FILENO); //if there was a pipe before, connecting this command to previous one
	if (tmp) //if there is an other pipe after this command we redirect its output into the fdpipe
		dup2(fdpipe[1], STDOUT_FILENO); //otherwise this command is the last one and will print to stdout
	close(fd_in);     //now saved in STDIN
	close(fdpipe[0]); //son is taking the input previously save from STDIN / or a previous pipe (fd_in)
	close(fdpipe[1]); //now saved in STDOUT if there is a next command
	execution(token, env);
	free(global_path);
	free(global_home);
	free_split(*env);
	free_token_list(first_token);
	exit(global_ret_value); //sets in execve_part
}

/*
** Goes to the next pipe to execute, and checks if there is one more to do.
** ex : ls | head | wc >> if *token was on ls, it's now on head part and *tmp
** isn't NULL and is on wc (so we can now that there is still one pipe to
** execute after this one).
*/
void	move_to_next_pipe(t_token **token, t_token **tmp)
{
	while (*token && (*token)->type != PIPE) //moving to next part of the pipe
		*token = (*token)->next;
	if ((*token) && (*token)->type == PIPE)
		*token = (*token)->next;
	*tmp = *token;
	while ((*tmp) && (*tmp)->type != PIPE) //checking if there is another pipe to execute
		*tmp = (*tmp)->next;               //after the actual one
}

/*
** Executes commands / redirections between each pipes. Sets global_ret_value
** to the exit code value of the last command executed (ex : ls | head | wc >> wc exit code).
*/
int		do_pipe(t_token *token, char ***env)
{
	t_token		*tmp;
	int			fdpipe[2];
	int			fd_in; //for saving the input of next command to be executed
	int			status;
	int			nb_wait;
	
	status = 0;
	tmp = token;
	nb_wait = 0;
	while (tmp && tmp->type != PIPE)
		tmp = tmp->next;
	if (!tmp)            //if *tmp == NULL, there is no pipe to do, normal execution
		execution(token, env);
	else
	{
		fd_in = dup(STDIN_FILENO);
		while (token)
		{
			if (pipe(fdpipe) == -1)
				return (global_ret_value = error_msg("pipe: pipe failed\n", FAILURE));
			if ((pid = fork()) == -1)
				return (global_ret_value = error_msg("pipe: fork failed\n", FAILURE));
			else if (!pid)       //son
				pipe_exec_son(token, tmp, env, fdpipe, fd_in);
			else                //parent
			{
				close(fd_in);           //we will copy pipe_intput inside
				fd_in = dup(fdpipe[0]); //saving pipe_input, will be use in the next loop
				close(fdpipe[0]);       //saved in fd_in
				close(fdpipe[1]);       //not used
				nb_wait++;
			}
			move_to_next_pipe(&token, &tmp);
		}
		close(fd_in); //close last save of fdpipe[0]
		while (nb_wait-- >= 0) //waiting that all the processes launched end
			if (wait(&status) == pid)
				global_ret_value = WEXITSTATUS(status);
	}
	return (SUCCESS);
}
