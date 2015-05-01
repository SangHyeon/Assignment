#include<iostream>
#include<fstream>
#include"mineModel.h"
using namespace std;

void mineModel::ReadFile() {
	this->readFile.open("Ranking.txt");
	for(int i=0; i<5; i++)
		readFile>>Rank[i].id>>Rank[i].time>>Rank[i].size;
	this->readFile.close();
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

	
}
