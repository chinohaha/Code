// zhiweihouweishidan.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <vector>

using namespace std;

	//int* A = new int[20];
   vector <int> A;
   
	int heapSize;

int PARENT(int i){
		return i/2;
};

int LEFT(int i){
	return 2*i;
};

int RIGHT(int i){
	return 2*i+1;
};

//helper
void MAX_HEAPIFY(int i){
	int l = LEFT(i);
	int r = RIGHT(i);
	int largest;
	if( l <= heapSize && A[l] > A[i] ){
		largest = l;
	}else { largest = i; }
	if( r <= heapSize && A[r] > A[largest] ){
		largest = r;
	}
	//comparisonCounter += 5;
	if (largest != i){
		//exchangesCounter++;
		int temp = A[i];
		A[i] = A[largest];
		A[largest] = temp;
		MAX_HEAPIFY(largest);
	}
};

//peek
int HEAP_MAXIMUM(){
	//choose the max
	return A[1];
};

//DEQ
int HEAP_EXTRACT_MAX(){
	/*if(heapSize < 1){
		cerr << "Error:Heap underflow.";
		exit(0);  
	}
	*/
	int max = A[1];
	A[1] = A[heapSize];
	heapSize--;
	MAX_HEAPIFY(1);
	if (max >0){
		cout << max << endl;}
	else{cout << "empty"<<endl; }
	return max;
};

//Helper
void HEAP_INCREASE_KEY(int i, int key){
	/*if(key < A[i]){
		cerr << "Error:New key is smaller than current key";
		exit(0);  
	}*/
	A[i] = key;
	while( i> 1 && A[PARENT(i)] < A[i]){
		int temp = A[i];
		A[i] = A[PARENT(i)];
		A[PARENT(i)] = temp;
		i = PARENT(i);
	}
	
};

//ENQ
void MAX_HEAP_INSERT(int key){
	
	heapSize++;
	A.resize(heapSize+1);
	A[heapSize] = 0;
	HEAP_INCREASE_KEY(heapSize, key);
};

//CLEAR
void CLEAR(){
	heapSize = 0;
};


int firline; // size of array


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


	string line1;
	getline(input, line1);
	firline = stoi(line1);
	for (int i=0; i<firline; i++) {
		string cmd;
		string tmp; // too close
		getline(input, tmp);
		stringstream ss(tmp);
		ss >> cmd;
		//read in instrcutions and number
		if (cmd == "ENQUEUE"){
			int m;
			ss >> m;
			MAX_HEAP_INSERT(m);
		}
		else if (cmd == "DEQUEUE"){
			if(heapSize<1){
				cout << "EMPTY"<<endl;
			}else {
			HEAP_EXTRACT_MAX();
			}
		}
		else if (cmd == "PEEK"){
			int m;
			m = HEAP_MAXIMUM();
			cout <<"Peek :" <<m << endl;
		}
		else if (cmd == "CLEAR"){
			CLEAR();
		}
	}

	return 0;
}

