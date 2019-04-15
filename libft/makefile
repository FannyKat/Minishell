NAME	=	libft.a

FLAGS	=	-Wall -Werror -Wextra -I. -c

SRCS	=	$(shell ls | grep -E ".+\.c")	

INC	=	libft.h

OBJ	= 	$(SRCS:.c=.o)

all: 		$(NAME)

$(NAME): 	$(OBJ)
			@ar rc $(NAME) $(OBJ)

$(OBJ):		$(INC)

$(OBJ): 	$(SRCS)
			@gcc $(FLAGS) $(SRCS)

clean:
			@rm -rf $(OBJ)

fclean: 	clean
			@rm -rf $(NAME)

re: 		fclean all

.PHONY:		 all clean fclean re
