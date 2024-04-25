NAME	=	push_swap

# Directories
LIBFT				= ./libft/libft.a
SRC_DIR				= srcs/
OBJ_DIR				= obj/

# Compiler and Flags
CC			= cc
RM			= rm -f
CFLAGS		= -g3 -Wall -Werror -Wextra -I. -MMD -MP

# Source Files
COMMANDS_DIR		=	$(SRC_DIR)commands/push.c \
						$(SRC_DIR)commands/reverse_rotate.c \
						$(SRC_DIR)commands/rotate.c \
						$(SRC_DIR)commands/swap.c

PUSH_SWAP_DIR		=	$(SRC_DIR)push_swap/push_swap.c \
						$(SRC_DIR)push_swap/ft_split.c \
						$(SRC_DIR)push_swap/init.c \
						$(SRC_DIR)push_swap/handle_error.c \
						$(SRC_DIR)push_swap/push_swap_utils.c \
						$(SRC_DIR)push_swap/sort.c \
						$(SRC_DIR)push_swap/move_strat.c \
						$(SRC_DIR)push_swap/init_node.c \
						$(SRC_DIR)push_swap/ft_atoi.c \
						$(SRC_DIR)push_swap/move_node.c 

# Concatenate all source files
SRCS				= $(COMMANDS_DIR) $(PUSH_SWAP_DIR)

# Apply the pattern substitution to each source file in SRC and produce a corresponding list of object files in the OBJ_DIR
OBJ					= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
DEPS    =       $(OBJ:.o=.d)
# Build rules
start:				
					@make all

$(LIBFT): FORCE
					@make -C ./libft

FORCE :

all: 				$(NAME)
-include $(DEPS)

$(NAME):			$(OBJ) $(LIBFT)
						@$(CC) $(CFLAGS) $(INC) $(OBJ) $(LIBFT) -o $(NAME)

# Compile object files from source files
$(OBJ_DIR)%.o:		$(SRC_DIR)%.c 
									@mkdir -p $(@D)
									@$(CC) $(CFLAGS) -c $< -o $@

clean:
					@$(RM) -r $(OBJ_DIR) $(DEPS)
					@make clean -C ./libft

fclean: 			clean
						@$(RM) $(NAME)
						@$(RM) $(LIBFT)

re: 				fclean all

# Phony targets represent actions not files
.PHONY:			start all clean fclean re
