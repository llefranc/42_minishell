/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:26:42 by llefranc          #+#    #+#             */
/*   Updated: 2020/10/19 11:24:49 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <locale.h>
# include <stdlib.h>

# include "libft.h"
# include "float.h"
# include "wchar.h"

# define BUFF_SIZE 1024
# define MAX_DIGIT	1030 //lib big int floats
# define BIG_INT	1000 //lib big int floats

typedef struct	s_elem
{
	int			count;
	char		b_wri[BUFF_SIZE + 1];
	int			bw;
	char		b_con[BUFF_SIZE + 1];
	char		*b_str;
	char		size_type[4];
	void		*ptr_n;
	int			boo_pre;
	int			val_pre;
	int			boo_wid;
	int			val_wid;
	int			fl_has;
	int			fl_sig;
	int			fl_zer;
	int			fl_rev;
	int			fl_spa;
}				t_elem;

/*
** La struct s_number est utilisee pour des calculs sur des chaines de
** caracteres permettant de reprensenter des gros ints.
** i et j sont les indexs permettant de se deplacer dans la chaine 1 et
** la chaine 2. s1FirD represente líndex du premier chiffre different de
** zero dans la chaine 1. Meme chose pour s2FirD mais pour la seconde chaine.
*/

typedef struct	s_number
{
	int			i;
	int			j;
	int			s1fird;
	int			s2fird;
}				t_number;

/*
** --------- FT_FD_PRINTF.C ---------
*/

int		ft_fd_printf(int fd, const char *str, ...);
int		fd_str_print(int fd, const char *str, va_list ap);
void	fd_buf_pri_res(int fd, t_elem *par);


/*
** --------- FT_PRINTF.C ---------
*/

int				ft_printf(const char *str, ...);
int				str_check(const char *str);
int				str_print(const char *str, va_list ap);

/*
** ------------------------------------------
** --------- FT_PRINTF_FILL_PARAM.C ---------
** ------------------------------------------
*/

void			init_struct(t_elem *par, int resall);
void			fill_param(const char *str, int *i, t_elem *par);
int				fill_param_flags(const char *str, int *i, t_elem *par);
int				fill_param_boo_witdh(const char *str, int *i, t_elem *par);

/*
** --------- FT_PRINTF_FILL_PARAM2.C ---------
*/

int				fill_param_boo_preci(const char *str, int *i, t_elem *par);
void			fill_param_boo_preci2(const char *str, int *i, t_elem *par);
int				fill_param_size(const char *str, int *i, t_elem *par);
void			fill_param_size2(const char *str, int *i,
								t_elem *par, int nbchar);

/*
** --------- FT_PRINTF_FILL_PARAM3.C ---------
*/

int				fill_param_type(const char *str, int *i, t_elem *par);
int				fill_param_type2(char type, int *i, t_elem *par);
int				fill_param_type3(const char *str, int *i, t_elem *par);

/*
** -------------------------------------------
** --------- FT_PRINTF_CHECK_PARAM.C ---------
** -------------------------------------------
*/

int				check_param(t_elem *par);
int				check_size_type(t_elem *par);
int				check_precision(t_elem *par);
int				check_width(t_elem *par);
int				check_flags_zero(t_elem *par);

/*
** --------- FT_PRINTF_CHECK_PARAM2.C ---------
*/

int				check_flags_rev(t_elem *par);
int				check_flags_signed(t_elem *par);
int				check_flags_hashtag(t_elem *par);
int				check_flags_space(t_elem *par);

/*
** ------------------------------------
** --------- FT_PRINTF_CONV.C ---------
** ------------------------------------
*/

void			buf_pri_res(t_elem *par);
void			get_asterisk(t_elem *par, va_list ap);
void			simp_param(t_elem *par);
void			buf_fill(t_elem *par, char *str, char c, int nbchar);
void			str_conv(const char *str, t_elem *par, va_list ap, int *s);

/*
** --------- FT_PRINTF_CONV_CDI.C ---------
*/

void			str_conv_c(t_elem *par, va_list ap);
void			str_conv_di(t_elem *par, va_list ap);
void			str_conv_di2(t_elem *par);
void			str_conv_di2_suite(t_elem *par);
void			str_conv_di3(t_elem *par);

/*
** --------- FT_PRINTF_CONV_UNP.C ---------
*/

void			str_conv_u(t_elem *par, va_list ap);
void			str_conv_u2(t_elem *par);
void			str_conv_u3(t_elem *par);
void			str_conv_n(t_elem *par, va_list ap);
void			str_conv_p(t_elem *par, va_list ap);

/*
** --------- FT_PRINTF_CONV_x.C ---------
*/

void			str_conv_x(t_elem *par, va_list ap);
void			str_conv_x_suite(t_elem *par, va_list ap);
void			str_conv_x2(t_elem *par);
void			str_conv_x2_suite(t_elem *par);
void			str_conv_x3(t_elem *par);

/*
** --------- FT_PRINTF_CONV_S.C ---------
*/

void			str_conv_s(t_elem *par, va_list ap);
void			str_conv_s2(t_elem *par);
void			str_conv_s3(t_elem *par);

/*
** --------- FT_PRINTF_CONV_F.C ---------
*/

void			str_conv_f(t_elem *par, va_list ap);
void			str_conv_f_suite(t_elem *par, int *i);
void			str_conv_f2(t_elem *par);
void			str_conv_f2_suite(t_elem *par);
void			str_conv_f3(t_elem *par);

/*
** --------- FT_PRINTF_CONV_E.C ---------
*/

void			str_conv_e(t_elem *par, va_list ap);
int				str_conv_e2(t_elem *par);
int				str_conv_e2_suite(t_elem *par, int *i, int exp);
int				check_zero(char *dblchar);
void			str_conv_e3(t_elem *par, int *exp);
void			str_conv_e4(t_elem *par, int *exp);

/*
** --------- FT_PRINTF_CONV_G.C ---------
*/

void			str_conv_g(t_elem *par, va_list ap);
void			str_conv_g2(t_elem *par);
void			str_conv_g3(t_elem *par, double dbl);
void			str_conv_g31(t_elem *par, int i);
void			str_conv_g_nbsig(t_elem *par);
void			str_conv_g_nbsig_suite(t_elem *par, int nbsig, int nbzerbef);
void			str_conv_g_nbsig2(t_elem *par);
void			str_conv_g32(t_elem *par);
void			str_conv_g_trimzero(t_elem *par);
void			str_conv_g4(t_elem *par, int *exp);

/*
** --------- FT_PRINTF_CONV_LCLS.C ---------
*/

void			str_conv_lc(t_elem *par, va_list ap);
void			buf_fill_wchar(t_elem *par, char *str);
void			str_conv_ls(t_elem *par, va_list ap);
void			str_conv_ls2(t_elem *par);
void			str_conv_ls3(t_elem *par);

/*
** --------- FT_PRINTF_CONV_OTHERS.C ---------
*/

void			str_conv_modu(t_elem *par, va_list ap);
void			str_conv_efg_inf(t_elem *par);
void			str_conv_efg_inf_suite(t_elem *par);
void			str_conv_efg_inf2(t_elem *par);
void			str_conv_efg_nan(t_elem *par);

// WCHAR
char			*wchar_to_utf8(wchar_t carac);
char			*wcharstr_to_utf8(wchar_t *carac);
int				wchar_utf8_len(wchar_t carac);
void			conv_utf8_1oct(wchar_t carac, char *str_utf8);
void			conv_utf8_2oct(wchar_t carac, char *str_utf8);
void			conv_utf8_3oct(wchar_t carac, char *str_utf8);
void			conv_utf8_4oct(wchar_t carac, char *str_utf8);

// FLOATS + BIG INT
/*
** --------- BIG_INT_ADD.C ---------
*/

char			*big_int_add(char *s1, char *s2);
void			big_int_add2(char *s1, char *s2, t_number *num);
char			*big_int_add3(char *s1);
char			*big_int_add4(char *s1, char *s2);
char			*big_int_add5(char *s1, char *s2);

/*
** --------- BIG_INT_SUBS.C && BIG_INT_SUBS2.C ---------
*/

char			*big_int_subs(char *s1, char *s2);
void			big_int_subs2(char *s1, char *s2, t_number *num);
char			*big_int_subs3(char *s1);
void			big_int_subs4(char *s1, char *s2);
void			big_int_subs5(char *s1, char *s2, t_number *num);
void			big_int_subs6(char *s1, char *s2);
void			big_int_subs7(char *s1, char *s2, t_number *num);

/*
** --------- BIG_INT_MULT_POW.C ---------
*/

char			*big_int_mult(char *s1, char *s2);
char			*big_int_mult2(char *s1, char *s2, t_number *num);
void			big_int_mult3(char *s1, t_number *num);
char			*big_int_pow(char *s1, unsigned int pow);

/*
** --------- BIG_INT_DIV.C ---------
*/

char			*big_int_div(char *s1, char *s2);
void			big_int_div2(char *s1, char *s2, char *res, t_number *num);
void			big_int_div3(char numer[], char denom[]);
void			big_int_div4(char *s1, char *s2, char *tmp, long *nb);

/*
** --------- PRINT_BITS.C ---------
*/

void			print_mantissa(char *str);
void			print_octet(char *str);
char			*str_bits(void *type, size_t size);
char			*fill_zero(char *str);

/*
** --------- BIG_INTS_INIT.C ---------
*/

int				get_val_exp(char *strbits);
unsigned long	get_val_man(char *strbits);
char			*fill_numerator(char *num, unsigned long valman, long valexp);
char			*fill_denominator(char *deno, long valexp, double nb);
int				get_digit_exp(double nb);

/*
** --------- BIG_INTS_CALC.C ---------
*/

void			init_num_struct(char *s1, char *s2, t_number *num);
int				big_int_comp(char *s1, char *s2);
char			*big_int_reset(char *str, char signe);
char			*pow_table2(char *bigint, unsigned long valexp);
void			frac_sci_notation(char *num, char *deno, int digitexp);

/*
** --------- DOUBLE_TO_CHAR.C && DOUBLE_TO_CHAR2 ---------
*/

char			*dbltoa(double dbl);
char			*fill_frac(double dbl, char num[], char den[]);
char			*fi_inf(double dbl, char *dblchar, char *strbits,
						unsigned long valman);
char			*fill_char_double(char *dbl, char *num,
						char *deno, int digitexp);
char			*fill_char_double2(char dix[], char zero[],
						int *digitexp, int *len);
void			fill_char_double3(char *dbl, char *num,
						int *len, int *digitexp);
int				fill_char_double4(char *dbl, char *num, char *deno);

/*
** --------- ROUND_DBLSTR.C && ROUND_DBLSTR2.C ---------
*/

void			round_up_int(char *dblchar, char tmp[], int len, int i);
void			round_up(char *dblchar, int prec, int i);
char			*round_dblstr(char *dblchar, int prec);
void			round_dblstr2(char *dblchar, int prec, int i, int j);
void			round_dblstr3(char *dblchar, int prec);
char			*round_dblstr4(char *dblchar, int i);

#endif
