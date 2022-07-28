#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace constants
{
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
	const float INIT_AVATAR_POSX = 13.f;
	const float INIT_AVATAR_POSY = 22.f;

	const float RED_GHOST_POSX = 12.3f;
	const float RED_GHOST_POSY = 10.5;

	const float ORANGE_GHOST_POSX = 14.3f;
	const float ORANGE_GHOST_POSY = 13;

	const float PINK_GHOST_POSX = 12.7f;
	const float PINK_GHOST_POSY = 13.f;

	const float CYAN_GHOST_POSX = 11.3f;
	const float CYAN_GHOST_POSY = 13.f;

	// Display positions
	const int FPS_POSX = 880;
	const int FPS_POSY = 50;

	const int SCORE_POSX = 20;
	const int SCORE_POSY = 50;

	const int LIVES_POSX = 20;
	const int LIVES_POSY = 8;
}
#endif