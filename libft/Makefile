# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lyubov <lyubov@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/20 13:07:25 by zurag             #+#    #+#              #
#    Updated: 2022/01/14 14:20:05 by lyubov           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c \
		ft_strlcat.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c \
		ft_atoi.c ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_calloc.c ft_strdup.c \
		ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
		ft_lstiter.c ft_lstmap.c

OBJS_B = ${SRCS_B:.c=.o}

OBJS = ${SRCS:.c=.o}

NAME = libft.a

CC = gcc

RM = rm -f

AR = ar rcs

INC = libft.h

CFLAGS = -Wall -Wextra -Werror -MMD -I ${INC}

all:		${NAME}

bonus:		${OBJS_B} ${INC}
			${AR} ${NAME} ${OBJS_B}

$(NAME):	${OBJS} ${INC}
			${AR} ${NAME} ${OBJS}


clean:
			${RM} ${OBJS} ${OBJS_B}
			$(RM) $(OBJS:.o=.d)

fclean:		clean
			${RM} ${NAME}
			${RM} *.d


re:			fclean all
