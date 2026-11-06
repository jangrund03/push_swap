NAME	= push_swap
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -Iincludes

# --- libft: copy your libft into ./libft, then uncomment these 4 lines ---
# LIBFT_DIR	= libft
# LIBFT		= $(LIBFT_DIR)/libft.a
# CFLAGS	+= -I$(LIBFT_DIR)
# LDFLAGS	= -L$(LIBFT_DIR) -lft

SRC_DIR	= src
OBJ_DIR	= obj
SRCS	= main.c parse.c stack.c stack_moves.c normalize.c ops.c disorder.c bench.c \
		  strat_simple.c strat_medium.c strat_complex.c strat_adaptive.c
OBJS	= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c includes/push_swap.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# $(LIBFT):
#	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)
#	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
#	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
