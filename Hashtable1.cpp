// Zhiweihouw.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <cmath> 

using namespace std;

class info {
		public:
			string name;
			long ID;
			string ages;
			string position;
			string birthday;
	};

info** library;
int firline; // size of array
int secline; // size of file


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

	//The first line is the value of m,size of the array
	string line1;
	getline(input, line1);
	firline = stoi(line1);
	cout  << firline << endl;

	//The second line is n, the number of records contained in the file
	string line2;
	getline(input, line2);
	secline = stoi(line2);
	cout  << secline << endl;


	//make array
	library = new info*[secline];
	vector<vector<info*>> myArray;
	myArray.resize(firline);
	
	for (int i=0; i<secline; i++) {
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

	int coll=0;
	int index = 0;
	for (int k = 0; k < secline; k++){
		//p2
		//hasing division
		index = library[k] -> ID % firline;
		//hasing multiply
		//index = firline*(library[k] -> ID * ((sqrt(5.00)-1)/2) - floor( library[k] -> ID * ((sqrt(5.00)-1)/2)));

		//p1
		/*if (myArray[index].empty()){
			myArray[index].push_back(library[k]);
			cout << "Attempting to hash" << library[k]->name <<"at index"<< index << "... SUCCESS!" << endl;
		}else{
			cout << "Attempting to hash" << library[k]->name <<"at index"<< index << "...OUCH! Collision with "<< library[index]->name << endl;
			coll++;
		}*/

		//p3
		if(myArray[index].size() != 0){
			coll++;
		}
		myArray[index].push_back(library[index]);
		int n = myArray[index].size()-1;
		cout <<"Attempting to hash" << library[k]->name <<"at index"<< index << "( "<< n <<" collisions)"<<endl;
	}
		// Collision 
		cout <<coll<<endl;
		return 0;
}
