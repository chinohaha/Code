// zhiweiho.cpp : Defines the entry point for the console application.
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

	long long comparisonCounter=0;
	long long exchangesCounter=0;
	info** library;
	info** A;
	int rfirline; // length
	int heapSize;

	int LEFT(int i){
		return 2*i+1;
	};

	int RIGHT(int i){
		return 2*i+2;
	};

	void MAX_HEAPIFY(int i){
		int l = LEFT(i);
		int r = RIGHT(i);
		int largest;
		if( l <= heapSize && library[l]->ID > library[i]->ID ){
			largest = l;
		}else { largest = i; }
		if( r <= heapSize && library[r]->ID > library[largest]->ID ){
			largest = r;
		}
		comparisonCounter += 5;
		if (largest != i){
			exchangesCounter++;
			info* temp = library[i];
			library[i] = library[largest];
			library[largest] = temp;
			MAX_HEAPIFY(largest);
		}
	};

	void BUILD_MAX_HEAP(){
		heapSize = rfirline - 1;
		for (int j =(rfirline - 1)/2; j >=0; j-- ){
			MAX_HEAPIFY(j);
		}
	};

	void HEAPSORT(){
		BUILD_MAX_HEAP();
		for (int k = rfirline - 1; k >= 1; k--){
			exchangesCounter++;
			info* temp = library[0];
			library[0] = library[k];
			library[k] = temp;
			heapSize = heapSize -1;
			MAX_HEAPIFY(0);
		}
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

	//HEAPSORT
	cout << "*** HEAP SORT ***" << endl;
	HEAPSORT();

	for(int g =0; g< rfirline; g++){
			cout << library[g]->ID<< " ";
		}
	cout << endl;

	//Comparison and Exchange report
	cout << comparisonCounter <<" comparisons and " << exchangesCounter << " exchanges"<<endl;

	//Write to file
	ofstream wr;
	wr.open("Daniel.txt");
	for (int i=0; i<rfirline; i++) {
		wr << library[i]->name<<"|"<< library[i]->ID <<"|"<< library[i]->ages << "|"<< library[i]->position <<"|"<< library[i]->birthday << endl;
	}
	wr.close();

	return 0;
}