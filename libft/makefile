NAME	=	libft.a

FLAGS	=	-Wall -Werror -Wextra -I. -c

SRCS	=	$(shell ls | grep -E ".+\.c")	

INC	=	libft.h

OBJ	= 	$(SRCS:.c=.o)

$(NAME): 	$(OBJ)
			@ar rc $(NAME) $(OBJ)

all: 		$(NAME)

$(OBJ): 	$(SRCS)
			@gcc $(FLAGS) $(SRCS)

$(OBJ):		$(INC)

clean:
			@rm -rf $(OBJ)

fclean: 	clean
			@rm -rf $(NAME)

re: 		fclean all

.PHONY:		 all clean fclean re
