#include "../includes/minishell.h"

/*
** Check if echo command is followed by one or more "-n" option.
** "-n -nnnnn -n -nn" is valid for exemple.
*/
char	**echo_n_opt(char **args, int *n_opt)
{
	int		i;

	while (*args && (*args)[0] == '-' && (*args)[1] == 'n') //checking all the "-n" 
	{
		i = 2; //because first 2 characters are "-n"
		while ((*args)[i] == 'n')
			i++;
		if ((*args)[i] == '\0')	//if '\0', only n in the string
			*n_opt = 1;			//so we indicate that there is at leat one valid "-n"
		else
			return (args);		//otherwise it's not "-n" >> it's an arg that echo need to print
		args++;
	}
	return (args);
}

/*
** Prints the args on stdoud, separated by one space, and end the line by '\n'.
** If "-n" option is present, doesn't print the last '\n'. 
*/
int		builtin_echo(char **args)
{
	int		i;
	int		n_opt;

	n_opt = 0;
	i = 0;
	args++; //args[0] == "echo" str
	if (!(*args))
	{
		ft_printf("\n");
		return (0);
	}
	args = echo_n_opt(args, &n_opt); //looking for n_opt
	while(args[i]) //printing each arg separated by a space
	{
		ft_printf("%s", args[i++]);
		args[i] ? ft_printf(" ") : 0;
	}
	if (!n_opt) //if no option -n, we print a '\n'
		ft_printf("\n");
	return (0);
}