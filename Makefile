NAME		= fdf

SRCS = \
		src/main.c \
		
OBJS 		= $(SRCS:.c=.o)

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

LIBFT_DIR	= libft_divinus
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_DIR)/$(LIBFT_NAME)

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

clean:
	$(RM) $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all
	make -C $(LIBFT_DIR) re

.phony: all clean fclean re
	make -C $(LIBFT_DIR) .phony
