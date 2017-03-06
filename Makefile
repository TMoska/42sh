# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moska <moska@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/07 21:40:09 by moska             #+#    #+#              #
#    Updated: 2017/03/06 16:14:38 by tmoska           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GCC 		= gcc
# GCC 		= clang -fsanitize=memory
NAME 		= 21sh
FLAGS 		= -Wall -Werror -Wextra -g

LIB_PATH	= libft
LIB			= $(LIB_PATH)/libft.a
LIB_LINK	= -L $(LIB_PATH) -lft
EXTRA_LIB = -ltermcap

INC_DIR 	= includes
INC_FLAGS 	= -I./includes -I $(LIB_PATH)/includes

SRC_DIR 	= srcs
SRC_FILES = main.c prompt.c shell.c interpreting.c validating.c \
command.c cleaning.c builtins.c builtins/builtin_exit.c builtins/builtin_env.c \
builtins/builtin_getenv.c env_list/utils.c env_list/utils2.c \
builtins/builtin_setenv.c builtins/builtin_unsetenv.c terminal/cut_copy_line.c \
builtins/builtin_env_utilities.c builtins/builtin_env_utilities2.c \
builtins/builtin_env_prints.c builtins/builtin_cd.c builtins/builtin_echo.c \
builtins/builtin_cd_utilities.c builtins/builtin_cd_utilities2.c \
builtins/builtin_cd_utilities3.c interpreting_utilities.c history/history.c \
reading/reader.c terminal/term_init.c terminal/cursor_left_right.c \
terminal/modify_buffer.c reading/mange_buffer.c history/utils.c quotes/quotes.c\
builtins/builtin_export.c

SOURCES		= $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJECTS		= $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(LIB) $(OBJECTS)
	@$(GCC) $(FLAGS) -o $@ $^ $(LIB_LINK) $(EXTRA_LIB)
	@echo "\033[0;32mSuccess: \033[0mminishell compiled"
	@echo "\033[0;32mDone"

$(LIB):
	@make -C $(LIB_PATH)

%.o: %.c $(INC_DIR)/*.h
	@$(GCC) $(FLAGS) $(INC_FLAGS) -c -o $@ $<

clean:
	@rm -f $(OBJECTS)
	@find . \( -name "*~" -o -name "*.swp" -o -name ".DS_Store" \) -delete
	@make clean -C $(LIB_PATH)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIB_PATH)

re: fclean all
