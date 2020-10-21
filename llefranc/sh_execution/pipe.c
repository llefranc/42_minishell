/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 17:20:08 by llefranc          #+#    #+#             */
/*   Updated: 2020/10/21 17:22:10 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Executes the redirections and the command. Frees all the variables allocated
** and then exits the process.
*/
int		pipe_exec_son(t_token *token, t_token *tmp, char ***env, int fdpipe[2], int fd_in)
{
	close(fdpipe[0]); //son is taking the input previously save from STDIN / or a previous pipe (fd_in)
	dup2(fd_in, STDIN_FILENO); //if there was a pipe before, connecting this command to previous one
	if (tmp) //if there is an other pipe after this command we redirect its output into the pipe_fd
		dup2(fdpipe[1], STDOUT_FILENO); //otherwise this command is the last one and will print to stdout
	execution(token, env);
	close(fd_in);
	close(fdpipe[1]);
	free(global_path); //freeing all the variables because this is a forked process (son)
	free(global_home); //and it will exit
	free_split(*env);
	free_token_list(first_token);
	exit(SUCCESS);
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
	pid_t		pid;
	int			fdpipe[2];
	int			fd_in; //for saving the input of next command to be executed
	int			status;
                          //for the first execution of the pipe, the left part
	fd_in = STDIN_FILENO; //doesn't take any input
	tmp = token;
	while (tmp && tmp->type != PIPE)
		tmp = tmp->next;
	if (!tmp)            //if *tmp == NULL, there is no pipe to do, normal execution
		execution(token, env);
	else
	{
		while (token)
		{
			pipe(fdpipe);
			pid = fork();
			if (pid == -1)
				return (global_ret_value = error_msg("pipe: fork failed\n", FAILURE));
			else if (!pid)
				pipe_exec_son(token, tmp, env, fdpipe, fd_in); //exec each parts / redirections between pipes
			else
			{
				close(fdpipe[1]);
				waitpid(pid, &status, 0); //waiting for the son to be executed
				fd_in = fdpipe[0]; //saving pipe_input, will be use in the next loop
			}                      //iteration inside son function
			move_to_next_pipe(&token, &tmp);
		}
	}
	global_ret_value = WEXITSTATUS(status); //exit code of last command executed
	return (SUCCESS);
}