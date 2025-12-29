#include "./lemipc.h"



static const Color g_colors[100] = {
    /* --- Original raylib-like colors (0–23) --- */
    {200,200,200,255}, {130,130,130,255}, {80,80,80,255},
    {253,249,0,255},   {255,203,0,255},   {255,161,0,255},
    {255,109,194,255}, {230,41,55,255},   {190,33,55,255},
    {0,228,48,255},    {0,158,47,255},    {0,117,44,255},
    {102,191,255,255}, {0,121,241,255},   {0,82,172,255},
    {200,122,255,255}, {135,60,190,255},  {112,31,126,255},
    {211,176,131,255}, {127,106,79,255},  {76,63,47,255},
    {255,255,255,255}, {0,0,0,255},       {245,245,245,255},

    /* --- Extended palette (24–99) --- */
    {255,  99,  71,255}, {154,205, 50,255}, { 72,209,204,255},
    { 65,105,225,255}, {218,112,214,255}, {255,182,193,255},
    { 46,139, 87,255}, {255,140,  0,255}, { 70,130,180,255},
    {199, 21,133,255}, {176,196,222,255}, { 34,139, 34,255},
    {255,215,  0,255}, { 95,158,160,255}, {138, 43,226,255},
    {244,164, 96,255}, { 32,178,170,255}, {205,133, 63,255},
    {147,112,219,255}, {240,128,128,255}, { 60,179,113,255},
    {123,104,238,255}, {255,160,122,255}, {  0,206,209,255},
    {186, 85,211,255}, {255,127, 80,255}, { 64,224,208,255},
    {139, 69, 19,255}, {100,149,237,255}, {188,143,143,255},
    {  0,191,255,255}, {219,112,147,255}, { 50,205, 50,255},
    {210,105, 30,255}, {176,224,230,255}, {199, 21, 21,255},
    {173,255, 47,255}, { 72, 61,139,255}, {255, 69,  0,255},
    {127,255,212,255}, {148,  0,211,255}, {240,230,140,255},
    {  0,250,154,255}, {255,105,180,255}, { 25, 25,112,255},
    {189,183,107,255}, {255,228,181,255}, {  0,139,139,255},
    {153, 50,204,255}, {233,150,122,255}, { 47, 79, 79,255},
    {255,222,173,255}, {  0,128,128,255}, {160, 82, 45,255},
    {135,206,250,255}, {178, 34, 34,255}, {107,142, 35,255},
    {216,191,216,255}, { 30,144,255,255}, {220, 20, 60,255},
    {143,188,143,255}, {218,165, 32,255}, { 75,  0,130,255},
    {255,239,213,255}, {  0,100,  0,255}, {255, 20,147,255},
    { 72,209,204,255}, {184,134, 11,255}, {  0,  0,128,255},
    {152,251,152,255}, {255,165,  0,255}, {106, 90,205,255}
};



int	ft_graphic_representation(t_player *player)
{
	int vertical_squares;
	int horizontal_squares;
	int y;
	int x;

	InitWindow(WIDTH, HEIGHT, TITLE);
	SetTargetFPS(60);

	vertical_squares = (HEIGHT / BOARD_Y_LEN);
	horizontal_squares = (WIDTH / BOARD_X_LEN);
	
	while (!WindowShouldClose() && player->game->game_active)
	{
		if (player->game->game_active == 0)
        		break;
	    	BeginDrawing();
	    	ClearBackground(BLACK);

	    	y = 0;
		while (y < BOARD_Y_LEN)
		{
			x = 0;
			while (x < BOARD_X_LEN)
			{
				if (player->game->board[y][x] == 0)
				{
					DrawRectangle(x * horizontal_squares, y * vertical_squares, horizontal_squares, vertical_squares, BLACK);
				}
				else
				{
					int color_index = (player->game->board[y][x] - 1) % 100;
                    			Color c = g_colors[color_index];

                    			DrawRectangle(x * horizontal_squares, y * vertical_squares, horizontal_squares, vertical_squares, c);
				}
				//draw vertical line	
				x++;
			}
			//draw horizental line
			y++;
		}
		/* Draw vertical lines */
		for (x = 0; x <= BOARD_X_LEN; x++)
		{
			int xpos = x * horizontal_squares;
			DrawLine(xpos, 0, xpos, HEIGHT, WHITE);  // color of grid lines
		}

		/* Draw horizontal lines */
		for (y = 0; y <= BOARD_Y_LEN; y++)
		{
			int ypos = y * vertical_squares;
			DrawLine(0, ypos, WIDTH, ypos, WHITE);
		}

		EndDrawing();
	}

	CloseWindow();
	return (0);
}

