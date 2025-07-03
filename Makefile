# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/24 15:24:31 by swied             #+#    #+#              #
#    Updated: 2025/07/03 17:17:17 by swied            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo
CC := cc
CFLAGS := -Wall -Wextra -Werror
INCD := include
SRCD := src
OBJD := obj

# Colors
GREEN := \033[0;32m
YELLOW := \033[0;33m
RED := \033[0;31m
NC := \033[0m # No Color

SRCS :=	$(SRCD)/main.c \
		$(SRCD)/check.c \
		$(SRCD)/parsing.c \
		$(SRCD)/utils.c \
		$(SRCD)/free.c \
		$(SRCD)/init.c \
		$(SRCD)/execute.c

OBJS := $(SRCS:$(SRCD)/%.c=$(OBJD)/%.o)

all: $(NAME)

$(OBJD):
	@mkdir -p $(OBJD)

$(OBJD)/%.o: $(SRCD)/%.c | $(OBJD)
	@$(CC) $(CFLAGS) -I$(INCD) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME)
	@printf "$(GREEN)Executable $(NAME) built successfully!$(NC)\n"

clean:
	@printf "$(RED)Cleaning object files...$(NC)\n"
	@rm -rf $(OBJD)
	@printf "$(GREEN)Object files cleaned!$(NC)\n"

fclean: clean
	@printf "$(RED)Cleaning executable...$(NC)\n"
	@rm -f $(NAME)
	@printf "$(GREEN)Executable cleaned!$(NC)\n"

re: fclean all

.PHONY: all clean fclean re
