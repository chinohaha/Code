// zhiweihou.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

	class info {
		public:
			string name;
			int ID;
			string ages;
			string position;
			string birthday;
	};

	long long comparisonCounter=0;
	long long exchangesCounter=0;
	long long recursive_call=0;
	info** library;
	info** A;
	int rfirline; // length



	int PARTITION(int p, int r){
		info* x = library[r];
		int i = p-1;
		for(int j = p; j<=r-1;j++){
			comparisonCounter++;
			if (library[j]->ID <= x->ID){
				i = i+1;
				exchangesCounter++;
				info* temp = library[i];
				library[i] = library[j];
				library[j] = temp;
				for(int g =0; g< rfirline; g++){
					cout << library[g]->ID<< " ";
				}
				cout << endl;
			}
		}
		exchangesCounter++;
		info* temp = library[i+1];
		library[i+1] = library[r];
		library[r] = temp;
		for(int g =0; g< rfirline; g++){
			cout << library[g]->ID<< " ";
		}
		cout << endl;
		return i+1;
	}

	inline int random(int p, int r)
{
     srand(time(NULL));
     int suiji = rand() % (r - p) + p;
     return suiji;
}

	int RANDOMIZED_PARTITION(int p, int r){
		srand(time(NULL));
		int l = random(p, r);
		info* temp = library[r];
		library[r] = library[l];
		library[l] = temp;
		return PARTITION(p,r);
	}

	void QUICKSORT(int p, int r){
		if (p < r){
		int q = PARTITION(p,r);
		QUICKSORT(p, q-1);
		recursive_call++;
		QUICKSORT(q+1,r);
		recursive_call++;
		}
	}

	void TAIL_RECURSIVE_QUICKSORT(int p, int r){
		while(p < r){
			//Partition and sort left subarray
			int q = PARTITION(p,r);
			TAIL_RECURSIVE_QUICKSORT(p,q-1);
			recursive_call++;
			p = q+1;
		}
	}

	void RANDOMIZED_QUICKSORT(int p, int r){
		if (p < r){
		int q = RANDOMIZED_PARTITION(p,r);
		RANDOMIZED_QUICKSORT(p, q-1);
		recursive_call++;
		RANDOMIZED_QUICKSORT(q+1,r);
		recursive_call++;
		}
	}

int _tmain(int argc, _TCHAR* argv[])
{
	//open file
	ifstream input;
	

	//check error
	if (argc < 2) {
		cout << "Missing Command Line Parameter!" << endl;
		exit(1);
	}
	input.open(argv[1], ios::in);
	if (!input){
		cout << "File Not Found!" << endl;
		exit(1);
	}

	//first line
	string line1;
	getline(input, line1);
	rfirline = stoi(line1);

	//make array
	library = new info*[rfirline];

	for (int i=0; i<rfirline; i++) {
		info* b = new info();
		getline(input, b->name, '|');
		string temp;
		getline(input, temp, '|');
		b -> ID = stoi(temp);
		getline(input, b->ages, '|');
		getline(input, b->position, '|');
		getline(input, b->birthday);
		library[i] = b; 
	}
	A = library;
	input.close();

	//Call QUICKSORT 
	//QUICKSORT(0,rfirline-1);
	RANDOMIZED_QUICKSORT(0,rfirline-1);
	//TAIL_RECURSIVE_QUICKSORT(0,rfirline-1);

	//Comparison and Exchange report
	cout << "Comparisons: " << comparisonCounter << endl;
	cout <<  "Exchanges: " << exchangesCounter << endl;
	cout << "Recursive calls: " << recursive_call <<endl;

	//Write to file
	ofstream wr;
	wr.open("Daniel.txt");
	for (int i=0; i<rfirline; i++) {
		wr << library[i]->name<<"|"<< library[i]->ID <<"|"<< library[i]->ages << "|"<< library[i]->position <<"|"<< library[i]->birthday << endl;
	}
	wr.close();

	return 0;
}

