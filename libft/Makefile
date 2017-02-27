# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/22 15:11:22 by tmoska            #+#    #+#              #
#    Updated: 2017/02/27 22:40:14 by tmoska           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = -Wall -Werror -Wextra -I./includes -g
NAME = libft.a
LIB_NAME = libft.h
SOURCES =	ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
					ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstadd.c ft_lstdel.c \
					ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c ft_memalloc.c \
					ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c \
					ft_memmove.c ft_memset.c ft_putchar.c ft_putchar_fd.c ft_putendl.c \
					ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c \
					ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c \
					ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c ft_striteri.c \
					ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c \
					ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c \
					ft_strnstr.c ft_strrchr.c ft_strsplit.c ft_strstr.c ft_strsub.c \
					ft_strtrim.c ft_tolower.c ft_toupper.c ft_lstrev.c ft_lstsort.c \
					ft_lstsize.c ft_lstforeach.c ft_lstmerge.c ft_lstrmif.c ft_ptrequ.c \
					ft_get_path.c ft_lst_create_elem.c ft_lst_removenode.c ft_basename.c \
					ft_lst_remove_if.c ft_count_umax_digits.c ft_itoa_ularge.c \
					ft_put_justified_str.c ft_put_justified_nbr.c ft_putchar_if.c \
					ft_lst_in_list.c ft_lstadd_back.c ft_lst_clear.c ft_char_arr_len.c \
					ft_strisblank.c ft_str2del.c ft_str2len.c ft_strndelat.c \
					ft_str2new.c ft_str2dup.c get_next_line.c ft_str3join.c \
					ft_strlen_until.c ft_str2join.c ft_strtrim_char.c ft_strndup.c

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)
	@echo "\033[0;32mSuccess: \033[0mmake done"

%.o: %.c
	@$(CC) $(FLAGS) -c -o $@ $<

clean:
	@rm -f $(OBJECTS)
	@find . \( -name ".DS_Store" \) -delete

fclean: clean
	@rm -f $(NAME)

re: fclean all
