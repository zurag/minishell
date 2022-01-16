NAME		= minishell
CC			= gcc
RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror -MMD -g

CPPFLAGS	= $(CFLAGS) -march=native -O2 -pipe

HEADERS		= includes/

SRCS =	srcs/main.c srcs/parser.c

OBJS = $(SRCS:.c=.o)

$(NAME):		$(OBJS)
				cd libft && $(MAKE) && mv libft.a ../libft.a
				$(CC) $(CPPFLAGS) -I $(HEADERS) $(OBJS) libft.a -lreadline -ltermcap -o $(NAME)

all:			$(NAME)

.c.o:
				$(CC) $(CPPFLAGS) -I $(HEADERS) -o $@ -c $<

$(OBJS):		$(HEADERS)

clean:
				$(RM) $(OBJS)
				$(RM) $(OBJS:.o=.d)

fclean:			clean
				cd libft && $(MAKE) clean
				$(RM) libft.a
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re