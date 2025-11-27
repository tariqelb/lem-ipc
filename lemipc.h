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

# define BOARD_X_LEN 32 
# define BOARD_Y_LEN 32
# define SHM_SIZE 8192 // page size * 2
# define MAX_TEAMS 100 //Game will be designed to hold handred team as max

//:)
#define SHM_KEY 0x4C454D49  // "LEMI" in hex
#define SEM_KEY 0x4C454D50  // "LEMP" in hex  
#define MSG_KEY 0x4C454D51  // "LEMQ" in hex

typedef struct	s_team
{
	//teamid is team number
	int		team_id; 	// 4 bytes
	int		nbr_of_players; // 4 bytes
	//initial position for team to access the board
	short		init_x;		// 2 bytes
	short		init_y;		// 2 bytes
}		t_team;

typedef struct	s_game 
{
 	//board: 0=empty, 1+=team_id
	//active: 1=game running, 0=game over, -1=not yet start 
	int		board[BOARD_Y_LEN][BOARD_X_LEN]; //4096 bytes
	short		game_active;	//2 bytes
	int		total_players;	//4 bytes
	short		total_teams;	//2 bytes
	t_team		teams[MAX_TEAMS]; //1012 bytes
}		t_game; //totale size 5316 bytes

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
}		t_player;

// This goes in MESSAGE QUEUE (not shared memory!)
// Message queue is MANAGED BY KERNEL - you don't reserve memory for it!
// Kernel handles storage automatically

typedef struct	s_message_queue
{
	long		mtype; 
	unsigned short 	team_id;     // unsinged short is 2 byte, 0-65,535 teams
	unsigned short	defence_flag; // 0 or 1
	unsigned short	nbr_team_member; // 0-127 players
	unsigned short	x_attack;    // 0-31
	unsigned short	y_attack;    // 0-31
	unsigned short	x_defence;   // 0-31  
	unsigned short	y_defence;   // 0-31
}		t_message_queue; //total size = 22 * 100 + 14 = 2214 byes




//file : ft_get_team.c
int	ft_get_team(char *av);
int	ft_atoi(char *str);


//file : ft_create_destroy_shared_memory.c
int     ft_create_shared_memory(t_player *player);
int	ft_remove_shared_memory(t_player *player);

//file : ft_semaphore.c
int	ft_create_semaphore(t_player *player);
int    ft_destroy_semaphore(t_player *player);

//file : ft_initialize_board.c
t_player	*ft_initialize_game_board(t_player *player);

//file : ft_initialize_player.c
int		ft_check_if_team_exist(t_player *player); 
int		ft_get_free_place_in_team_array(t_player *player);
t_player	*ft_initialize_player(t_player *player);

//file : ft_active_the_game.c
int     ft_active_the_game(t_player *player);
int     ft_is_the_game_active(t_player *player);

//file: ft_setup_msg_queue.c
int     ft_create_message_queue(t_player *player);
int     ft_destroy_message_queue(t_player *player);

#endif
