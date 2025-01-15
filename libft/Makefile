# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amesmar <amesmar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/16 14:44:37 by xhuang            #+#    #+#              #
#    Updated: 2025/01/15 19:42:41 by amesmar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# variables

NAME := libft.a

RM := rm -f

CC := cc

CFLAGS := -Wall -Wextra -Werror

# directories and files

INCLUDES := ./header/

SRCS := ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
	ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c \
	ft_strncmp.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_isspace.c ft_strcmp.c ft_tolower.c ft_toupper.c ft_strnstr.c ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
	ft_lstclear.c ft_lstiter.c ft_lstmap.c \
	ft_printf/ft_printf.c ft_printf/ft_print_utils.c ft_printf/ft_print_unsign.c get_next_line.c
	

SRCOBJ := $(SRCS:%.c=%.o) 

# rules

.PHONY: all clean fclean re

all:	$(NAME)

$(NAME):	$(SRCOBJ) 
	ar rcs $(NAME) $(SRCOBJ)
	@echo "Library $(NAME) has been created."

%.o:	%.c
	@$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@ 

clean:	
	$(RM) $(SRCOBJ) $(BONUS_OBJ)
	@echo "Object files have been deleted."

fclean: clean
	$(RM) $(NAME)
	@echo "Library has been deleted."

re: fclean all 
