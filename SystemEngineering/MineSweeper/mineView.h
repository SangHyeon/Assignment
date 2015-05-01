#ifndef __MINEVIEWER___H__
#define __MINEVIEWER___H__

#include"mineGene.h"

class MineViewer {
	private:
		MineGenerator mine;
		int GameStart;
	public:
		void StartGame();
};

#endif
