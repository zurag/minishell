# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dtentaco <dtentaco@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/20 13:07:25 by zurag             #+#    #+#              #
#    Updated: 2022/01/12 02:35:23 by dtentaco         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
CFLAGS	= -Wall -Werror -Wextra -Iincludes -c
FILES	= $(shell ls | grep -E ".+\.c")
OBJ		= $(FILES:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

$(OBJ): $(FILES)
	gcc $(CFLAGS) $(FILES)

clean:
	rm -f $(OBJ)
	rm -f *.d

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re
