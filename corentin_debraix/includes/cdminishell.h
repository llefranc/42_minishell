/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdminishell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 23:53:03 by user42            #+#    #+#             */
/*   Updated: 2020/11/13 15:23:43 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CDMINISHELL_H
# define CDMINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

# include "../../lucas_lefrancq/includes/minishell.h"

# define SQUOTES	39
# define DQUOTES	34
# define BSLASH		92
# define SEMICOLON	59
# define SPACE		32

typedef	struct	s_sh
{
	char		**copyenv;
	char		**command;
	int			envlen;
	int			cmpvar;
	int			sqflag;
	int			dqflag;
	int			onemoredollar;
	int			syntaxerror;
}				t_sh;

/*
** PARSING UTILS
*/

int				ft_sepcomp(char c, char *s2, unsigned int n);
char			*ft_strcat_char(char *dest, char c);
int				ft_count_backslash(char *line, int i);
int				ft_count_backslash2(char *line, int i);
void			ft_free_doublearray(char **semicolon);
void			ft_cdsplit_and_free(t_sh *sh, char *semicolon);
void			ft_copy_env(char **env, t_sh *sh);
void			ft_putsyntax_fd(char *str, t_sh *sh, int fd);
void			ft_print_doubletabchar(char **tab);
char			*ft_strjoinfree(char *s1, char *s2);
int				create_new_env(t_sh *sh);
void			ft_init_sh(t_sh *sh);

/*
** LEXER
*/

char			*ft_lexer(char *line, t_sh *sh);
char			*ft_lexer_manage_sep(char *line, int i);
void			ft_lexer_sep_errors(t_sh *sh, char *line, int i);
char			*ft_lexer_squotes(int i, char *line, t_sh *sh);
char			*ft_lexer_dquotes(int i, char *line, t_sh *sh);
void			ft_lexer_syntax_start(char *line, t_sh *sh);
void			ft_lexer_syntax_chevron(int i, char *line, t_sh *sh);
void			ft_lexer_syntax_end(char *line, t_sh *sh);
void			ft_lexer_syntax_middle(int i, char *line, t_sh *sh);
char			*ft_lexer_escape_dollar(int i, char *line);
char			*ft_lexer_nonescape_space(int i, char *line);
char			*ft_lexer_nonescape_semicolon(int i, char *line);
char			*ft_lexer_transfo_sep(int i, char *line);
char			*ft_lexer_nonescape_sep(int *i, char *line);

/*
** PARSER
*/

void			ft_parser(char **semicolon, t_sh *sh);
void			ft_target_bslash(t_sh *sh);
void			ft_replace_path(t_sh *sh);
void			ft_take_env_path(t_sh *sh, int z, int i);
void			ft_trim_command(t_sh *sh, int z, int len);
void			ft_onemore_dollar(t_sh *sh, int z);
int				ft_handle_spaces_in_env(t_sh *sh);
void			ft_trim_quotes(t_sh *sh);
void			ft_transfo_dollars(t_sh *sh);

/*
** GNL
*/

int				get_next_line(int fd, char **line);

/*
** LIBFT
*/

void			ft_cdputstr(char *str);
char			*ft_cdstrncpy(char *dest, char *src, unsigned int n);
int				ft_cdstrncmp(char *s1, char *s2, unsigned int n);
size_t			ft_cdstrlcpy(char *dst, char *src, size_t dstsize);
char			*ft_cdstrcat(char *dest, char *src);
char			**ft_cdsplit(char const *s, char c);
int				ft_cdstrcmp(const char *s1, const char *s2);
char			*ft_cdstrjoin(char *s1, char *s2);
int				ft_cdstrlen(char *s);
char			*ft_cdstrdup(char *s1);
char			*ft_cdstrchr(char *s, int c);
char			*ft_cdstrcpy(char *dest, char *src);
char			*ft_cditoa(int n);

/*
** UTILS.C (partie Lucas)
*/

int				create_new_env(t_sh *sh);

#endif
