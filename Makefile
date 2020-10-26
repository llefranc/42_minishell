# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/26 16:07:08 by llefranc          #+#    #+#              #
#    Updated: 2020/10/26 17:15:56 by llefranc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	gcc
FLAGS		=	-O3 -Wall -Wextra -Werror

SRCS_BUI	=	cd.c echo.c env.c exit.c export.c pwd.c unset.c
SRCS_EXE	=	execution.c execve_part.c pipe.c
SRCS_OTH	=	main.c signal.c tokens_chainlist.c utils.c
SRCS_LIB	=	ft_fd_printf.c ft_printf.c ft_printf_fill_param.c ft_printf_fill_param2.c \
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

OBJS_BUI	=	$(SRCS_BUI:.c=.o)
OBJS_EXE	=	$(SRCS_EXE:.c=.o)
OBJS_OTH	=	$(SRCS_OTH:.c=.o)
OBJS_LIB	=	$(SRCS_LIB:.c=.o)

PATH_BUI	=	llefranc/sh_builtins/
PATH_EXE	=	llefranc/sh_execution/
PATH_OTH	=	llefranc/sh_others/
PATH_LIB	=	llefranc/libft/

all		: 	$(NAME)

$(NAME)	:	$(addprefix $(PATH_LIB), $(OBJS_LIB)) $(addprefix $(PATH_OTH), $(OBJS_OTH)) \
			$(addprefix $(PATH_BUI), $(OBJS_BUI)) $(addprefix $(PATH_EXE), $(OBJS_EXE))
			$(CC) -o $(NAME) $(FLAGS) -I includes/\
			$(addprefix $(PATH_LIB), $(OBJS_LIB)) $(addprefix $(PATH_OTH), $(OBJS_OTH)) \
			$(addprefix $(PATH_BUI), $(OBJS_BUI)) $(addprefix $(PATH_EXE), $(OBJS_EXE))

clean	:	
				rm -rf $(addprefix $(PATH_LIB), $(OBJS_LIB)) $(addprefix $(PATH_OTH), $(OBJS_OTH)) \
				$(addprefix $(PATH_BUI), $(OBJS_BUI)) $(addprefix $(PATH_EXE), $(OBJS_EXE))

fclean	:	clean
				rm -rf $(NAME)

$(PATH_LIB)%.o		:	$(PATH_LIB)%.c
			$(CC) $(FLAGS) -o $@ -c $<

$(PATH_OTH)%.o		:	$(PATH_OTH)%.c
			$(CC) $(FLAGS) -o $@ -c $<

$(PATH_BUI)%.o		:	$(PATH_BUI)%.c
			$(CC) $(FLAGS) -o $@ -c $<

$(PATH_EXE)%.o		:	$(PATH_EXE)%.c
			$(CC) $(FLAGS) -o $@ -c $<
			

re		:	fclean all

.PHONY	:	all clean fclean re