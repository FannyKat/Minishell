NAME 	=	minishell

SRC 	=	init.c utils.c fork.c builtins.c\

OBJ	=	$(SRC:.c=.o)

CC	=	clang -I /usr/local/include

CFLAGS	+=	-Wall -Wextra

PURPLE	=	\033[38;5;105m
BLUE	=	\033[38;5;141m
PINK	=	\033[38;5;177m
END	=	\033[0m

$(NAME):	$(OBJ)
	@make -C ./libft
	@echo "${PINK}LIBRARY COMPILED${END}"
	@$(CC) $(CFLAGS) ${SRC} ./libft/libft.a -o $(NAME)

all:		$(NAME)

clean:
	@/bin/rm -rf $(OBJ)
	@make -C ./libft/ clean
	@echo "${BLUE}clean obj${END}"

fclean:		clean
	@/bin/rm -rf $(NAME)
	@make -C ./libft/ fclean
	@echo "${BLUE}clean $(NAME)${END}"

.PHONY: all clean fclean re
