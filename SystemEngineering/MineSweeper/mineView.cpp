#include<iostream>
#include"mineView.h"
using namespace std;

void MineViewer::StartGame() {	
	
	cout<<"Do you want to play the MineSweeper? <1: Yes, 0: Quit> "; 
	cin>>GameStart;

	while(GameStart) {
		int row_size, line_size;
		cout<<"Input MineTable Size < (ex)8 6 > ";
		cin>>row_size>>line_size;

		mine.Generator(row_size, line_size);
		
		while(1) {
			int game;
			game = mine.SelectPoint();
			if(game == 1) {
				cout<<"You Win!!!"<<endl;
				break;
			}
			else if(game == 2) {
				cout<<"You Lose!!!"<<endl;
				break;
			}
		}
		
		mine.Destroy();
		cout<<"Do you want to play the MineSweeper? <1: Yes, 0: Quit> "; 
		cin>>GameStart;
	}
}
