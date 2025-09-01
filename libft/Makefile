# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaiache <aaiache@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/29 17:21:37 by aaiache           #+#    #+#              #
#    Updated: 2025/08/27 17:48:23 by aaiache          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
      ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
      ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
      ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
      ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
      ft_strtrim.c ft_split.c ft_itoa.c ft_striteri.c \
      ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
      ft_strrchr.c ft_strmapi.c ft_lstadd_front.c ft_lstadd_back.c ft_lstclear.c \
      ft_lstiter.c ft_lstlast.c ft_lstnew.c ft_lstsize.c \
      ft_lstdelone.c ft_lstmap.c get_next_line.c ft_strcmp.c ft_strncpy.c

OBJS_DIR = objs
OBJS = $(SRCS:.c=.o)
OBJS := $(addprefix $(OBJS_DIR)/, $(OBJS))

CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror


all: ft_printf $(NAME)

ft_printf:
	@echo "\033[0;32mCompilation de ft_printf...\033[0m"
	@$(MAKE) -C ft_printf

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	@echo "\033[38;5;194mCompilation de $<\033[0m"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

clean:
	@echo "	\033[0;33mSuppression des fichiers objets."
	@$(RM) $(OBJS_DIR)
	@$(MAKE) -C ft_printf clean

fclean: clean
	@echo "	\033[0;33mSuppression de l'exécutable $(NAME)."
	@$(RM) $(NAME)
	@$(MAKE) -C ft_printf fclean

re: fclean all
	@echo "\033[0;32m Recompilation complète terminée."

.PHONY: all clean fclean re ft_printf