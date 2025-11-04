NAME=philo.a

CC= cc
CFLAGS=-Wall -Werror -Wextra

INCLUDE = philo.h
OBJ_DIR = obj

SRC = 

OBJ = $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	@echo "🔧 Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) && \
		echo "✅ Build successful!" || echo "❌ Build failed!"

$(OBJ_DIR)/%.o: src/%.c $(INCLUDE)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ && \
		echo "🟢 Compiled $<" || echo "🔴 Failed to compile $<"

clean:
	@echo "🧹 Cleaning object files..."
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_DIR_BONUS)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	@if [ -d $(MLX_BUILD) ]; then cmake --build $(MLX_BUILD) --target clean > /dev/null 2>&1; fi

fclean: clean
	@echo "🧹 Removing binaries..."
	@rm -f $(NAME)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
	@rm -rf $(MLX_BUILD)

re: fclean all

.PHONY: all clean fclean re
