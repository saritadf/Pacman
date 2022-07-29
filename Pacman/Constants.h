#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace constants
{
	enum GhostBehavior
	{
		Wander,
		Chase,
		Intercept,
		Fear,
		Vulnerable,
		Scatter
	};

	enum GhostType
	{
		Red,
		Orange,
		Pink,
		Cyan,
		All
	};

	//Avatar Paths
	inline constexpr const char* ASSET_PATH_RIGHT_AVATAR = "open_right_32.png";
	inline constexpr const char* ASSET_PATH_DOWN_AVATAR = "open_down_32.png";
	inline constexpr const char* ASSET_PATH_LEFT_AVATAR = "open_left_32.png";
	inline constexpr const char* ASSET_PATH_UP_AVATAR = "open_up_32.png";
	
	// Ghosts Paths
	inline constexpr const char* ASSET_PATH_RED_GHOST = "ghost_32_red.png";
	inline constexpr const char* ASSET_PATH_ORANGE_GHOST = "ghost_32_orange.png";
	inline constexpr const char* ASSET_PATH_PINK_GHOST = "ghost_32_pink.png";
	inline constexpr const char* ASSET_PATH_CYAN_GHOST = "ghost_32_cyan.png";

	inline constexpr const char* ASSET_PATH_GHOST_DEAD = "Ghost_Dead_32.png";
	inline constexpr const char* ASSET_PATH_GHOST_VULNERABLE = "Ghost_Vulnerable_32.png";

	// World Paths
	inline constexpr const char* ASSET_PATH_PLAYFIELD = "playfield.png";
	inline constexpr const char* FILE_PATH_MAP = "map.txt";

	// Big Dot Path
	inline constexpr const char* ASSET_PATH_BIG_DOT = "Big_Dot_32.png";

	// Small Dot Path
	inline constexpr const char* ASSET_PATH_SMALL_DOT = "Small_Dot_32.png";

	// Cherry
	inline constexpr const char* ASSET_PATH_CHERRY = "cherry.png";

	// Sprite Size
	inline constexpr const int SPRITE_SIZEX = 32;
	inline constexpr const int SPRITE_SIZEY = 32;

	// Tile Size
	inline constexpr const int TILE_SIZE = 22;

	// Initial Positions
	const int INIT_AVATAR_POSX = 13;
	const int INIT_AVATAR_POSY = 22;

	const int RED_GHOST_POSX = 12;
	const int RED_GHOST_POSY = 10;

	const int PINK_GHOST_POSX = 12;
	const int PINK_GHOST_POSY = 13;

	const int CYAN_GHOST_POSX = 10;
	const int CYAN_GHOST_POSY = 13;

	const int ORANGE_GHOST_POSX = 14;
	const int ORANGE_GHOST_POSY = 13;

	// Display positions
	const int FPS_POSX = 880;
	const int FPS_POSY = 50;

	const int SCORE_POSX = 20;
	const int SCORE_POSY = 50;

	const int LIVES_POSX = 20;
	const int LIVES_POSY = 8;

	// Tunnel Tiles
	const int RIGHT_TUNNEL_TILEX = 25;
	const int LEFT_TUNNEL_TILEX = 0;

	//Ghosts Initial Box
	const int MIN_RANGE_TILEX = 10;
	const int MAX_RANGE_TILEX = 15;

	const int MIN_RANGE_TILEY = 11;
	const int MAX_RANGE_TILEY = 14;

	// Out of the box tile
	const int OUTSIDE_BOX_POSX = 13;
	const int OUTSIDE_BOX_POSY = 10;
}
#endif