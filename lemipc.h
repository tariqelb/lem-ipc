#ifndef LEMIPC
# define LEMIPC

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <sys/errno.h>
# include <sys/sem.h>
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/msg.h>
# include <time.h>
# include "raylib.h"
# include <sys/wait.h>

# define BOARD_X_LEN 9 
# define BOARD_Y_LEN 9
# define BOARD_MIN_LEN 8
# define BOARD_MAX_LEN 32
# define MAX_TEAMS 10
# define MAX_PLAYER_IN_TEAM 20
# define SHM_SIZE 8192 // page size * 2 // should be geater that t_game struct
		       

# define RANDOM 1


#define HEIGHT 900
#define WIDTH  800
#define TITLE  "lemipc"


//:)
#define SHM_KEY 0x4C454D49  // "LEMI" in hex
#define SEM_KEY 0x4C454D50  // "LEMP" in hex  
#define MSG_KEY 0x4C454D51  // "LEMQ" in hex

typedef struct	s_team
{
	//team_id is team number (./lemipc 5)
	//init_x init_y initial position for team to access the board
	//corner is a varial increase every time new team member get in game 
	//and decrease after a player move to the corner of the board
	int		team_id; 	// 4 bytes
	int		nbr_of_players; // 4 bytes
	short		init_x;		// 2 bytes
	short		init_y;		// 2 bytes
	short		corner;		// 2 bytes
}		t_team;

typedef struct	s_game 
{
 	//board: 0=empty, player : 1+=team_id
	//active: 1=game running, 0=game over, -1=not yet start
	int	board[BOARD_Y_LEN][BOARD_X_LEN];	//4096 bytes for 32 * 32 * 4
	short	game_active;				//2 bytes
	int	total_players;				//4 bytes
	short	total_teams;				//2 bytes
	t_team	teams[MAX_TEAMS];			//1400 bytes for 100 team
}		t_game; 				//totale size 5504 bytes

// System V semaphore operations
typedef struct sembuf t_sem_lock;  // Wait/Lock
typedef struct sembuf t_sem_unlock;  // Post/Unlock

typedef struct	s_player
{
	t_game	*game; // board
	short	team_id;
	short	player_id;
	short	pos_x;
	short	pos_y;
	int	semid;
	int	shmid;
	int	msqid;
	int	died;
	int	path[4];//top->right->bottom->left
	int	first_move;
	int	target_team_id;
	short	find_x;
	short	find_y;
	short	last_x_pos;
	short	last_y_pos;
	short	find_path_active;
	int	graphic_representative;
	// Semaphore operations - DECLARE ONCE
	t_sem_lock	lock_op;
	t_sem_unlock	unlock_op;
}		t_player;

// This goes in MESSAGE QUEUE (not shared memory!)
// Message queue is MANAGED BY KERNEL - you don't reserve memory for it!
// Kernel handles storage automatically

typedef struct	s_message_queue
{
	long		mtype; 
	unsigned short 	team_id;     // unsinged short is 2 byte, 0-65,535 teams
	unsigned short	defence_flag; // when 0 or 4
	unsigned short	nbr_team_member;
	unsigned short	x_attack;    //N > 0 N < 2 bytes max
	unsigned short	y_attack;    
	unsigned short	x_defence;     
	unsigned short	y_defence;   
	unsigned short  x_player;
	unsigned short  y_player;
}		t_message_queue; //total size = 22 * 100 + 14 = 2214 byes


//file : ft_active_the_game.c
int     ft_active_the_game(t_player *player);
int     ft_is_the_game_active(t_player *player);
int     ft_check_if_team_win(t_player *player);

//file : ft_attack_defend_escape_moves.c
int     ft_get_message_from_message_queue(t_player *player, t_message_queue *msg);
int     ft_attack_defend_escape_moves(t_player *player, t_message_queue *msg);

//file : ft_calculate_push_new_attack.c
int	ft_calculate_push_new_attack(t_player *player, t_message_queue *msg);

//file : 	ft_check_if_player_in_the_corner.c
int	ft_check_if_player_in_the_corner(t_player *player);

//file : ft_check_if_player_need_to_escape_or_died.c
int	ft_check_if_player_in_the_corner(t_player *player);


//file : ft_check_if_player_need_to_escape_or_died.c
int	ft_check_if_player_need_to_escape_or_died(t_player *player);

//file : ft_check_if_position_safe.c
int     ft_check_position_is_safe(t_player *player, int x, int y);
int     ft_check_if_position_is_free(t_player *player, int x, int y);

//file :  ft_check_if_team_member_need_defence.c
int	ft_check_if_postion_need_defence(t_player *player, int p_x, int p_y, t_message_queue *new_msg);
int	ft_check_if_team_member_need_defence(t_player *player, t_message_queue *new_msg);

//file : ft_choose_one_side_to_attack.c
int	ft_choose_one_side_to_attack(t_player *player, int x, int y);

//file : ft_create_destroy_shared_memory.c
int	ft_check_if_max_teams_or_players_reached(t_player *player);
int	ft_create_shared_memory(t_player *player);
int     ft_remove_shared_memory(t_player *player);

//file : ft_exit_from_game.c
int	ft_exit_from_game(t_player *player, int flag);

//file : ft_find_path_to_position_and_make_move.c
int     ft_find_path_recursion(t_player *player, int p_x, int p_y, int board_visited_positions[BOARD_Y_LEN][BOARD_X_LEN], int index, int side);
int     ft_find_path_to_position(t_player *player);
int	ft_move_to_position_path(t_player *player);
int	ft_find_path_to_position_and_make_move(t_player *player, int x, int y);

//file : ft_get_into_board.c
int	ft_get_into_board(t_player *player);

//file : ft_get_team_array_index.c
int	ft_get_team_array_index(t_player *player);

//file : ft_get_team.c
int     ft_putint(int nbr);
int	ft_atoi(char *str);
int     ft_get_team(int ac, char *av, t_player *player);


//file : ft_initialize_board.c
t_player	*ft_initialize_game_board(t_player *player);

//file : ft_initialize_player.c
int		ft_check_if_team_exist(t_player *player);
int		ft_get_free_place_in_team_array(t_player *player);
t_player	*ft_initialize_player(t_player *player);

//file : ft_is_it_one_step_to_position.c
int	ft_is_it_one_step_to_position(t_player *player, t_message_queue msg, int side_to_attack);
int     ft_is_it_one_step_to_position_x_y(t_player *player, int x, int y);

//file : ft_last_player_escape.c
int	ft_random_direction(int a, int b, int c, int d);
int	ft_find_best_move_and_escape(t_player *player);

//file : ft_leave_the_board.c
int	ft_leave_the_board(t_player *player);

//file : ft_move_to_position_x_y.c
int	ft_move_to_position_x_y(t_player *player, int x, int y);

//file : ft_push_message_to_queue.c
int	ft_push_message_to_queue(t_player *player, t_message_queue *msg);

//file : ft_scan_the_board_and_get_x_y_of_enemy_to_attack.c
int	ft_scan_the_board_and_get_x_y_of_enemy_to_attack(t_player *player, int *enemy_x, int *enemy_y, int *enemy_team_id);

//file : ft_semaphore.c
void	ft_initialize_semaphore_struct(t_player *player);
int	ft_create_semaphore(t_player *player);
int	ft_destroy_semaphore(t_player *player);

//file : ft_setup_msg_queue.c
int	ft_create_message_queue(t_player *player);
int	ft_destroy_message_queue(t_player *player);

//file : lem-ipc.c

//file :  ft_print_the_board.c
void	ft_print_the_board(t_player *player);

//file :  ft_get_target_enemy_team_id.c
int     ft_get_target_enemy_team_id(t_player *pleyer);


//file :  ft_display_the_board.c
void    ft_display_the_board(int board[BOARD_Y_LEN][BOARD_X_LEN]);

//file : ft_best_side.c
int	ft_include(int best_side[4], int i, int include);
int	ft_best_side(t_player *player, int p_x, int p_y, int i, int best_side[4]);

//file : ft_is_enemy_surounded.c
int     ft_is_player_surrounded(t_player *player);
int     ft_scan_board_if_a_player_surrounded(t_player *player);
int     ft_get_player_sides(t_player *player, int x, int y, int *top, int *right, int *bottom, int *left);


//file : ft_graphic_representation.c
int     ft_graphic_representation(t_player *player);

//file : ft_best_move.c
int	ft_best_move(t_player *player, int *x, int *y);
int     ft_second_best_move(t_player *player, int *x, int *y);

//file : ft_side_to_attack.c
int     ft_attack_position(t_player *player, int x, int y);
int     ft_second_side_to_attack(t_player *player, t_message_queue msg);

//file :  ft_check_if_player_surround_enemy_from_one_side.c
int     ft_get_position_sides(t_player *player, int x, int y, int *top, int *right, int *bottom, int *left);
int     ft_check_if_player_surround_enemy_from_one_side(t_player *player, t_message_queue *msg);

//file : ft_move_to_best_position.c
int     ft_move_to_best_position(t_player *player, int *x, int *y);
int     ft_move_to_second_best_position(t_player *player, int *x, int *y);

//file :  ft_check_if_attack_position_still_valid_and_free.c
int     ft_check_if_attack_position_still_valid_and_free(t_player *player, t_message_queue *msg);

//file :
int	ft_go_closer_to_position_no_valid_path_to_it(t_player *player, int x, int y);


//file : ft_player_first_checks_and_moves.c
int     ft_player_first_checks_and_moves(t_player *player, t_message_queue *msg);

//file : ft_new_enemy_found_select_best_side_to_attack.c
int     ft_new_enemy_found_select_best_side_to_attack(t_player *player, int enemy_x, int enemy_y, int enemy_team_id);

//file : ft_first_move.c
int	ft_first_move(t_player *player);

//file : ft_get_message_from_message_queue.c
int     ft_get_message_from_message_queue(t_player *player, t_message_queue *msg);

//file : ft_is_enemy_still_in_position.c
int     ft_is_enemy_still_in_position(t_player *player, int x, int y);

//file : ft_get_resouces.c
int     ft_get_resouces(t_player *player);

//file : ft_active_the_game_and_get_into_board.c
int     ft_active_the_game_and_get_into_board(t_player *player);


//file : ft_check_if_last_position_surround_enemy.c
int     ft_check_if_last_position_surround_enemy(t_player *player, int new_x, int new_y);

//file : ft_check_defines.c
int		ft_check_defines(void);









//********random set of functions
//file : ft_check_if_player_died.c
int     ft_random_rule_check_if_other_enemy_exist(short player_sides[8], short index);
int     ft_random_rule_check_if_player_surrounded(t_player *player, int player_id, int x, int y);

//file :
int     ft_random_rule_check_if_player_attacked_surround_enemy_from_side(t_player *player, int x, int y);

//file :
//file :








#endif
