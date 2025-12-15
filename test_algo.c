#include "./lemipc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Simple position safety check (replace with your actual function)
int     ft_check_position_is_safe(t_player *player, int x, int y)
{
        int     left;
        int     right;
        int     top;
        int     bottom;

        if (x == -1 || x == 32 || y == -1 || y == 32)
                return (-1);
        if (x == 0)
                left = -1;
        else
                left = player->game->board[x - 1][y];
        if (x == 31)
                right = -1;
        else
                right = player->game->board[x + 1][y];
        if (y == 0)
                top = -1;
        else
                top = player->game->board[x][y - 1];
        if (y == 31)
                bottom = -1;
        else
                bottom = player->game->board[x][y + 1];
        if (top != -1 && top != player->team_id + 1 &&
                bottom != -1 && bottom != player->team_id + 1)
                return (1);
        if (left != -1 && left != player->team_id + 1 &&
                right != -1 && right != player->team_id + 1)
                return (1);
        //0 = safe
        return (0);
}

// Mock your pathfinding function (replace with your actual implementation)


int ft_find_path_recursion(t_player *player, int p_x, int p_y, int b_x, int b_y, 
                          int already_been[4], int index, int visited[32][32])
{
    int top;    //1
    int right;  //2
    int bottom; //3
    int left;   //4
    int result;
    
    // Check boundaries
    if (p_x < 0 || p_x >= 32 || p_y < 0 || p_y >= 32)
        return -1;
    
    // Check if already visited
    if (visited[p_x][p_y] == 1)
        return -1;
    
    // Check if position is occupied
    if (player->game->board[p_x][p_y] != 0)
        return -1;
    
    // Mark as visited
    visited[p_x][p_y] = 1;
    
    // Record the move that got us here
    if (already_been[0] == 1)
        player->path[index] = 1;  // top
    else if (already_been[1] == 1)
        player->path[index] = 2;  // right
    else if (already_been[2] == 1)
        player->path[index] = 3;  // bottom
    else if (already_been[3] == 1)
        player->path[index] = 4;  // left
    
    // Check if we reached target
    if (p_x == b_x && p_y == b_y)
    {
        return index + 1;  // Return number of steps
    }
    
    // Try all 4 directions in order (prioritize towards target)
    int directions[4][3] = {
        {p_x, p_y - 1, 0},    // up (1)
        {p_x + 1, p_y, 1},    // right (2)
        {p_x, p_y + 1, 2},    // down (3)
        {p_x - 1, p_y, 3}     // left (4)
    };
    
    int came_from[4][4] = {
        {0, 0, 1, 0},  // came from top
        {0, 1, 0, 0},  // came from right
        {1, 0, 0, 0},  // came from bottom
        {0, 0, 0, 1}   // came from left
    };
    
    // Try each direction
    for (int i = 0; i < 4; i++)
    {
        // Skip if we would go out of bounds
        if (directions[i][0] < 0 || directions[i][0] >= 32 || 
            directions[i][1] < 0 || directions[i][1] >= 32)
            continue;
            
        result = ft_find_path_recursion(player, 
                                        directions[i][0], 
                                        directions[i][1], 
                                        b_x, b_y, 
                                        came_from[directions[i][2]], 
                                        index + 1, 
                                        visited);
        
        if (result > 0)  // Found a path
            return result;
    }
    
    // If we reach here, no path found from this position
    // Unmark visited for backtracking (optional - depends on algorithm)
    // visited[p_x][p_y] = 0;
    return -1;
}

int ft_find_path_to_position(t_player *player, int board_x, int board_y, 
                            int next_x, int next_y)
{
    int visited[32][32] = {0};
    int top, right, bottom, left;
    int path_length = -1;
    
    // Initialize path array
    for (int i = 0; i < FIND_PATH_MAX; i++)
        player->path[i] = 0;
    
    // Mark current position as visited (don't go back to start)
    visited[player->pos_x][player->pos_y] = 1;
    
    // Try each direction from current position
    // UP
    if (ft_check_position_is_safe(player, player->pos_x, player->pos_y - 1) == 0)
    {
        int came_from_up[4] = {0, 0, 1, 0};
        top = ft_find_path_recursion(player, 
                                    player->pos_x, 
                                    player->pos_y - 1, 
                                    board_x, board_y, 
                                    came_from_up, 
                                    0, 
                                    visited);
        if (top > 0)
            return top;
    }
    
    // Reset visited for next direction (or maintain separate arrays)
    // Clear visited except start position
    memset(visited, 0, sizeof(visited));
    visited[player->pos_x][player->pos_y] = 1;
    
    // RIGHT
    if (ft_check_position_is_safe(player, player->pos_x + 1, player->pos_y) == 0)
    {
        int came_from_right[4] = {0, 1, 0, 0};
        right = ft_find_path_recursion(player, 
                                      player->pos_x + 1, 
                                      player->pos_y, 
                                      board_x, board_y, 
                                      came_from_right, 
                                      0, 
                                      visited);
        if (right > 0)
            return right;
    }
    
    // Reset visited
    memset(visited, 0, sizeof(visited));
    visited[player->pos_x][player->pos_y] = 1;
    
    // DOWN
    if (ft_check_position_is_safe(player, player->pos_x, player->pos_y + 1) == 0)
    {
        int came_from_down[4] = {1, 0, 0, 0};
        bottom = ft_find_path_recursion(player, 
                                       player->pos_x, 
                                       player->pos_y + 1, 
                                       board_x, board_y, 
                                       came_from_down, 
                                       0, 
                                       visited);
        if (bottom > 0)
            return bottom;
    }
    
    // Reset visited
    memset(visited, 0, sizeof(visited));
    visited[player->pos_x][player->pos_y] = 1;
    
    // LEFT
    if (ft_check_position_is_safe(player, player->pos_x - 1, player->pos_y) == 0)
    {
        int came_from_left[4] = {0, 0, 0, 1};
        left = ft_find_path_recursion(player, 
                                     player->pos_x - 1, 
                                     player->pos_y, 
                                     board_x, board_y, 
                                     came_from_left, 
                                     0, 
                                     visited);
        if (left > 0)
            return left;
    }
    
    return -1;  // No path found
}
// Initialize board with random teams
void init_board(t_game *game) {
    srand(time(NULL));
    
    // Clear board
    memset(game->board, 0, sizeof(game->board));
    
    // Fill some positions with random team numbers (1-4)
    for (int i = 0; i < 50; i++) {  // 50 random obstacles/players
        int x = rand() % BOARD_SIZE;
        int y = rand() % BOARD_SIZE;
        game->board[x][y] = (rand() % 4) + 1;  // Team 1-4
    }
}

// Print board section around positions
void print_board_section(t_game *game, int center_x, int center_y, int target_x, int target_y) {
    printf("\nBoard view (7x7 around start):\n");
    
    int start_x = center_x - 3;
    int start_y = center_y - 3;
    int end_x = center_x + 3;
    int end_y = center_y + 3;
    
    // Adjust bounds
    if (start_x < 0) start_x = 0;
    if (start_y < 0) start_y = 0;
    if (end_x >= BOARD_SIZE) end_x = BOARD_SIZE - 1;
    if (end_y >= BOARD_SIZE) end_y = BOARD_SIZE - 1;
    
    for (int y = start_y; y <= end_y; y++) {
        printf("Y=%2d: ", y);
        for (int x = start_x; x <= end_x; x++) {
            if (x == center_x && y == center_y) {
                printf(" S");  // Start position
            } else if (x == target_x && y == target_y) {
                printf(" T");  // Target position
            } else if (game->board[x][y] != 0) {
                printf(" %d", game->board[x][y]);  // Team number
            } else {
                printf(" .");  // Empty
            }
        }
        printf("\n");
    }
}

int main(void) {
    t_game game;
    t_player player;
    
    // Initialize
    player.game = &game;
    init_board(&game);
    
    // Test case 1: Simple diagonal path
    printf("\n=== Test Case 1: Simple Path ===\n");
    player.pos_x = 10;
    player.pos_y = 5;
    int target_x = 16;
    int target_y = 9;
    
    print_board_section(&game, player.pos_x, player.pos_y, target_x, target_y);
    int steps = ft_find_path_to_position(&player, target_x, target_y, 10, 5);
    printf("Path found with %d steps\n", steps);
    
    // Test case 2: Blocked path
    printf("\n=== Test Case 2: Possibly Blocked Path ===\n");
    player.pos_x = 5;
    player.pos_y = 5;
    target_x = 5;
    target_y = 15;
    
    // Add a vertical wall of players
    for (int y = 6; y < 15; y++) {
        game.board[5][y] = 1;
    }
    
    print_board_section(&game, player.pos_x, player.pos_y, target_x, target_y);
    steps = ft_find_path_to_position(&player, target_x, target_y, 0, 0);
    printf("Path found with %d steps\n", steps);
    
    // Test case 3: Edge case - target on edge
    printf("\n=== Test Case 3: Edge Target ===\n");
    player.pos_x = 15;
    player.pos_y = 15;
    target_x = 0;
    target_y = 0;
    
    print_board_section(&game, player.pos_x, player.pos_y, target_x, target_y);
    steps = ft_find_path_to_position(&player, target_x, target_y, 0, 0);
    printf("Path found with %d steps\n", steps);
    
    // Test case 4: Same position
    printf("\n=== Test Case 4: Same Position ===\n");
    player.pos_x = 20;
    player.pos_y = 20;
    target_x = 20;
    target_y = 20;
    
    print_board_section(&game, player.pos_x, player.pos_y, target_x, target_y);
    steps = ft_find_path_to_position(&player, target_x, target_y, 0, 0);
    printf("Path found with %d steps\n", steps);
    
    // Test case 5: Random positions
    printf("\n=== Test Case 5: Random Test ===\n");
    player.pos_x = rand() % BOARD_SIZE;
    player.pos_y = rand() % BOARD_SIZE;
    target_x = rand() % BOARD_SIZE;
    target_y = rand() % BOARD_SIZE;
    
    // Ensure target is not occupied
    while (game.board[target_x][target_y] != 0) {
        target_x = rand() % BOARD_SIZE;
        target_y = rand() % BOARD_SIZE;
    }
    
    printf("Random test: From (%d,%d) to (%d,%d)\n", 
           player.pos_x, player.pos_y, target_x, target_y);
    print_board_section(&game, player.pos_x, player.pos_y, target_x, target_y);
    steps = ft_find_path_to_position(&player, target_x, target_y, 0, 0);
    printf("Path found with %d steps\n", steps);
    
    return 0;
}
