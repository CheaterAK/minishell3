# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akocabas <akocabas@student.42istanbul.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/26 17:29:55 by akocabas          #+#    #+#              #
#    Updated: 2022/10/24 11:53:49 by akocabas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS = ft_printf.c
OBJS = $(SRCS:.c=.o)
LIBFT = ./libft/libft.a

CFLAGS = -Wall -Werror -Wextra -g

$(NAME): $(LIBFT) $(OBJS)
	cp $(LIBFT) ./$(NAME)
	ar -rcs $(NAME) $(OBJS)

$(LIBFT) :
	make -sC ./libft bonus
%.o: %.c
	gcc $(CFLAGS) -o $@ -c $< -g

all: $(NAME)

clean:
	make -sC ./libft clean
	rm -rf $(OBJS)

fclean: clean
	make -sC ./libft fclean
	rm -rf $(NAME)


re: fclean all

.PHONY: all clean fclean re
