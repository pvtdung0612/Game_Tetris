#ifndef _DATA_H_
#define _DATA_H_

#include <iostream>
#include <SDL.h>

using namespace std;

namespace data {
	enum Window
	{
		SCREEN_WIDTH = 705,
		SCREEN_HEIGHT = 610,
	};
	enum Launch_play
	{
		BORDER = 5,
		BORDER_CELL = 5,
		CELL_SIZE = 30,
		NUM_WIDTH = 15,
		NUM_HEIGHT = 20,
		BOARD_BLOCK_WIDTH = 450,
		BOARD_BLOCK_HEIGHT = 600,
	};
	enum Launch_Hight_Score {
		NUM_HIGHT_SCORE = 10,
	};
	struct Info_Player
	{
		string name;
		int mark;
		int level;
		int num_block;
		double time_play;
	};
	namespace level1 {

	    const int mark = 100;
	 	const double speed = 1;
	
	}
	namespace level2 {
		const int mark = 200;
		const double speed = 0.8;
	}
	namespace level3 {
		const int mark = 300;
		const double speed = 0.6;
	}
	namespace level4 {
		const int mark = 400;
		const double speed = 0.4;
	}
	namespace level5 {
		const int mark = 500;
		const double speed = 0.2;
	}
	namespace level6 {
		const int mark = 600;
		const double speed = 0.1;
	}
}
#endif // !_DATA_H_
