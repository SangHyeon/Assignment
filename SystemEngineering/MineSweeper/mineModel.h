#ifndef __MINEMODEL___H___
#define __MINEMODEL___H___
#include<string>
#include<fstream>
using namespace std;

struct RANK {
	string id;
	double time;
	int size;
};

class mineModel {
	private:
		RANK Rank[6];//0~4 : current, 5 : new data
		ifstream readFile;
		ofstream writeFile;

	public:
		void ReadFile();
		void WriteFile();
		void CompareData(RANK rank);
		void PrintRank();
};

#endif
