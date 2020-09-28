#include "../includes/minishell.h"

//echo >>> output
//cd
//pwd >>> output
//export
//unset
//env >> output
//exit

//fonction qui remet les commandes en minuscule
//echo -nnnnnn -n -n -n 
//export sans rien affiche env trié

//parseur doit retraiter auparavant les guillemets  
//parseur premier lecture pour voir si grammaire est correct >> puis traiter commande par commande
//ne pas gerer les doubles pipe etc >> renvoyer les erreurs
// cat < notes.txt > test.fsfds > test2
// si " >> multiligne


char	**echo_n_opt(char **args, int *n_opt)
{
	int		i;

	while (args && (*args)[0] == '-' && (*args)[1] == 'n')
	{
		i = 2;
		while ((*args)[i] == 'n')
			i++;
		if ((*args)[i] == '\0')
			*n_opt = 1;
		else
			return (args);
		args++;
	}
	return (args);
}

int		builtin_echo(char **args)
{
	int		i;
	int		n_opt;

	n_opt = 0;
	i = 0;
	args++; ////args[0] == echo command
	args = echo_n_opt(args, &n_opt); //looking for n_opt
	while(args[i]) //printing each arg separated by a space
	{
		ft_putstr_fd(args[i++], 1);
		ft_putchar_fd(' ', 1);
	}
	if (!n_opt) //if no option -n, we print a '\n'
		ft_putchar_fd('\n', 1);
	return (0);
}