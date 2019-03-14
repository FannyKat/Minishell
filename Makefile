NAME 	=	minishell

SRC 	=	minishell.c\

OBJ		=	$(SRC:.c=.o)

CC		=	clang -I /usr/local/include

CFLAGS	+=	-Wall -Wextra

$(NAME):	$(OBJ)
		@make -C libft
		$(CC) $(CFLAGS) libft/libft.a $(SRC) -o $(NAME)

all:		$(NAME)

clean:
		rm -rf $(OBJ)
		@make -C libft clean

fclean:
		rm -rf $(NAME)
		@make -C libft fclean

re:		fclean all

.PHONY: all clean fclean re
