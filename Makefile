# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/03 18:16:44 by mburgler          #+#    #+#              #
#    Updated: 2023/05/09 21:21:35 by mburgler         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                     CONFIG                                   #
################################################################################

NAME        := so_long
CC        := cc
FLAGS    := -Wall -Wextra -Werror -g3
################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS        :=      MY_LIB/ft_printf/ft_printf.c \
                          MY_LIB/ft_printf/ft_printf_helper.c \
                          MY_LIB/ft_printf2/ft_printf2.c \
                          MY_LIB/ft_printf2/ft_printf2_helper.c \
                          MY_LIB/libft/ft_bzero.c \
                          MY_LIB/libft/ft_putstr_fd.c \
                          MY_LIB/libft/ft_memchr.c \
                          MY_LIB/libft/ft_itoa.c \
                          MY_LIB/libft/ft_isalpha.c \
                          MY_LIB/libft/ft_isdigit.c \
                          MY_LIB/libft/ft_memcmp.c \
                          MY_LIB/libft/ft_tolower.c \
                          MY_LIB/libft/ft_toupper.c \
                          MY_LIB/libft/ft_strrchr.c \
                          MY_LIB/libft/ft_isprint.c \
                          MY_LIB/libft/ft_strtrim.c \
                          MY_LIB/libft/ft_strjoin.c \
                          MY_LIB/libft/ft_strchr.c \
                          MY_LIB/libft/ft_isascii.c \
                          MY_LIB/libft/ft_strmapi.c \
                          MY_LIB/libft/ft_striteri.c \
                          MY_LIB/libft/ft_putendl_fd.c \
                          MY_LIB/libft/ft_calloc.c \
                          MY_LIB/libft/ft_strnstr.c \
                          MY_LIB/libft/ft_strlcat.c \
                          MY_LIB/libft/ft_isalnum.c \
                          MY_LIB/libft/ft_putchar_fd.c \
                          MY_LIB/libft/ft_memcpy.c \
                          MY_LIB/libft/ft_strncmp.c \
                          MY_LIB/libft/ft_putnbr_fd.c \
                          MY_LIB/libft/ft_split.c \
                          MY_LIB/libft/ft_strdup.c \
                          MY_LIB/libft/ft_substr.c \
                          MY_LIB/libft/ft_memset.c \
                          MY_LIB/libft/ft_strlcpy.c \
                          MY_LIB/libft/ft_atoi.c \
                          MY_LIB/libft/ft_strlen.c \
                          MY_LIB/libft/ft_memmove.c \
                          MY_LIB/get_next_line/get_next_line_utils_bonus.c \
                          MY_LIB/get_next_line/get_next_line_bonus.c \
                          sources/floodfill.c \
                          sources/free_ma_boi.c \
                          sources/check_map.c \
                          sources/error_handler.c \
                          sources/main.c \
                          sources/check_files.c \
                          sources/initialise.c \
                          sources/linux_event_handler.c \
                          sources/rendering.c \
                          sources/plyr.c \
                          
OBJS        := $(SRCS:.c=.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

################################################################################
#                                  Makefile  objs                              #
################################################################################

CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f

UNAME		:=	$(shell uname)

ifeq ($(UNAME), Darwin)
$(NAME): ${OBJS}
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			@ $(MAKE) -C mlx all >/dev/null 2>&1
			@ cp ./mlx/libmlx.a .
			$(CC) $(CFLAGS) -g3 -Ofast -o $(NAME) -Imlx $(OBJS) -Lmlx -lmlx -lm -framework OpenGL -framework AppKit
			@echo "$(GREEN)$(NAME) created[0m ✔️"
endif

ifeq ($(UNAME), Linux)
$(NAME): ${OBJS}
			@echo "$(GREEN)Linux compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			@chmod 777 mlx_linux/configure
			@ $(MAKE) -C mlx_linux all
			$(CC) $(CFLAGS) -g3 -o $(NAME) $(OBJS) -Imlx_linux -Lmlx_linux -lmlx -lmlx_Linux -L/usr/lib -lXext -lX11 -lm
			@echo "$(GREEN)$(NAME) created[0m ✔️"
endif

all:		${NAME}

ifeq ($(UNAME), Darwin)
clean:
			@ ${RM} *.o */*.o */*/*.o
			@ rm -rf $(NAME).dSYM >/dev/null 2>&1
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"
endif

ifeq ($(UNAME), Linux)
clean:
			@ ${RM} *.o */*.o */*/*.o
			@ rm -rf $(NAME).dSYM >/dev/null 2>&1
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"
endif


ifeq ($(UNAME), Linux)
fclean:		clean
			@ ${RM} ${NAME}
			@ $(MAKE) -C mlx_linux clean 
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"
endif

ifeq ($(UNAME), Darwin)
fclean:		clean
			@ ${RM} ${NAME}
			@ rm libmlx.a
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"
endif

re:			fclean all

.PHONY:		all clean fclean re
