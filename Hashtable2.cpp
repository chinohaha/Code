// Zhiweihouwe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <cmath> 
#include <string>

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
int queries; // size of queries 



int hash_StrPri(string k){
		int hash_number = 0;
		string magic = k;
		int prime [168] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997};
		int p = 167;

		//hash key
		for (int y = 0; y < magic.size(); y++){
			hash_number += magic[y] * prime[p];
			p--;
		}

		//hasing
		int index = ( hash_number )  % (firline);
		return index;
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

	//key, size of array m 
	string line1;
	getline(input, line1);
	firline = stoi(line1);
	cout  << "key, size of array m "<<firline << endl;

	//actual recoreds amount of the files, n 
	string line2;
	getline(input, line2);
	secline = stoi(line2);
	cout  << "actual recoreds amount of the files "<<secline << endl;

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

	//get the que file
	string start;
	getline(input, start); // skip the star line
	getline(input, start);
	queries = stoi(start);
	cout  << "queries size " <<queries << endl;
	string* name = new string[ queries ];
	for(int l = 0; l < queries; l++){
		string ques;
		getline(input, ques);
		name[l] = ques;
	}

	input.close();

	/*for(int l = 0; l < queries; l++){
		cout << 
		name[l]<< endl;
	}*/

	int coll=0;

	for (int k = 0; k < secline; k++){

		//hasing division
        int index = hash_StrPri(library[k]->name);
		myArray[index].push_back(library[k]);
		int n = myArray[index].size()-1;
		cout <<"Adding " << library[k]->name <<" to table at index "<< index << "( "<< n <<" collisions)"<<endl;
	}


	//cout << "size of the hash " << myArray[index].size() << endl;
	cout <<endl;


	for (int g = 0; g < queries; g++ ){
		int index = hash_StrPri(name[g]);
		for(int w = 0; w< myArray[index].size(); w++){
			if( name[g] == myArray[index].at(w)->name ){
				coll += w;
				cout<< "Found " << myArray[index].at(w)->name << " after " << w << " collisions at index " << index << " in the hashtable."<< endl;
				cout<< "COMPLETE RECORD: " << myArray[index].at(w)->name << "|"<< myArray[index].at(w)->ID << "|" << myArray[index].at(w)->ages << "|" << myArray[index].at(w)->position << "|" << myArray[index].at(w)->birthday << endl;

			}
		}
	}

	// Collision 
	cout <<" Collision in Look up "<<coll<<endl;
	return 0;
}



