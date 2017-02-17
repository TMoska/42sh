# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moska <moska@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/07 21:40:09 by moska             #+#    #+#              #
#    Updated: 2017/02/16 23:37:13 by moska            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GCC 		= gcc
# GCC 		= clang -fsanitize=memory
NAME 		= minishell
FLAGS 		= -Wall -Werror -Wextra -g

LIB_PATH	= libft
LIB			= $(LIB_PATH)/libft.a
LIB_LINK	= -L $(LIB_PATH) -lft

INC_DIR 	= includes
INC_FLAGS 	= -I./includes -I $(LIB_PATH)/includes

SRC_DIR 	= srcs
SRC_FILES = main.c prompt.c reading.c shell.c interpreting.c validating.c \
						command.c cleaning.c builtins.c builtins/builtin_exit.c

SOURCES		= $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJECTS		= $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(LIB) $(OBJECTS)
	@$(CC) $(FLAGS) -o $@ $^ $(LIB_LINK)
	@echo "\033[0;32mSuccess: \033[0mminishell compiled"
	@echo "\033[0;32mDone"

$(LIB):
	@make -C $(LIB_PATH)

%.o: %.c $(INC_DIR)/*.h
	@$(CC) $(FLAGS) $(INC_FLAGS) -c -o $@ $<

clean:
	@rm -f $(OBJECTS)
	@find . \( -name "*~" -o -name "*.swp" -o -name ".DS_Store" \) -delete
	@make clean -C $(LIB_PATH)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIB_PATH)
	
re: fclean all
