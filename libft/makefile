NAME	=	libft.a

FLAGS	=	-Wall -Werror -Wextra -I. -c

SRCS	=	$(shell ls | grep -E ".+\.c")	

INC	=	libft.h

OBJ	= 	$(SRCS:.c=.o)

$(OBJ):		$(INC)

$(NAME): 	$(OBJ)
			@ar rcs $(NAME) $(OBJ)

$(OBJ): 	$(SRCS)
			@gcc $(FLAGS) $(SRCS)

all: 		$(NAME)

clean:
			@rm -rf $(OBJ)

fclean: 	clean
			@rm -rf $(NAME)

re: 		fclean all

.PHONY:		 all clean fclean re
