#include<iostream>
#include<fstream>
#include<iomanip>
#include"mineModel.h"
using namespace std;

void mineModel::ReadFile() {
	this->readFile.open("Ranking.txt");
	for(int i=0; i<5; i++)
		readFile>>Rank[i].id>>Rank[i].time>>Rank[i].size;
	this->readFile.close();

	PrintRank();
}

void mineModel::WriteFile() {
	this->writeFile.open("Ranking.txt");
	for(int i=0; i<5; i++)
		writeFile<<Rank[i].id<<Rank[i].time<<Rank[i].size;
	this->writeFile.close();
}

void mineModel::CompareData(RANK rank) {
	//Input New Data
	Rank[5].id = rank.id;
	Rank[5].time = rank.time;
	Rank[5].size = rank.size;

	//using simple sorting algorithm -> cuz) small size of data
	for(int i = 0; i<5; i++) {
		RANK t_rank;
		int index = i;
		t_rank.id = Rank[i].id;
		t_rank.time = Rank[i].time;
		t_rank.size = Rank[i].size;
		for(int j=i+1; j<6; j++) {
			if(t_rank.time == Rank[j].time) {
				if(t_rank.size < Rank[j].size)
					index = j;
			}
			else if(t_rank.time > Rank[j].time) 
				index = j;
		}
		if(index != i) { //find high score
			Rank[i] = Rank[index];
			Rank[index] = t_rank;
		}
	}
}

void mineModel::PrintRank() {
	cout<<"|  ID  |"<<" SIZE |"<<"       TIME       ";
	for(int i=0; i<5; i++) {
		cout<<" "<<setw(6)<<Rank[i].id<<" "<<setw(6)<<Rank[i].size<<" "<<
			Rank[i].time<<endl;
	}
}
