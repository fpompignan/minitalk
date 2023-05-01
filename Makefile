CLIENT = client
SERVER = server

SRC = 	client.c			\
		server.c						


OBJ = $(SRC:.c=.o)

WWW = -Wall -Werror -Wextra

all: server client

.c.o:
	gcc $(WWW)  -c $< -o $(<:.c=.o)


server: server.o
	gcc $(WWW) -o $(SERVER) server.o

client: client.o
	gcc $(WWW) -o $(CLIENT) client.o


clean:
	rm -f $(OBJ) 

fclean: clean
	rm -f $(CLIENT) $(SERVER)

re: fclean $(CLIENT) $(SERVER)

.PHONY: all clean fclean re bonus
