# Variables
SRC = client.c server.c
SRC_BONUS = client_bonus.c server_bonus.c
NAME = client server
CC = cc
FLAGS = -Wall -Werror -Wextra
RM = rm -rf

# Object files
OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

# Default target
all: $(NAME)

# Rule to build the client
client: client.o
	$(CC) $(FLAGS) $< -o $@

# Rule to build the server
server: server.o
	$(CC) $(FLAGS) $< -o $@

# Bonus target
bonus: client_bonus server_bonus

client_bonus: client_bonus.o
	$(CC) $(FLAGS) $< -o $@

server_bonus: server_bonus.o
	$(CC) $(FLAGS) $< -o $@

# Rule to compile .c files into .o files
%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

# Clean up object files and executables
clean:
	$(RM) $(OBJ) $(OBJ_BONUS)

fclean: clean
	$(RM) $(NAME) client_bonus server_bonus

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re bonus