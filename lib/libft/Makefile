# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/31 16:47:05 by dcherend          #+#    #+#              #
#    Updated: 2018/07/04 18:08:08 by dcherend         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC_DIR =   ./src/
OBJ_DIR =   ./
INC_DIR =   ./inc/
LIB_DIR =   ./lib
SRC =       ft_bzero.c ft_memcpy.c ft_memccpy.c ft_strcpy.c ft_strcat.c \
            ft_strchr.c ft_strrchr.c ft_strcmp.c ft_isprint.c ft_strncpy.c \
            ft_strncat.c ft_isascii.c ft_strncmp.c ft_memchr.c ft_strnstr.c \
            ft_atoi.c ft_memcmp.c ft_strlen.c ft_strlcat.c ft_memalloc.c \
            ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c ft_strstr.c \
            ft_strmap.c ft_striter.c ft_striteri.c ft_strmapi.c ft_strequ.c \
            ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c ft_putchar.c \
            ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c \
            ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strsplit.c \
            ft_memmove.c ft_strdup.c ft_tolower.c ft_toupper.c ft_isdigit.c \
            ft_isalnum.c ft_isalpha.c ft_itoa.c ft_memset.c ft_lstnew.c \
            ft_lstdelone.c ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_lstdel.c \
            get_next_line.c ft_elems.c ft_two_del.c ft_swapch.c \
            ft_strjoin_free.c ft_numlen.c ft_strsjoin.c
OBJ =       $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
all: $(NAME)
$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
$(OBJ_DIR)%.o: %.c
	gcc -Wall -Werror -Wextra -std=c99 -o $@ -c $< -I $(INC_DIR)
clean: 
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all
vpath %.c $(SRC_DIR)

