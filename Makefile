NAME=philo

CC= cc
CFLAGS=-Wall -Werror -Wextra

INCLUDE = philo.h
OBJ_DIR = obj

SRC = src/philo.c

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

fclean: clean
	@echo "🧹 Removing binaries..."
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
