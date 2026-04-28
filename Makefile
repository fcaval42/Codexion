# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fcaval <fcaval@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/28 10:07:26 by fcaval            #+#    #+#              #
#    Updated: 2026/04/28 13:29:25 by fcaval           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = codexion
CC      = cc
CFLAGS  = -Wall -Wextra -Werror
SRCS    = main.c parsing.c utils.c init.c
OBJS    = $(SRCS:.c=.o)
HEADER  = codexion.h

# Couleurs
GREEN   = \033[0;32m
RED     = \033[0;31m
RESET   = \033[0m

# ========== RÈGLES ========== #

all: $(NAME)

$(NAME): $(OBJS)
	@echo " "
	@echo "$(GREEN)🚧 Compilation de $(NAME)...$(RESET)"
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo " "
	@echo "$(GREEN)👌 $(NAME) créé avec succès !$(RESET)"
	@echo " "

%.o: %.c $(HEADER)
	@echo " "
	@echo "$(GREEN)⏳ Compilation de $<...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo " "
	@echo "$(RED)🧹 Nettoyage des fichiers objets...$(RESET)"
	rm -f $(OBJS)
	@echo " "

fclean: clean
	@echo " "
	@echo "$(RED)🗑️ Suppression de $(NAME)$(RESET)"
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re