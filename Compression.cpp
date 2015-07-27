// ZhiweiandZoram.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm> 
#include <map>  //unordered_map cannot be use
#include <ctime>

using namespace std;

class Node;

class Node{
	public:
		char ch;
		int fre;
		Node* left;
		Node* right;
		Node(char n){
			ch = n;
			fre = 1;
			left = NULL;
			right = NULL;
		}
		int getFreq(){
			return fre;
		}
};

vector<Node*> AllNode;
map <char, string> Char2Code;   
map <string, char> Code2Char;
vector <Node*> A;
vector <char> wholeString;
int heapSize;
vector<Node*> Q;
string Master;
long int MasterNum;
string encode;

//// MIN PQ
int PARENT(int i){
	return i/2;
};
int LEFT(int i){
	return 2*i;
};

int RIGHT(int i){
	return 2*i+1;
};

void MIN_HEAPIFY(int i){
	int l = LEFT(i);
	int r = RIGHT(i);
	int smallest;
	if( l <= heapSize && A[l]->fre < A[i]->fre ){
		smallest = l;
	}else { smallest = i; }
	if( r <= heapSize && A[r]->fre < A[smallest]->fre ){
		smallest = r;
	}
	if (smallest != i){
		Node* temp = A[i];
		A[i] = A[smallest];
		A[smallest] = temp;
		MIN_HEAPIFY(smallest);
	}
};

Node* HEAP_EXTRACT_MIN(){
	Node* min = A[1];
	A[1] = A[heapSize];
	heapSize--;
	MIN_HEAPIFY(1);
	return min;
};

void HEAP_DECREASE_KEY(int i, Node* key){
	A[i] = key;
	while( i> 1 && A[PARENT(i)]->fre > A[i]->fre){
		Node* temp = A[i];
		A[i] = A[PARENT(i)];
		A[PARENT(i)] = temp;
		i = PARENT(i);
	}
};

void MIN_HEAP_INSERT(Node* key){
	//cout<< "PLease be here" << endl;  //for test
	heapSize++;
	A.resize(heapSize+1);
	//Node* head = new Node('head');
	//A[heapSize] = head;
	A.push_back(key); 
	HEAP_DECREASE_KEY(heapSize, key);
};

//// Huffman code
Node* Huffman(){
	Node* head = new Node('head');
	head->fre = 900;
	A.push_back(head);
	int n = AllNode.size();
	for(int k = 0; k<AllNode.size(); k++){
		MIN_HEAP_INSERT(AllNode[k]);
	}
	//HEAP_EXTRACT_MIN();
	for(int i = 0 ; i < n; i++){
		Node* z = new Node(' '); // suposse the ch here does not matter

		Node* X = new Node(' ');
		X = HEAP_EXTRACT_MIN();
		z->left = X;

		Node* Y = new Node(' ');
		Y = HEAP_EXTRACT_MIN();
		z->right = Y;

		//cout<<"X"<<X->fre<<endl;
		//cout<<"Y"<<Y->fre<<endl;
		z->fre = X->fre + Y->fre;
		MIN_HEAP_INSERT(z);
	}
	return HEAP_EXTRACT_MIN(); //root->fre need to find charater before use
};

void DF(Node* r, string path ){
	if(!(r->left) && !(r->right)){
		Char2Code[r->ch] = path;
	}else {
		DF(r->left,path+"0");
		DF(r->right,path+"1");
	}
}

void Traverse(){
	Node* Root = Huffman();
	DF(Root, "");
}

int ConvertBinary2Decimal(int bin)
{
    int dec = 0, pos = 0;
    int factor = 1;
 
    while(bin > 0)
    {
        if( (bin % 10) == 1)
        {
            dec += factor;
        }
        bin /= 10;
        pos++;
        factor = factor * 2;
    }
 
    return dec;
}

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
	input.open(argv[1], ios::in);
	if (!input){
		cout << "File Not Found!" << endl;
		exit(1);
	}

	//Puting in all nodes
	while (input.good()) {
		char readin;
		input.get(readin);
		wholeString.push_back(readin);
		bool tempb=1;
		for(int j = 0; j < AllNode.size();j++){
			if(readin == AllNode[j]->ch){
				AllNode[j]->fre++;
				tempb = 0;
			}
		}
		if(tempb){
			if(readin == '\n'){
				Node* n = new Node('\n');
				AllNode.push_back(n);
				tempb=1;
			}
			else if(readin == '\r'){
				Node* n = new Node('\r');
				AllNode.push_back(n);
				tempb=1;
			}
			else if(readin == '\t'){
				Node* n = new Node('\t');
				AllNode.push_back(n);
				tempb=1;
			}
			else{
				Node* n = new Node(readin);
				AllNode.push_back(n);
				tempb=1;
			}
		}
	}

	////print fre
	/*for(int k =0; k < AllNode.size(); k++){
		if(AllNode[k]->ch == '\n'){
			
			cout << "\\n" << " " << AllNode[k]->fre << endl;
		}
		else if(AllNode[k]->ch == '\r'){
			cout << "\\r" << " " << AllNode[k]->fre << endl; // does not have any
		}
		else if(AllNode[k]->ch == '\t'){
			cout << "\\t" << " " << AllNode[k]->fre << endl;
		}
		else if(AllNode[k]->ch == ' '){
			cout << "space" << " " << AllNode[k]->fre << endl;
		}
		else{
		cout << AllNode[k]->ch << " " << AllNode[k]->fre << endl;
		}

	}*/


	Traverse();
	//cout << "A size" << heapSize<< endl;
	//A.erase(A.begin()+0);
	//for(int k = 0; k<A.size();k++){
	//	cout << A[k]->fre<<endl;
	//}

	//cout << "Char2Code.size() is " << Char2Code.size() << endl;

	//Write to file
	//split the file path
	string fileName = argv[1];
	char* context	= NULL;
	char *token = strtok_s( const_cast<char*>( fileName.c_str() ), ":. \\" ,&context);
	std::vector<string> values;
	while ( token != NULL ) {
		// save the numeral
		values.push_back( string(token) );
		// get next token (if any)
		token = strtok_s( NULL, ":. \\" ,&context);
	}
	string baseFilename(values[values.size()-2]);
	string newFilename(baseFilename + ".zip301");

	ofstream wr;
	wr.open(newFilename.c_str());
	map<char,string>::iterator it;
	for (std::map<char,string>::iterator it=Char2Code.begin(); it!=Char2Code.end(); ++it){
		if(it->first == ' '){
			wr << it->second << " " << "space" << '\n';
		}
		else if(it->first == '\n'){
			wr << it->second << " " << "newline" << '\n';
		}
		else if(it->first == '\t'){
			wr << it->second << " " << "tab" << '\n';
		}
		else{
			wr << it->second << " " <<  it->first << '\n';
		}
	}

	wr << "*****"<< endl;

	for(int y = 0; y < wholeString.size(); y++){
		Master += Char2Code[wholeString[y]];
	}
	//cout << Master<< endl;
	MasterNum = Master.length();
	wr << Master.length()<< endl;
	int extra = MasterNum%8;

	for(int x = 0; x< MasterNum-extra; x+=8){
		string m = Master.substr(x, 8);
		int bin = stoi(m);
		//cout << bin<<endl;
		int mi = ConvertBinary2Decimal(bin);
		char ac = static_cast<char>(mi); 
		encode += ac;
	}
	//handle extra bits
	string more;
	for(int g=0;g<extra;g++){
		more += Master[g];
	}
	for(int g=0;g<8-extra;g++){
		more +="0";
	}
	int bin = stoi(more);
	//cout << bin<<endl;
	int mi = ConvertBinary2Decimal(bin);
	char ac = static_cast<char>(mi); 
	encode += ac;
	//cout<<" "<< more<<endl;

	wr << encode << endl;
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

