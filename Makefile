# Project Name
NAME        = fdf

# Source Files
SRCS        = 	\
				src/matrix/translate.c \
				src/matrix/zoom.c \
				src/matrix/rotate_2d.c \
				src/utils.c \
				src/map.c \
				src/memory_cleanup.c \
				src/projection.c \
				src/graphic.c \
				src/graphic_utils.c \
				src/app.c \
				src/main.c \

OBJS        = $(SRCS:.c=.o)

# Compiler & Flags
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
RM          = rm -f

# Libft Configuration
LIBFT_DIR   = libft_divinus
LIBFT_NAME  = libft.a
LIBFT       = $(LIBFT_DIR)/$(LIBFT_NAME)

# MLX42 Configuration
MLX42_DIR   = MLX42
MLX42_LIB   = $(MLX42_DIR)/build/libmlx42.a
MLX42_INC   = -I./MLX42/include  # Correct Include Path

# Additional Libraries
LIBS = -L/opt/homebrew/lib -lglfw -ldl -lm -framework OpenGL

# Build Rules
all: $(NAME)

# Link .o to executable
$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	cmake -B $(MLX42_DIR)/build -S $(MLX42_DIR)
	cmake --build $(MLX42_DIR)/build -j
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX42_LIB) $(MLX42_INC) $(LIBS) -o $(NAME)

# Compile .c to .o
%.o: %.c
	$(CC) $(CFLAGS) $(MLX42_INC) -c $< -o $@

clean:
	$(RM) $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean

# Build only libft
libft:
	make -C $(LIBFT_DIR) re

re: fclean all

e: all clean

.PHONY: all clean fclean re
