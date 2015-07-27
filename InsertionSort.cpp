// zhiwe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class info {
public:
	string name;
	int ID;
	string ages;
	string position;
	string birthday;
};

int _tmain(int argc, _TCHAR* argv[])
{
	//open file
	ifstream input;
	input.open(argv[1], ios::in);

	//check error
	if (argc < 2) {
		cout << "Missing Command Line Parameter!" << endl;
		exit(1);
	}
	if (!input){
		cout << "File Not Found!" << endl;
		exit(1);
	}

	//first line
	int rfirline;
	string line1;
	getline(input, line1);
	rfirline = stoi(line1);

	//make array
	info** library = new info*[rfirline];

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
	input.close();

	long long comparisonCounter=0;
	long long exchangesCounter=0; 

	//Insertion Sort
	int i=0;
	for(int j =1; j<rfirline; j++){
		info* key = library[j];
		i = j -1;
		while( i >= 0 && library[i]->ID > key->ID){
			comparisonCounter++;
			exchangesCounter++;
			library[i+1] = library[i];
			i = i-1;
		}
		exchangesCounter++;
		library[i+1] = key;
	}

	cout << comparisonCounter <<" comparisons and " << exchangesCounter << " exchanges"<<endl;

	ofstream wr;
	wr.open("Daniel.txt");
	for (int i=0; i<rfirline; i++) {
		wr << library[i]->name<<"|"<< library[i]->ID <<"|"<< library[i]->ages << "|"<< library[i]->position <<"|"<< library[i]->birthday << endl;
	}
	wr.close();

	return 0;
}

