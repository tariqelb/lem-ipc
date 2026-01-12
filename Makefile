NAME = lemipc

SRCS =	./lem-ipc.c \
	./ft_active_the_game_and_get_into_board.c \
	./ft_active_the_game.c \
	./ft_attack_defend_escape_moves.c \
	./ft_best_side.c \
	./ft_best_move.c \
	./ft_calculate_push_new_attack.c \
	./ft_check_attack_sides_of_surrouned_enemy_and_choose_one.c \
	./ft_check_if_attack_position_still_valide_and_free.c \
	./ft_check_if_last_position_surround_enemy.c \
	./ft_check_if_player_died.c \
	./ft_check_if_player_in_right_position_do_not_move.c \
	./ft_check_if_player_in_the_corner.c \
	./ft_check_if_player_need_to_escape_or_died.c \
	./ft_check_if_player_surround_enemy_from_one_side.c \
	./ft_check_if_position_safe.c \
	./ft_check_if_team_member_need_defence.c \
	./ft_choose_one_side_to_attack.c \
	./ft_create_destroy_shared_memory.c \
	./ft_display_the_board.c \
	./ft_exit_from_game.c \
	./ft_find_path_to_position_and_make_move.c \
	./ft_first_move.c \
	./ft_get_resources.c \
	./ft_get_into_board.c \
	./ft_get_message_from_message_queue.c \
	./ft_get_target_enemy_team_id.c \
	./ft_get_team_array_index.c \
	./ft_graphic_representation.c \
	./ft_get_team.c \
	./ft_go_closer_to_position_no_valid_path_to_it.c \
	./ft_initialize_board.c \
	./ft_initialize_player.c \
	./ft_is_enemy_still_in_position.c \
	./ft_is_enemy_surounded.c \
	./ft_is_it_one_step_to_position.c \
	./ft_last_player_escape.c \
	./ft_leave_the_board.c \
	./ft_move_to_best_position.c \
	./ft_move_to_position_x_y.c \
	./ft_new_enemy_found_select_best_side_to_attack.c \
	./ft_player_first_checks_and_moves.c \
	./ft_player_surround_enemy_from_one_side_and_other_side_free.c \
	./ft_print_the_board.c \
	./ft_push_message_to_queue.c \
	./ft_scan_the_board_and_get_x_y_of_enemy_to_attack.c \
	./ft_semaphore.c \
	./ft_setup_msg_queue.c \
	./ft_side_to_attack.c
       
OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RAYLIB = -lraylib -lm -ldl -lpthread -lX11

all: $(NAME) clean

$(NAME): $(OBJS)
	$(CC) $(RAYLIB) -o $(NAME) -I . $(OBJS) $(RAYLIB) 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
