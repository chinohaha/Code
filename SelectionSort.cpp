// zhiwei.cpp : Defines the entry point for the console application.
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

	//Selection sort
	cout << "*** SELECTION SORT ***" << endl;
	for(int k =0; k< rfirline; k++){
			cout << library[k]->ID<< " ";
	}
	cout << endl;

	long long comparisonCounter=0;
	long long exchangesCounter=0; 
	
	int min = 0;
	int minIndex = 0;
	for(int i =0; i<=rfirline-2; i++){
		min = library[i]->ID;
		minIndex = i;
		for( int j = i; j < rfirline; j++){
			comparisonCounter++;
			if (library[j]->ID < min){
				min = library[j]->ID;
				minIndex = j;
				//cout <<"minIndex:"<<minIndex <<endl;
			}
		}

		
		exchangesCounter++;
		info* temp = library[i];
	    library[i] = library[minIndex];
		library[minIndex] = temp;
		

		for(int k =0; k< rfirline; k++){
			cout << library[k]->ID<< " ";
		}
		cout << endl;
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

