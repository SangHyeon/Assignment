#include"mineGene.h"
#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;

void MineGenerator::DrawMineSweeper() {
	cout<<endl;
	for(int i = 0; i < this->row; i++) {
		for(int j = 0; j < this->line; j++) {
			if(MineTable[i][j].IsClicked){
				if(MineTable[i][j].Flag)
					cout<<"◻︎ ";//Flag
				else if(MineTable[i][j].value == 10)
					cout<<"* ";//Mine
				else if(MineTable[i][j].value >= 0 && MineTable[i][j].value < 9)
					cout<<MineTable[i][j].value<<" ";
				else
					cout<<endl<<endl<<"ERROR"<<endl<<endl;//error
			}
			else {
				cout<<"◼︎ ";
			}
		}
		cout<<endl;
	}
	cout<<endl;

	for(int i=0; i<this->row; i++) {
		for(int j=0; j<this->line;j++) 
			cout<<MineTable[i][j].value<<" ";
		cout<<endl;
	}
	cout<<endl;

}

void MineGenerator::Generator(int row, int line) {
	//int MineCount;//Mine number
	int count;//count Mine
	int t_row, t_line;//Mine Position
	int s_row, s_line;//Start Position
	Mine_count = (int)(row*line)/4;//set Mine number
	this->row = row;
	this->line = line;
	Click_count = 0;
	Flag_count = 0;
	real_Flag_count = 0;
	count = 0;//set count
	
	//Generate MineTable
	MineTable = new Mine*[row];
	for(int i = 0; i < row; i++)
		MineTable[i] = new Mine[line];
	
	//Initializing Table
	for(int i=0; i<row; i++)
		for(int j=0; j<line; j++) {
			MineTable[i][j].value = 0;
			MineTable[i][j].IsClicked = false;
			MineTable[i][j].Flag = false;
		}
	
	//start & Draw?
	DrawMineSweeper();
	cout<<"Input the your position <row, column>: ";
	
	while(1) {
		cin>>s_row>>s_line;
		if( (s_row > 0 && row >= s_row) && (s_line > 0 && line >= s_line))
			break;
	}
	Click_count++;
	s_row--; s_line--;	
	//set Random position
	srand(time(0));

	while(1) {
		t_row = rand()%row;
		t_line = rand()%line;
		if( (MineTable[t_row][t_line].value == 10) || ((t_row == s_row) && (t_line == s_line)) )
			continue;
		else {
			MineTable[t_row][t_line].value = 10;//It is Mine
			count++;
		}
		
		if(count == Mine_count)
			break;//stop making Mine
	}

	//set other table => have count of mine
	//Mine 주위의 table에 값들을 ++ 시켜줌 => 알아서 다 채우게 됨
	for(int i=0; i<row; i++) {
		for(int j=0; j<line; j++) {
			if(MineTable[i][j].value == 10) {
				if( (row>i+1) )
					if(MineTable[i+1][j].value != 10)
						MineTable[i+1][j].value++;
				
				if( (row>i+1) && (line>j+1)) 
					if(MineTable[i+1][j+1].value != 10)
						MineTable[i+1][j+1].value++;
				
				if( line>j+1 ) 
					if(MineTable[i][j+1].value != 10)
						MineTable[i][j+1].value++;
				
				if( (i-1>=0) && (line>j+1) ) 
					if(MineTable[i-1][j+1].value != 10)
						MineTable[i-1][j+1].value++;
				
				if( (i-1>=0) ) 
					if(MineTable[i-1][j].value != 10)
						MineTable[i-1][j].value++;
				
				if( (i-1>=0) && (j-1>=0) ) 
					if(MineTable[i-1][j-1].value != 10)
						MineTable[i-1][j-1].value++;
				
				if( j-1>=0 ) 
					if(MineTable[i][j-1].value != 10)
						MineTable[i][j-1].value++;

				if( (row>i+1) && (j-1>=0) ) 
					if(MineTable[i+1][j-1].value != 10)
						MineTable[i+1][j-1].value++;
			}
		}
	}

	//start!!
	MineTable[s_row][s_line].IsClicked = true;
	if(MineTable[s_row][s_line].value == 0)
		ZeroPosition(s_row, s_line);
	DrawMineSweeper();
	cout<<"END OF GENERATOR"<<endl;
}

void MineGenerator::Destroy() {
	for(int i = 0; i < this->line; i++)
		delete [] MineTable[i];
	delete [] MineTable;
}

/*
 * return value
 * -1 : error
 *  0 : normal
 *  1 : WIN
 *  2 : LOSE
 */
int MineGenerator::SelectPoint() {
	int row, line;
	int flag;
	cout<<"Input the your position <row, column>: ";
	while(1) {
		cin>>row>>line;
		if( ((row > 0) && (this->row >= row)) && ((line > 0) && (this->line >= line)) )
			break;
		else
			cout<<"OUT OF SIZE : Re-Input position> ";
	}
	row--; line--;
	//If select flag
	if(MineTable[row][line].Flag) {
		cout<<"Do you want to remove the mark? <1: Yes, 0: No>: ";
		cin>>flag;
		if(flag) {
			if(MineTable[row][line].value == 10) {
				real_Flag_count--;
				Flag_count--;//very 아쉽
			}
			else
				real_Flag_count--;
		
			MineTable[row][line].Flag = false;
			MineTable[row][line].IsClicked = false;
			Click_count--;
		}
		DrawMineSweeper();
		return 0;//normal
	}

	cout<<"Do you want to mark the sweeper? <1: Yes, 0: No>: ";
	cin>>flag;

	if(!MineTable[row][line].IsClicked) {
		Click_count++;
		MineTable[row][line].IsClicked = true;
		if(flag) {
			if(MineTable[row][line].value == 10) {
				real_Flag_count++;
				Flag_count++;//corect
			}
			else
				real_Flag_count++;

			MineTable[row][line].Flag = true;
			cout<<Flag_count<<" "<<Mine_count<<" "<<Click_count<<" "<<this->row*this->line<<endl;	
			if( (real_Flag_count == Flag_count) && (Flag_count == Mine_count) && (Click_count == (this->row*this->line)) ) {
				DrawMineSweeper();
				return 1;//you win
			}
		}
		else {
			if(MineTable[row][line].value == 10) {
				DrawMineSweeper();
				return 2;//you lose
			}
		}
		
		if(MineTable[row][line].value == 0)
			ZeroPosition(row, line);
		DrawMineSweeper();
		if( (real_Flag_count == Flag_count) && (Flag_count == Mine_count) && (Click_count == (this->row*this->line)) ) {
			DrawMineSweeper();
			return 1;//you win
		}
		return 0;//normal
	}
	else {
		cout<<"ERROR : RETRY"<<endl;
		return -1;//error
	}
}

/*
 * 0인 경우에는 주위에 지뢰가 없으므로
 * 주위의 값들을 자동으로 click한 상태로
 */
void MineGenerator::ZeroPosition(int i, int j) {

	if( row>i+1 ) {
		if(!(MineTable[i+1][j].Flag || MineTable[i+1][j].IsClicked)) {
			MineTable[i+1][j].IsClicked = true;
			Click_count++;

			if(MineTable[i+1][j].value == 0)
				ZeroPosition(i+1, j);//click했는데 또 0 나오면 재귀를 이용함
		}
	}

	if( (row>i+1) && (line>j+1)) {
		if(!(MineTable[i+1][j+1].Flag || MineTable[i+1][j+1].IsClicked)) {
			MineTable[i+1][j+1].IsClicked = true;
			Click_count++;

			if(MineTable[i+1][j+1].value == 0)
				ZeroPosition(i+1, j+1);
		}
	}

	if( line>j+1 ) { 
		if(!(MineTable[i][j+1].Flag || MineTable[i][j+1].IsClicked)) {
			MineTable[i][j+1].IsClicked = true;
			Click_count++;

			if(MineTable[i][j+1].value == 0)
				ZeroPosition(i, j+1);
		}
	}

	if( (i-1>=0) && (line>j+1) ) { 
		if(!(MineTable[i-1][j+1].Flag || MineTable[i-1][j+1].IsClicked)) {
			MineTable[i-1][j+1].IsClicked = true;
			Click_count++;

			if(MineTable[i-1][j+1].value == 0)
				ZeroPosition(i-1, j+1);
		}
	}

	if( (i-1>=0) ) {
		if(!(MineTable[i-1][j].Flag || MineTable[i-1][j].IsClicked)) {
			MineTable[i-1][j].IsClicked = true;
			Click_count++;

			if(MineTable[i-1][j].value == 0)
				ZeroPosition(i-1, j);
		}
	}

	if( (i-1>=0) && (j-1>=0) ) {
		if(!(MineTable[i-1][j-1].Flag || MineTable[i-1][j-1].IsClicked)) {
			MineTable[i-1][j-1].IsClicked = true;
			Click_count++;

			if(MineTable[i-1][j-1].value == 0)
				ZeroPosition(i-1, j-1);
		}
	}

	if( j-1>=0 ) {
		if(!(MineTable[i][j-1].Flag || MineTable[i][j-1].IsClicked)) {
			MineTable[i][j-1].IsClicked = true;
			Click_count++;

			if(MineTable[i][j-1].value == 0)
				ZeroPosition(i, j-1);
		}
	}

	if( (row>i+1) && (j-1>=0) ) {
		if(!(MineTable[i+1][j-1].Flag || MineTable[i+1][j-1].IsClicked)) {
			MineTable[i+1][j-1].IsClicked = true;
			Click_count++;

			if(MineTable[i+1][j-1].value == 0)
				ZeroPosition(i+1, j-1);
		}
	}

}
