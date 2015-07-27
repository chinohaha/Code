#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <map>  //unordered_map cannot be use
#include <bitset> 
#include <ctime>

using namespace std;

map <char, string> Char2Code;   
map <string, char> Code2Char;

void timeWaster() {
	int dummy = 0;
	for (int i = 0; i < 100000000; i++) {
		dummy++;
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
	input.open(argv[1], ios::in|ios::binary);
	if (!input){
		cout << "File Not Found!" << endl;
		exit(1);
	}
	while (input.good()) {
		string tmp;
		getline(input, tmp);
		if(tmp[0] == '*'){
		break;
		}else{
			stringstream ss(tmp);
			string chrs;
			char chr;
			string cod;
			ss >> cod;
			ss >> chrs;
			if(chrs == "space"){
				chr = ' ';
			}
			else if(chrs == "newline"){
				chr = '\n';
			}
			else if(chrs == "tab"){
				chr = '\t';
			}
			else{
				chr = chrs[0];
			}
			Char2Code[chr] = cod;
			Code2Char[cod] = chr;
		}
	}
	
	/*cout << "Char2Code.size() is " << Char2Code.size() << endl;
	map<char,string>::iterator it;

	for (std::map<char,string>::iterator it=Char2Code.begin(); it!=Char2Code.end(); ++it){
		if(it->first == ' '){
			cout << "space" << " -- " << it->second <<endl;
		}
		else if(it->first == '\n'){
			cout << "\\n" << " -- " << it->second <<endl;
		}
		else if(it->first == '\t'){
			cout << "\\t" << " -- " << it->second <<endl;
		}
		else{
			cout << it->first << " -- " << it->second <<endl;
		}
	}*/
	
	//into binary
	string line1;
	string binary;
	bitset<8> mybits;
	int useful;		 //signaficant number
	getline(input, line1);
	useful = stoi(line1);
	//cout<< useful<< endl;
	int readbin = 0;
	while (input.good()) {
		string decode;
		char readin;
		input.get(readin);
		readbin++;
		line1 = readin;
		mybits = bitset<8>(readin);
		//cout << mybits<<endl; 
		binary += mybits.to_string<char,std::string::traits_type,std::string::allocator_type>();
	}
	//cout<<readbin<<endl;

	//into message
	//cout << binary<<endl;         //binary string
	//cout << binary.length()<<endl;	//total bits
	//cout << useful<<endl;			//how many bits is useful
	int useless = binary.length() - useful;
	string compare;

	//Write to file
	//split the file path
	string fileName = argv[1];
	char* context	= NULL;
	char *token = strtok_s( const_cast<char*>( fileName.c_str() ), ":. \\" ,&context);
	std::vector<string> values;
	while ( token != NULL ) {
		// save the numeral
		values.push_back( string(token) );
		// get next token 
		token = strtok_s( NULL, ":. \\" ,&context);
	}
	string baseFilename(values[values.size()-2]);
	string newFilename(baseFilename + "2.txt");
	
	
	
	ofstream wr(newFilename.c_str(), std::ios::out | std::ios::binary);
	//wr.open(newFilename.c_str());
	for(int l = 0; l<binary.length()-useless; l++){
		compare += binary[l];
		//wr<< binary[l];
		for (std::map<char,string>::iterator it=Char2Code.begin(); it!=Char2Code.end(); ++it){
			if( it->second == compare){
				wr << it->first;
				compare ="";
			}
		}
	}

	wr.close();

	float ticksPerSecond = CLOCKS_PER_SEC;
	clock_t startingTime = clock();
	cout << "starting..." << endl;

	timeWaster();

	clock_t firstHurdle = clock();
	cout << "First Hurdle! " << ((firstHurdle - startingTime) / ticksPerSecond) << " sec" << endl;

	timeWaster();

	clock_t secondHurdle = clock();
	cout << "Second Hurdle! " << ((secondHurdle - firstHurdle) / ticksPerSecond) << " sec" << endl;

	timeWaster();

	clock_t thirdHurdle = clock();
	cout << "Third Hurdle! " << ((thirdHurdle - secondHurdle) / ticksPerSecond) << " sec" << endl;

	cout << "DONE! Total time: " << ((thirdHurdle - startingTime) / ticksPerSecond) << " sec" << endl;

	return 0;
}