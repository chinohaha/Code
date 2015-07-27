// Zhi.cpp : Defines the entry point for the console application.

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

double trytime;

int BS( int x, int T[], int p, int r){
	int low = p; 
	int high = max(p,r+1);
	cout << "Looking for " << x << endl;
	while (low < high){
		trytime++;
		int mid = ((low + high)/2);
		if(x <= T[mid]){
			high = mid ;}
		else{ 
			low = mid +1;}
		}
	return high;
}

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
		library[i] = *b; 
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
	int* quecom = new int[qfirline];

	int count =0;
	for (int i=0; i<qfirline; i++) {
		getline(sinput,que[i]);
		quecom[i]= stoi(que[i]);
	}
	sinput.close();

	int* T = new int[rfirline];
	for (int i=0; i<rfirline; i++) {
		T[i] = stoi(library[i].ID);
	}
	
	double tttrytime=0;
	double final=0;
	/*BS*/
	for (int i=0;i < qfirline; i++){
	 cout.precision(7);
	 int ans = BS( quecom[i],T, 0,  rfirline);
	 
	 cout <<"Found "<< library[ans].name << " at position " << ans << " after " << trytime << " comparisons" << endl;
	 
	 tttrytime += trytime;
	 
	 final = tttrytime/qfirline;
	 trytime = 0;
	 
	 
	}
	cout <<"Average number of comparisons overall: "<< final << endl;
	return 0;
}