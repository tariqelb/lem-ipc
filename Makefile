NAME = lemipc

SRCS =	./lem-ipc.c \
	./ft_create_destroy_shared_memory.c \
	./ft_get_team.c \
	./ft_initialize_board.c \
	./ft_semaphore.c \
	./ft_initialize_player.c \
	./ft_active_the_game.c \
	./ft_setup_msg_queue.c
       
OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME) clean

$(NAME): $(OBJS)
	$(CC) -o $(NAME) -I . $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
