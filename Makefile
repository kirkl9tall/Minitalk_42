SRC = client.c server.c
SRC_BONUS = client_bonus.c server_bonus.c
NAME = client server
CC = cc
FLAGS = -Wall -Werror -Wextra
RM = rm -rf

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

all: $(NAME)

client: client.o
	$(CC) $(FLAGS) $< -o $@

server: server.o
	$(CC) $(FLAGS) $< -o $@

bonus: client_bonus server_bonus

client_bonus: client_bonus.o
	$(CC) $(FLAGS) $< -o $@

server_bonus: server_bonus.o
	$(CC) $(FLAGS) $< -o $@

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(OBJ_BONUS)

fclean: clean
	$(RM) $(NAME) client_bonus server_bonus

re: fclean all

.PHONY: all clean fclean re bonus