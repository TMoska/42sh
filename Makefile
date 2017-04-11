# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moska <moska@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/07 21:40:09 by moska             #+#    #+#              #
#    Updated: 2017/04/11 17:30:29 by tmoska           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GCC 		= gcc
NAME 		= 42sh
FLAGS 		= -Wall -Werror -Wextra -g

LIB_PATH	= libft
LIB			= $(LIB_PATH)/libft.a
LIB_LINK	= -L $(LIB_PATH) -lft
EXTRA_LIB = -ltermcap

INC_DIR 	= includes
INC_FLAGS 	= -I./includes -I $(LIB_PATH)/includes

SRC_DIR 	= srcs
SRC_FILES = main.c execution/interpreting.c terminal/shell.c cleanup/cleaning.c\
builtins/builtins.c builtins/builtin_exit.c builtins/builtin_env.c \
builtins/builtin_getenv.c env_list/utils.c env_list/utils2.c tokenizer/errors.c\
builtins/builtin_setenv.c builtins/builtin_unsetenv.c terminal/cut_copy_line.c \
builtins/builtin_env_utilities.c builtins/builtin_env_utilities2.c \
builtins/builtin_env_prints.c builtins/builtin_cd.c builtins/builtin_echo.c \
builtins/builtin_cd_utilities.c builtins/builtin_cd_utilities2.c \
builtins/builtin_cd_utilities3.c history/history.c reading/prompt.c \
reading/reader.c terminal/term_init.c terminal/cursor_left_right.c \
terminal/modify_buffer.c reading/mange_buffer.c history/utils.c quotes/quotes.c\
builtins/builtin_export.c tokenizer/utils.c tokenizer/split_command.c \
tokenizer/get_tokens.c tokenizer/tokenizer.c tokenizer/reorganizer.c \
tokenizer/tree_builder.c execution/executer.c history/single_exclamation.c \
execution/right_redirections.c execution/logic_operators.c execution/pipe.c \
execution/semicolon.c execution/left_redirections.c tokenizer/reorganizer2.c \
execution/fd_aggregation.c execution/interpreting2.c tokenizer/utils2.c \
tokenizer/split_command_utils.c execution/left_redirection_utils.c \
execution/interpreting_utilities.c reading/validating.c heredoc/heredoc.c \
execution/left_redirections2.c reading/prompt_utils.c terminal/edition_utils.c \
history/history_search.c history/exclamation.c terminal/edition.c \
terminal/edition_cursor_right.c history/single_exclamation_utils.c \
completion/c_utils.c completion/c_utils2.c completion/put_options.c \
completion/tab_completion.c completion/define_pading.c completion/tab_arrows.c \
completion/c_utils3.c completion/tab_lst_sort.c completion/c_utils4.c \
terminal/edition_cursor_right.c quotes/splitquote_str2.c cleanup/cleaning2.c\
execution/left_redirections2.c reading/prompt_utils.c history/history_search.c \
history/exclamation.c history/single_exclamation_utils.c \
builtins/builtin_env_prints2.c quotes/ft_isescapechar.c \
quotes/treatquotes.c quotes/ft_splittreat.c \
completion/tab_name.c completion/ft_print.c completion/get_info.c \
completion/get_dir.c completion/get_list.c \
completion/clean_list.c completion/try_up.c completion/name_completion.c \
completion/name_utils.c \
terminal/edition_cursor_right.c quotes/splitquote_str2.c \
execution/left_redirections2.c reading/prompt_utils.c history/history_search.c \
history/exclamation.c history/single_exclamation_utils.c \
builtins/builtin_env_prints2.c quotes/ft_isescapechar.c \
quotes/treatquotes.c quotes/ft_splittreat.c quotes/quotes_env.c \
completion/padding_utils.c

SOURCES		= $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJECTS		= $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(LIB) $(OBJECTS)
	@$(GCC) $(FLAGS) -o $@ $^ $(LIB_LINK) $(EXTRA_LIB)
	@echo "\033[0;32mSuccess: \033[0m42sh compiled"
	@echo "\033[0;32mDone\033[0m"

$(LIB):
	@make -C $(LIB_PATH)

%.o: %.c $(INC_DIR)/minishell.h
	@$(GCC) $(FLAGS) $(INC_FLAGS) -c -o $@ $<

clean:
	@rm -f $(OBJECTS)
	@make clean -C $(LIB_PATH)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIB_PATH)

re: fclean all

.PHONY : re fclean clean all
