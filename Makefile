# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/14 16:42:34 by xhuang            #+#    #+#              #
#    Updated: 2025/01/28 16:52:07 by xhuang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS =  -Werror -Wextra -Wall -g

INC = -I ./inc/

SRCS_DIR = ./srcs/

SRCS = $(shell find $(SRCS_DIR) -type f -name "*.c")


OBJS = $(SRCS:.c=.o)

LIBFT = ./libft/

LIB = $(LIBFT)/libft.a

RM = rm -f

all: libft $(NAME)

libft: 
	@make -C $(LIBFT)

$(NAME):	$(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) $(LIB) $(INC) -o $(NAME) -l readline
	@echo "Executable $(NAME) has been created."

%.o:	%.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(INC) 

clean:	
	$(RM) $(OBJS) 
	@make clean -C $(LIBFT)
	@echo "Object files have been deleted."

fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(LIBFT)
	@echo "Library has been deleted."

re: fclean all 

.PHONY: all clean fclean re libft
