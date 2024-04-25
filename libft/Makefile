NAME	=	libft.a

# Directories
SRC_DIR			= src/
OBJ_DIR			= obj/

CC	=	cc
RM	=	rm -f
CFLAGS	=	-Wall -Wextra -Werror -I. -MMD -MP

SRCS	=	$(SRC_DIR)ft_strdup.c  \
			$(SRC_DIR)ft_printf.c \
			$(SRC_DIR)printf_utility.c

OBJS	= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
DEPS    =       $(OBJS:.o=.d)

all:	$(NAME)
-include $(DEPS)

$(NAME):	$(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) -c $< -o $@

clean:
				@$(RM) -r $(OBJ_DIR) $(DEPS)
				@$(RM) .cache_exists

fclean:		clean
				$(RM) $(NAME)

re:		fclean $(NAME)

.PHONY:		all clean fclean re bonus
