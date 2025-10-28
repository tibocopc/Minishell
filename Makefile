# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xx <xx@student.42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/19 14:34:39 by aaiache           #+#    #+#              #
#    Updated: 2025/09/19 13:59:19 by xx               ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = minishell
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -Ilibft -g
RM      = rm -f

BUILD_DIR = objs

BUILTINS_SRCS = src/builtins/pwd.c src/builtins/cd.c src/builtins/exit.c src/builtins/echo.c src/builtins/env.c
LEXER_SRCS = src/lexer/lexer.c src/lexer/utils.c
SRCS = src/main.c src/set_env.c
PARSING_SRCS =  src/parse/parseur.c src/parse/utils.c src/parse/parse.c
ALL_SRCS   = $(SRCS) $(BUILTINS_SRCS) $(LEXER_SRCS) $(PARSING_SRCS)

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

bonus: libft $(OBJS_BONUS)
	@echo "Link des objets bonus pour créer $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS_BONUS) libft/ft_printf/ft_printf.a libft/libft.a -o $(NAME)
	@echo "\033[0;32mCompilation bonus terminée avec succès.\033[0m"

.PHONY: all clean fclean re libft