# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zurag <zurag@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/20 21:12:43 by zurag             #+#    #+#              #
#    Updated: 2022/01/20 21:12:46 by zurag            ###   ########.fr        #
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
