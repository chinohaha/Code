// zhiweih.cpp : Defines the entry point for the console application.
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
	info** library;
	info** A;
	int rfirline;
	

//Merge function
void Merge(  int p, int q, int r ){
	int n_1 = q - p + 1;
	int n_2 = r - q;
	info** L = new info*[n_1+1];
	info** R = new info*[n_2+1];

	for(int i =0; i < n_1; i++){
		L[i] = A[p+i];
	}
	for(int j =0; j < n_2; j++){
		R[j] = A[q+j+1];
	}

	info* c = new info();
	c -> ID = 999999;
	L[n_1]  = c;
	
	info* d = new info();
	d -> ID = 999999;
	R[n_2] = d;
	
	int i = 0; 
	int j = 0;
	int k;
	info* e = new info();
	
	for( k = p; k <= r ; k++){
		comparisonCounter++;
		if(L[i]->ID <= R[j]->ID){
			
			A[k] = L[i];
			i += 1;
		}else {
			A[k]=R[j];
			j += 1;
		}
	}


};

void Merge_sort(  int p, int r ){
		if(p < r){
			int q = (p+r)/2;
		//cout << "p "<<p<< endl;
		//cout << "q "<<q<< endl;
		//cout << "r "<<r<< endl;
			Merge_sort( p, q);
			Merge_sort( q+1, r);
			Merge( p, q, r);

			for(int k =0; k< rfirline; k++){
			cout << library[k]->ID<< " ";
			}
			cout << endl;
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


	//Merge sort
	cout << "*** MERGE SORT ***" << endl;
	Merge_sort( 0, rfirline-1);

	//Comparison report
	cout << "comparisons : " << comparisonCounter <<endl;

	//Write to file
	ofstream wr;
	wr.open("Daniel.txt");
	for (int i=0; i<rfirline; i++) {
		wr << library[i]->name<<"|"<< library[i]->ID <<"|"<< library[i]->ages << "|"<< library[i]->position <<"|"<< library[i]->birthday << endl;
	}
	wr.close();

	return 0;
}

