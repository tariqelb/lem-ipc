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

# define BOARD_SIZE 32
# define BOARD_X_LEN 6 
# define BOARD_Y_LEN 7
# define SHM_SIZE 8192 // page size * 2
# define MAX_TEAMS 100 //Game will be designed to hold handred team as max
# define MAX_PLAYER_IN_TEAM 50


#define HEIGHT 900
#define WIDTH  800
#define TITLE  "lemipc"


//:)
#define SHM_KEY 0x4C454D49  // "LEMI" in hex
#define SEM_KEY 0x4C454D50  // "LEMP" in hex  
#define MSG_KEY 0x4C454D51  // "LEMQ" in hex
#define FIND_PATH_MAX 200 //max steps calculate to find path to position

typedef struct	s_team
{
	//teamid is team number
	int		team_id; 	// 4 bytes
	int		nbr_of_players; // 4 bytes
	//initial position for team to access the board
	short		init_x;		// 2 bytes
	short		init_y;		// 2 bytes
	short		corner;		// 2 bytes
}		t_team;

typedef struct	s_game 
{
 	//board: 0=empty, 1+=team_id
	//active: 1=game running, 0=game over, -1=not yet start 
	int	board[BOARD_Y_LEN][BOARD_X_LEN]; //4096 bytes
	short	game_active;	//2 bytes
	int	total_players;	//4 bytes
	short	total_teams;	//2 bytes
	t_team	teams[MAX_TEAMS];//1400 bytes for 100 team
}		t_game; //totale size 5504 bytes

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
	//this var hold how mony step i need to reach find_x/y from safe side
	//related to player->pos_x/y
	int	path[4];//top->right->bottom->left
	int	first_move;
	int	target_team_id;
	short	find_x;//you should check if i use this or remove it
	short	find_y;//
		       //
		       //
	int	graphic_representative;
	int	team_color;
	int	attack;
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
	unsigned short	defence_flag; // 0 or 1 for defence 2 surround from one side
	unsigned short	nbr_team_member; // 0-127 players
	unsigned short	x_attack;    // 0-31
	unsigned short	y_attack;    // 0-31
	unsigned short	x_defence;   // 0-31  
	unsigned short	y_defence;   // 0-31
	unsigned short  x_y_sides[4][2];
	unsigned short  sides[4];	// enemy surrounded from one side attack side[1] = 1 => [P][E][0] 
					// enemies positions in x y sides , surround flag = 2 in defence_flag and side to attack in side[N] = 1
}		t_message_queue; //total size = 22 * 100 + 14 = 2214 byes


//file : ft_active_the_game.c
int     ft_active_the_game(t_player *player);
int     ft_is_the_game_active(t_player *player);
int     ft_check_if_team_win(t_player *player);

//file : ft_attack_defend_escape_moves.c
int     ft_get_message_from_message_queue(t_player *player, t_message_queue *msg);
int     ft_attack_defend_escape_moves(t_player *player);

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
int	ft_go_closer_to_position_no_valid_path_to_it(t_player *player, int x, int y);
int	ft_find_path_to_position_and_make_move(t_player *player, int x, int y);

//file : ft_get_into_board.c
int	ft_get_into_board(t_player *player);

//file : ft_get_team_array_index.c
int	ft_get_team_array_index(t_player *player);

//file : ft_get_team.c
int     ft_putint(int nbr);
int	ft_get_team(char *av);
int	ft_atoi(char *str);

//file : ft_initialize_board.c
t_player	*ft_initialize_game_board(t_player *player);

//file : ft_initialize_player.c
int		ft_check_if_team_exist(t_player *player);
int		ft_get_free_place_in_team_array(t_player *player);
t_player	*ft_initialize_player(t_player *player);

//file : ft_is_it_one_step_to_position.c
int	ft_is_it_one_step_to_position(t_player *player, t_message_queue msg, int side_to_attack);

//file : ft_last_player_escape.c
int	ft_random_direction(int a, int b, int c, int d);
int	ft_find_best_move_and_escape(t_player *player);
int	ft_last_player_escape(t_player *player);

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


//file : ft_check_if_player_in_right_position_do_not_move.c
int	ft_check_if_player_in_right_position_do_not_move(t_player *player);


//file :  ft_display_the_board.c
void    ft_display_the_board(int board[BOARD_Y_LEN][BOARD_X_LEN]);

//file : ft_best_side.c
int	ft_include(int best_side[4], int i, int include);
int	ft_best_side(t_player *player, int p_x, int p_y, int i, int best_side[4]);

//file : ft_is_enemy_surounded.c
int     ft_is_player_surrounded(t_player *player);
int	ft_is_enemy_surounded(t_player *player);
int     ft_scan_board_if_a_player_surrounded(t_player *player);
int     ft_get_player_sides(t_player *player, int x, int y, int *top, int *right, int *bottom, int *left);


//file : ft_graphic_representation.c
int     ft_graphic_representation(t_player *player);

//file : ft_best_move.c
int	ft_best_move(t_player *player, int *x, int *y);
int     ft_second_best_move(t_player *player, int *x, int *y);

//file : ft_player_surround_enemy_from_one_side_and_other_side_free.c
int	ft_player_surround_enemy_from_one_side_and_other_side_free(t_player *player, t_message_queue *msg);

//file : ft_check_attack_sides_of_surrouned_enemy_and_choose_one.c
int     ft_is_it_one_step_to_position_x_y(t_player *player, int x, int y);
int     ft_check_attack_sides_of_surrouned_enemy_and_choose_one(t_player *player, t_message_queue *msg);

//file : ft_side_to_attack.c
int     ft_side_to_attack(t_player *player, t_message_queue msg);
int     ft_surround_side_to_attack(t_player *player, t_message_queue msg);

//file :  ft_check_if_player_surround_enemy_from_one_side.c
int     ft_get_position_sides(t_player *player, int x, int y, int *top, int *right, int *bottom, int *left);
int     ft_check_if_player_surround_enemy_from_one_side(t_player *player, t_message_queue *msg);

//file : ft_move_to_best_position.c
int     ft_move_to_best_position(t_player *player, int *x, int *y);

//file :
//file :
//file :
//file :








#endif
