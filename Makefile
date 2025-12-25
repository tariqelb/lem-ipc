NAME = lemipc

SRCS =	./lem-ipc.c \
	./ft_print_the_board.c \
	./ft_active_the_game.c \
	./ft_attack_defend_escape_moves.c \
	./ft_calculate_push_new_attack.c \
	./ft_check_if_player_died.c \
	./ft_check_if_player_in_the_corner.c \
	./ft_check_if_player_need_to_escape_or_died.c \
	./ft_check_if_position_safe.c \
	./ft_check_if_team_member_need_defence.c \
	./ft_choose_one_side_to_attack.c \
	./ft_create_destroy_shared_memory.c \
	./ft_exit_from_game.c \
	./ft_find_path_to_position_and_make_move.c \
	./ft_get_into_board.c \
	./ft_get_team_array_index.c \
	./ft_get_team.c \
	./ft_initialize_board.c \
	./ft_initialize_player.c \
	./ft_is_it_one_step_to_position.c \
	./ft_last_player_escape.c \
	./ft_leave_the_board.c \
	./ft_move_to_position_x_y.c \
	./ft_push_message_to_queue.c \
	./ft_scan_the_board_and_get_x_y_of_enemy_to_attack.c \
	./ft_semaphore.c \
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
