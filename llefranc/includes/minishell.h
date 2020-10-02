#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/errno.h>

# include "libftprintf.h"

//--------------------- UTILS ---------------------
char	*add_quotes(char *var);


char	**copy_env(char **env, int add_quotes_bool);


//--------------------- BUILTINS ---------------------
int		builtin_echo(char **args);
int		builtin_env(char **args, char **env);
int		builtin_export(char **args, char ***env);


#endif