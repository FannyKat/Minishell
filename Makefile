NAME	= minishell

SRC_DIR	= ./src/
SRCS	= $(shell ls $(SRC_DIR) | grep -E ".+\.c")
SRC	= $(addprefix $(SRC_DIR), $(SRCS))
INC	= ./inc/
OBJ_DIR	= ./objs/
OBJS	= $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

LIB_DIR	= ./libft/
LIB	= ./libft/libft.a
LIB_INC	= ./libft/includes/

CC	= gcc
CFLAGS	= -Wall -Werror -Wextra

PINK	=	\033[35;5;108m
PURPLE	=	\033[38;5;141m
MAGENTA	=	\033[38;5;177m
END	=	\033[0m

all: $(OBJ_DIR) $(LIB) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@$(CC) $(CFLAGS) -I$(LIB_INC) -I$(INC) -o $@ -c $<

$(NAME): $(LIB) $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB)
	@echo "${PINK}MINISHELL IS READY ✓${END}"	

$(LIB):
	@make -C $(LIB_DIR)
	@echo "${MAGENTA}LIBRARY COMPILED ✓${END}"

$(OBJS):	$(INC) 

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIB_DIR) clean
	@echo "${PURPLE}clean objs ✗${END}"

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIB_DIR) fclean
	@echo "${PURPLE}clean $(NAME) ✗${END}"

re: fclean all

.PHONY: all fclean clean re
