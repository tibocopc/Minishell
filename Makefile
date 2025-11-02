# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xx <xx@student.42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/28 14:31:24 by aaiache           #+#    #+#              #
#    Updated: 2025/11/02 16:54:38 by xx               ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = minishell
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -Ilibft
RM      = rm -f

BUILD_DIR = objs

BUILTINS_SRCS = src/builtins/utils.c src/builtins/pwd.c src/builtins/echo.c src/builtins/env.c src/builtins/exit.c \
				src/builtins/cd.c src/builtins/export.c src/builtins/export_utils.c src/builtins/export_utils2.c \
				src/builtins/unset.c src/builtins/unset_utils.c
PARSE_SRCS = src/parseur/parseur.c src/parseur/utils.c src/parseur/expand.c src/parseur/expand_utils.c src/parseur/parseur_utils2.c src/parseur/expand_utils2.c
LEXER_SRCS = src/lexer/lexer.c src/lexer/utils.c src/lexer/lexer_utils.c
EXEC_SRCS = src/exec/pipeless.c src/exec/path.c src/exec/pipe.c src/exec/pipeless_utils.c src/exec/pipe_utils.c src/exec/pipe_fork.c
HEREDOC_SRCS = src/heredoc/heredoc.c src/heredoc/heredoc_utils.c
SRCS = src/main.c src/env.c src/cleanup.c src/main_utils.c src/input_handler.c
SIGNALS_SRC = src/Signals/signaux.c src/Signals/signaux_utils.c src/Signals/signaux_modes.c
ALL_SRCS   = $(SRCS) $(LEXER_SRCS) $(PARSE_SRCS) $(BUILTINS_SRCS) $(EXEC_SRCS) $(SIGNALS_SRC) $(HEREDOC_SRCS)

OBJS       = $(ALL_SRCS:%.c=$(BUILD_DIR)/%.o)

$(BUILD_DIR)/%.o: %.c includes/minishell.h
	@mkdir -p $(dir $@)
	@echo "\033[0;32mCompilation de $<"
	@$(CC) $(CFLAGS) -c $< -o $@

all: libft $(NAME)
	@echo "\033[0;32m\n----Compilation terminée avec succès.----"

libft:
	@echo "\033[0;32m-----Compilation de la libft-----\033[0m"
	@$(MAKE) -C libft

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -lreadline libft/ft_printf/ft_printf.a libft/libft.a -o $(NAME)

clean:
	@echo "\033[0;33mSuppression des fichiers objets"
	@$(RM) -r $(BUILD_DIR)

fclean: clean
	@echo "\033[0;33mSuppression de l'exécutable $(NAME)"
	@$(RM) $(NAME)
	@$(MAKE) -C libft fclean

re: fclean all

valgrind: $(NAME)
	@echo "$(YELLOW)🔍 Lancement de Valgrind sur ./minishell..."
	valgrind -q --suppressions=./ignore --trace-children=yes \
		--leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes \
		./minishell

bonus: libft $(OBJS_BONUS)
	@echo "Link des objets bonus pour créer $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS_BONUS) libft/ft_printf/ft_printf.a libft/libft.a -o $(NAME)
	@echo "\033[0;32mCompilation bonus terminée avec succès.\033[0m"

.PHONY: all clean fclean re libft valgrind