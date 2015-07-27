// Hou.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <vector>

using namespace std;

//Brother Draper's 2d array
class TwoDimIntArray {
private:
	int* data;
	int sizeX, sizeY;

public:
	TwoDimIntArray(int x, int y) {
		sizeX = x;
		sizeY = y;
		data = new int[x*y];
	}

	~TwoDimIntArray() {
		delete[] data;
	}

	int get(int x, int y) {
		return data[y*sizeX + x];
	}

	void set(int x, int y, int val) {
		data[y*sizeX + x] = val;
	}
};

	TwoDimIntArray* B;
	TwoDimIntArray* C;
	string line1;
	string line2;
	int vertical = 0; //'v'+'e'+'r';
	int oblique = 1;//'o'+'b'+'l';
	int horizon = 2;//'h'+'o'+'r';

	//Building 2d table
	void LCS_LENGTH(){
		int m = line1.length();
		int n = line2.length();
		TwoDimIntArray* b = new TwoDimIntArray(m+1,n+1);
		TwoDimIntArray* c = new TwoDimIntArray(m+1,n+1);
		for( int i=0; i <= m; i++){
			c->set(i,0,0);
		}
		for(int j =0; j <= n; j++){
			c->set(0,j,0);
		}
		
		for(int i =1; i<= m; i++){
			for(int j = 1; j<=n; j++){
				//cout<< "i" << i<<endl;
				//cout<< "j" << j<<endl;
				if(line1[i-1] == line2[j-1]){
					c->set(i,j,c->get(i-1,j-1)+1);
					b->set(i,j, oblique );
				}
				else if(c->get(i-1,j) >= c->get(i,j-1)){
					c->set(i,j,c->get(i-1,j));
					b->set(i,j, vertical );
				}
				else {
					c->set(i,j,c->get(i,j-1));
					b->set(i,j, horizon );	
				}
			
			
			}
		}
	
		B = b;
		C = c;
	}

	//Print out the LCS
	void Print_LCS(int i, int j){
		if (i == 0 || j == 0){
			return;
		}
		if ( B->get(i,j) == oblique ){
			Print_LCS(i-1, j-1);
			cout << line1[i-1];
		}
		else if ( B->get(i,j) == vertical ){
			Print_LCS(i-1, j);
		} 
		else {
			Print_LCS(i, j-1);
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

	getline(input, line1);
	getline(input, line2);

	cout << "String X: " << line1 << endl;
	cout << "String Y: " << line2 << endl;

	//Call LCS-length
	LCS_LENGTH();
	cout << "LCS: ";
	Print_LCS(line1.length(),line2.length());
	cout<< endl;
	return 0;
}

