NAME	=	libft.a

FLAGS	=	-Wall -Wextra -I. -c

SRCS	=	ft_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcat.c ft_strncat.c\
			ft_strchr.c ft_strrchr.c ft_strstr.c ft_strnstr.c ft_strcmp.c ft_memalloc.c\
			ft_strncmp.c ft_atoi.c ft_strnew.c ft_strdel.c ft_strclr.c ft_memcpy.c\
			ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_itoa.c ft_putchar.c\
			ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c\
			ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstdelone.c ft_isupper.c\
			ft_lstdel.c ft_lstadd.c ft_isblank.c ft_isspace.c ft_swap.c get_next_line.c\
			ft_xlstadd.c my_printf.c function.c ft_split.c ft_memdel.c ft_memset.c\
			ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isdigit.c ft_strndup.c isstart.c\
			ft_tablen.c print_tab.c ft_tabcopy.c ft_tabfree.c realloc_tab.c strlen_to.c\
			ft_strnjoinclr.c ft_strjoinclr.c strdupfree.c\

INC		=	libft.h

OBJ		= 	$(SRCS:.c=.o)

$(NAME): 	$(OBJ)
			@ar rc $(NAME) $(OBJ)

all: 		$(NAME)

$(OBJ):		$(INC)

$(OBJ): 	$(SRCS)
			@gcc $(FLAGS) $(SRCS)

clean:
			@rm -rf $(OBJ)

fclean: 	clean
			@rm -rf $(NAME)

re: 		fclean all

.PHONY:		 all clean fclean re
