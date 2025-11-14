NAME=philo

CC= cc
CFLAGS=-Wall -Werror -Wextra -pthread

INCLUDE = philo.h
OBJ_DIR = obj

SRC = src/philo.c src/parse.c src/philo_utils.c src/inits.c src/routine.c src/monitor.c src/threads.c

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
