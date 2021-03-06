# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmp <gmp@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/02/20 09:56:28 by gmp               #+#    #+#              #
#    Updated: 2015/07/03 16:49:02 by gpetrov          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= npuzzle
SRCS	= $(shell find srcs -type f -print | grep '\.cpp$$')
OBJS	= $(SRCS:srcs/%.cpp=srcs/.obj/%.o)
INC		= -I includes -I libft/includes
FLAGS	= -Wall -Wextra -Werror -pedantic
LIB		= -L libft -lft
CC		= g++ -g -std=c++11
OBJ_DIR = srcs/.obj

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(INC) $(INC) $(LIB)
	@echo "\n=> Compiling $(NAME) [\033[32mDONE\033[m]"

$(OBJ_DIR)/%.o: srcs/%.cpp
	@mkdir -p $(OBJ_DIR)
	@$(CC) -c $< -o $@ $(FLAGS) $(INC)
	@echo -n .

gdb:
	make -C libft
	$(CC) -g $(FLAGS) $(OBJS) -o $(NAME) $(INC) $(INC) $(LIB)
	gdb $(NAME)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft

re: fclean all

.PHONY: all gdb clean fclean

