#ifndef __MINE___GENE__H___
#define __MINE___GENE__H___

struct Mine {
	bool IsClicked;
	bool Flag;
	int value;//0~10
};

class MineGenerator{
	private:
		int StartRow, StartLine;//first click
		Mine ** MineTable;//table
		int row;//size
		int line;//size
		int Flag_count;//지뢰에 세워진 깃발 수
		int real_Flag_count;//실제 세워진 깃발 수
		int Click_count;
		int Mine_count;
	public:
		void DrawMineSweeper();//draw table
		void Generator(int row, int line);//create new table
		void Destroy();//delete table
		int SelectPoint();//select point
		void ZeroPosition(int row, int line);//click table
};

#endif
