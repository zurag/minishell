NAME		= minishell

CC			= gcc
RM			= rm -rf

CFLAGS		= -Wall -Wextra -Werror -I $(READLINE_INC) -MMD -march=native -O2 -pipe -g -fsanitize=address

# Project builds and dirs
SRCDIR = ./srcs/
SRCNAMES = $(shell ls $(SRCDIR) | grep -E ".+\.c")
SRC = $(addprefix $(SRCDIR), $(SRCNAMES))
INC = ./includes/
BUILDDIR = ./build/
BUILDOBJS = $(addprefix $(BUILDDIR), $(SRCNAMES:.c=.o))

# Libft builds and dirs
LIBDIR = ./libft/
LIBFT = ./libft/libft.a
LIBINC = ./libft/includes/

# Lib readline
# READLINE_INC = /usr/local/opt/readline/include
# READLINE_LIB = /usr/local/opt/readline/lib
READLINE_INC = ~/.brew/opt/readline/include
READLINE_LIB = ~/.brew/opt/readline/lib

all: $(BUILDDIR) $(LIBFT) $(NAME)

# Object dir rule
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Objects rule
$(BUILDDIR)%.o:$(SRCDIR)%.c
	$(CC) $(CFLAGS) -I$(LIBINC) -I$(INC) -o $@ -c $<

# Project file rule
$(NAME): $(BUILDOBJS)
	$(CC) $(CFLAGS) $(BUILDOBJS) $(LIBFT) -lreadline -ltermcap -I $(INC) -I $(READLINE_INC) -L $(READLINE_LIB) -o $(NAME)

# Libft rule
$(LIBFT):
	make -C $(LIBDIR)

clean:
	$(RM) $(BUILDDIR)
	make -C $(LIBDIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBDIR) fclean

re: fclean all

.PHONY: all clean fclean re
