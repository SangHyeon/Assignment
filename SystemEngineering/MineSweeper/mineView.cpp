#include<iostream>
#include"mineView.h"
#include"mineModel.h"
#include<time.h>
using namespace std;

void MineViewer::StartGame() {	
	mineModel model;
	MineGenerator mine;
	clock_t start_time, end_time;//게임 시간 측정
	RANK rank;//Ranking data

	cout<<"Do you want to play the MineSweeper? <1: Yes, 0: Quit> "; 
	cin>>GameStart;

	while(GameStart) {
		int row_size, line_size;
		int registration;
		bool win=false;
		cout<<"Input MineTable Size < (ex)8 6 > ";
		cin>>row_size>>line_size;

		mine.Generator(row_size, line_size);
		
		start_time = clock();//start time of game

		while(1) {
			int game;
			game = mine.SelectPoint();
			if(game == 1) {
				cout<<"You Win!!!"<<endl;
				win = true;
				break;
			}
			else if(game == 2) {
				cout<<"You Lose!!!"<<endl;
				break;
			}
		}
		
		end_time = clock();//end time!!
	
		model.PrintRank();
		if(win) {
			cout<<"Do you want to register Rank? <1: Yes, 0: No> ";
			cin>>registration;

			if(registration == 1) {
				cout<<"asdfasdf"<<endl;
				string id;
				cout<<"Input Your ID (under 6) : ";
				cin>>id;
				rank.id = id;
				rank.time = (double)(end_time - start_time);//CLOCKS_PER_SEC;
				rank.size = (int)(row_size*line_size);
				model.CompareData(rank);
				model.PrintRank();
			}
		}
		mine.Destroy();
		cout<<"Do you want to play the MineSweeper? <1: Yes, 0: Quit> "; 
		cin>>GameStart;
	}
}
