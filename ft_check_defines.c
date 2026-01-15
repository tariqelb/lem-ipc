#include "./lemipc.h"



int	ft_check_defines(void)
{
	//check board mix max lenght
	if (BOARD_X_LEN < BOARD_MIN_LEN || BOARD_X_LEN > BOARD_MAX_LEN || BOARD_Y_LEN < BOARD_MIN_LEN || BOARD_Y_LEN > BOARD_MAX_LEN)
	{
		write(2, "Lemipc: Error , adjust board lenght on lemipc.h file\n", 53);
		write(2, "Lemipc: Board should not have less than 8/8 squares\n", 52);
		write(2, "Lemipc: Board max squares should be resonable\n", 46);
		return (1);
	}
	if (MAX_TEAMS < 3)
	{
		write(2, "Lemipc: Error , Adjust max team define, be aware that MAX_TEAM increase memory needed for shared momery\n", 104);
		write(2, "Lemipc: Error , Mix value for MAX team allowed is 3\n", 52);
		return (1);
	}
	if (MAX_PLAYER_IN_TEAM < 5)
	{
		write(2, "Lemipc: Error , mix player defined for team should be at less 5\n", 64);
		return (1);
	}

	if (SHM_KEY == 0 || MSG_KEY == 0 || SEM_KEY == 0)
	{
		write(2, "Lemipc: Error , Shared memory, Messge queue and Semaphore keys\n", 63);
		return (1);
	}

	return (0);
}
