# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: corentindebraix <corentindebraix@studen    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/26 16:07:08 by llefranc          #+#    #+#              #
#    Updated: 2020/11/08 23:11:56 by corentindeb      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror -g -fsanitize=address

SRCS_LL_BUI	=	cd.c echo.c env.c exit.c export.c pwd.c unset.c
SRCS_LL_EXE	=	execution.c execve_part.c pipe.c
SRCS_LL_OTH	=	main.c signal.c tokens_chainlist.c utils.c
SRCS_LL_LIB	=	ft_fd_printf.c ft_printf.c ft_printf_fill_param.c ft_printf_fill_param2.c \
				ft_printf_fill_param3.c ft_printf_check_param.c \
				ft_printf_check_param2.c ft_printf_conv.c ft_printf_conv_cdi.c \
				ft_printf_conv_unp.c ft_printf_conv_x.c ft_printf_conv_s.c \
				ft_printf_conv_f.c ft_printf_conv_e.c ft_printf_conv_e2.c ft_printf_conv_g.c \
				ft_printf_conv_g2.c ft_printf_conv_lcls.c ft_printf_conv_others.c \
				big_int_add.c big_int_subs.c big_int_subs2.c big_int_mult_pow.c \
				big_int_div.c big_ints_init.c big_ints_calc.c print_bits.c \
				double_to_char.c double_to_char2.c round_dblstr.c round_dblstr2.c \
				wchar_conv.c wchar.c ft_atoi.c ft_calloc.c ft_isalpha.c ft_isdigit.c ft_pow.c \
				ft_memccpy.c ft_memcmp.c ft_memmove.c ft_strchr.c \
				ft_strlcat.c ft_strlen.c ft_strnstr.c ft_tolower.c \
				ft_bzero.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strisdigit.c \
				ft_memchr.c ft_memcpy.c ft_memset.c ft_strdup.c \
				ft_strlcpy.c ft_strncmp.c ft_strrchr.c ft_toupper.c \
				ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_free_split.c \
				ft_itoa.c ft_itoa_base.c ft_itoa_buffer.c ft_itoa_buffer_uns.c \
				ft_itoa_base_buffer_uns.c ft_strmapi.c ft_putchar_fd.c \
				ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strcmp.c \
				ft_convert_base.c ft_convert_base2.c ft_replace_char.c \
				get_next_line.c get_next_line_utils.c

SRCS_CD_LEX	=	ft_lexer.c ft_lexer2.c ft_lexer3.c ft_lexer4.c
SRCS_CD_LIB	=	ft_cditoa.c ft_cdputstr.c ft_cdstrcat.c ft_cdstrcmp.c ft_cdstrdup.c ft_cdstrlcpy.c ft_cdstrncmp.c \
				ft_cdsplit.c ft_cdstrchr.c ft_cdstrcpy.c ft_cdstrjoin.c ft_cdstrlen.c ft_cdstrncpy.c
SRCS_CD_PAR	=	ft_parser.c ft_replace_path.c ft_target_bslash.c ft_transfo_dollars.c ft_trim_quotes.c \
				ft_handle_spaces_in_env.c ft_trim_command.c ft_take_env_path.c
SRCS_CD_UTI	=	ft_copy_env.c ft_free_doublearray.c ft_sepcomp.c ft_strcat_char.c \
				ft_count_backslash.c ft_putsyntax_fd.c ft_split_and_free.c ft_strjoinfree.c


OBJS_LL_BUI	=	$(SRCS_LL_BUI:.c=.o)
OBJS_LL_EXE	=	$(SRCS_LL_EXE:.c=.o)
OBJS_LL_OTH	=	$(SRCS_LL_OTH:.c=.o)
OBJS_LL_LIB	=	$(SRCS_LL_LIB:.c=.o)

OBJS_CD_LEX	=	$(SRCS_CD_LEX:.c=.o)
OBJS_CD_LIB	=	$(SRCS_CD_LIB:.c=.o)
OBJS_CD_PAR	=	$(SRCS_CD_PAR:.c=.o)
OBJS_CD_UTI	=	$(SRCS_CD_UTI:.c=.o)

PATH_LL_BUI	=	lucas_lefrancq/sh_builtins/
PATH_LL_EXE	=	lucas_lefrancq/sh_execution/
PATH_LL_OTH	=	lucas_lefrancq/sh_others/
PATH_LL_LIB	=	lucas_lefrancq/libft/

PATH_CD_LEX	=	corentin_debraix/lexer/
PATH_CD_LIB	=	corentin_debraix/libft/
PATH_CD_PAR	=	corentin_debraix/parser/
PATH_CD_UTI	=	corentin_debraix/parsing_utils/

all		: 	$(NAME)

$(NAME)	:	$(addprefix $(PATH_LL_LIB), $(OBJS_LL_LIB)) $(addprefix $(PATH_LL_OTH), $(OBJS_LL_OTH)) \
			$(addprefix $(PATH_LL_BUI), $(OBJS_LL_BUI)) $(addprefix $(PATH_LL_EXE), $(OBJS_LL_EXE)) \
			$(addprefix $(PATH_CD_LEX), $(OBJS_CD_LEX)) $(addprefix $(PATH_CD_LIB), $(OBJS_CD_LIB)) \
			$(addprefix $(PATH_CD_PAR), $(OBJS_CD_PAR)) $(addprefix $(PATH_CD_UTI), $(OBJS_CD_UTI))
			$(CC) -o $(NAME) $(FLAGS) \
			$(addprefix $(PATH_LL_LIB), $(OBJS_LL_LIB)) $(addprefix $(PATH_LL_OTH), $(OBJS_LL_OTH)) \
			$(addprefix $(PATH_LL_BUI), $(OBJS_LL_BUI)) $(addprefix $(PATH_LL_EXE), $(OBJS_LL_EXE)) \
			$(addprefix $(PATH_CD_LEX), $(OBJS_CD_LEX)) $(addprefix $(PATH_CD_LIB), $(OBJS_CD_LIB)) \
			$(addprefix $(PATH_CD_PAR), $(OBJS_CD_PAR)) $(addprefix $(PATH_CD_UTI), $(OBJS_CD_UTI))

clean	:	
				rm -rf $(addprefix $(PATH_LL_LIB), $(OBJS_LL_LIB)) $(addprefix $(PATH_LL_OTH), $(OBJS_LL_OTH)) \
				$(addprefix $(PATH_LL_BUI), $(OBJS_LL_BUI)) $(addprefix $(PATH_LL_EXE), $(OBJS_LL_EXE)) \
				$(addprefix $(PATH_CD_LEX), $(OBJS_CD_LEX)) $(addprefix $(PATH_CD_LIB), $(OBJS_CD_LIB)) \
				$(addprefix $(PATH_CD_PAR), $(OBJS_CD_PAR)) $(addprefix $(PATH_CD_UTI), $(OBJS_CD_UTI))

fclean	:	clean
				rm -rf $(NAME)

$(PATH_LL_LIB)%.o		:	$(PATH_LL_LIB)%.c
			$(CC) $(FLAGS) -o $@ -c $<

$(PATH_LL_OTH)%.o		:	$(PATH_LL_OTH)%.c
			$(CC) $(FLAGS) -o $@ -c $<

$(PATH_LL_BUI)%.o		:	$(PATH_LL_BUI)%.c
			$(CC) $(FLAGS) -o $@ -c $<

$(PATH_LL_EXE)%.o		:	$(PATH_LL_EXE)%.c
			$(CC) $(FLAGS) -o $@ -c $<
			
$(PATH_CD_LEX)%.o		:	$(PATH_CD_LEX)%.c
			$(CC) $(FLAGS) -o $@ -c $<

$(PATH_CD_LIB)%.o		:	$(PATH_CD_LIB)%.c
			$(CC) $(FLAGS) -o $@ -c $<

$(PATH_CD_PAR)%.o		:	$(PATH_CD_PAR)%.c
			$(CC) $(FLAGS) -o $@ -c $<

$(PATH_CD_UTI)%.o		:	$(PATH_CD_UTI)%.c
			$(CC) $(FLAGS) -o $@ -c $<

re		:	fclean all

.PHONY	:	all clean fclean re
