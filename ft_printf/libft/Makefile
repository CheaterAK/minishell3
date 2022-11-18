# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akocabas <akocabas@student.42istanbul.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/19 05:55:44 by akocabas          #+#    #+#              #
#    Updated: 2022/10/24 11:53:32 by akocabas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libft.a

SRCS =	ft_isalnum.c	ft_isprint.c	ft_memcmp.c		ft_putchar_fd.c	\
		ft_strlcat.c	ft_strncmp.c	ft_substr.c		ft_atoi.c		\
		ft_itoa.c		ft_memcpy.c		ft_putendl_fd.c	ft_strchr.c		\
		ft_strnstr.c	ft_tolower.c	ft_bzero.c		ft_isascii.c	\
		ft_memmove.c	ft_putnbr_fd.c	ft_strdup.c		ft_strlen.c		\
		ft_toupper.c	ft_calloc.c		ft_isdigit.c	ft_memchr.c		\
		ft_split.c		ft_isalpha.c	ft_strlcpy.c	ft_strtrim.c	\
		ft_strrchr.c	ft_memset.c		ft_putstr_fd.c	ft_strjoin.c	\
		ft_strmapi.c	ft_striteri.c

OBJS = $(SRCS:.c=.o)

BONUS =	ft_lstadd_front.c	ft_lstclear.c	ft_lstsize.c	ft_lstnew.c	\
		ft_lstadd_back.c	ft_lstdelone.c	ft_lstlast.c	ft_lstiter.c

BONUS_OBJS = $(BONUS:.c=.o)

CC = @gcc
CFLAGS = -I. -Wall -Wextra -Werror -g

.PHONY: all clean fclean re bonus

all: $(NAME)
	@echo "Library's ready to use."
$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

%.o: %.c
	@$(CC) -c $^ -g
clean:
	@rm -f $(OBJS) $(BONUS_OBJS)
fclean: clean
	@rm -f $(NAME)

re: fclean $(NAME)

bonus: $(OBJS) $(BONUS_OBJS)
	@ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)
	@echo "Library's ready to use with bonus."

