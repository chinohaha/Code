// Zh.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class info {
public:
	string name;
	string ID;
	string ages;
	string position;
	string birthday;
};

int _tmain(int argc, _TCHAR* argv[])
{
	/*roster*/
	//open roster file
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
	info* library = new info[rfirline];

	for (int i=0; i<rfirline; i++) {
		info* b = new info();
		getline(input, b->name, '|');
		getline(input, b->ID, '|');
		getline(input, b->ages, '|');
		getline(input, b->position, '|');
		getline(input, b->birthday);
		library[i] = *b; //here *b means "give me the object that is stored in the memory address referred to in variable b"
	}
	input.close();

	/*queries*/
	//open queries file
	ifstream sinput;
	sinput.open(argv[2], ios::in);

		if (!sinput){
		cout << "File Not Found!" << endl;
		exit(1);
	}

	//first line
	int qfirline;
	string qline1;
	getline(sinput, qline1);
	qfirline = stoi(qline1);

	//make array
	string* que = new string[qfirline];

	int count =0;
	for (int i=0; i<qfirline; i++) {
		getline(sinput, que[i]);
	}
	sinput.close();

	/*Start to compare*/
	double total_com=0.0;
	for (int i=0;i < qfirline; i++){
		double trytime = 0;
		for (int j=0;j < rfirline; j++){
			if ( que[i].compare(library[j].ID) == 0 ){
				trytime += 1.0;
				//cout << "Looking for "<< que[i] << endl;
				//cout << "Found " << library[j].name << " at position " << j << " after " << trytime << " comparisons" << endl;
				total_com += trytime;
				trytime = 0;
			}else { trytime += 1.0; }
		}
	}
	double n = qfirline;
	double ave = total_com / n;
	cout.precision(7) ;
	cout << "Average number of comparisons overall: " << ave << endl;
	/*
	double l = 89602.1;
	cout << l << endl;
	double k = 0.1;
	k= k + 230256.0 +612322.0 +906163.1+ 833230.1 + 989602.1;
	cout << k << endl;
	k= k/5;
	cout << k << endl;
	*/
	return 0;
}

