#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/errno.h>

# include "libftprintf.h"

int		builtin_echo(char **args);

#endif