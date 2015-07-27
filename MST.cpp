// zhiwei.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm> 

using namespace std;

class Node;
class Edge;

class Node{
	public:
		vector<Edge*>neihbor;
		char startChar;	
		bool visited;
		Node(char n){
			startChar = n;
			visited = 0;
			//neihbor = NULL;
		}
		vector<Edge*> getNeihbor(){
			return neihbor;
		}
};

class Edge{
	public:
		Node* from;
		Node* to;
		int cost;
		Edge(Node*a, Node*b, int n){
			from = a;
			to = b;
			cost = n;
		}
};

vector<Edge*>BUCKET;
vector<Edge*> allEdge;
vector<Node*> allNode;
string line1;

int mini(){
	int min =0;
	for(int i = 1; i < BUCKET.size(); i++){
		if(BUCKET[i]->cost < BUCKET[min]->cost){
			min = i;
		}
	}
	return min;
}

Edge* GET_BEST_EDGE(){
	Edge* BEST = NULL;
	while(BEST == NULL && BUCKET.size() != 0){
		int small = mini();
		BEST = BUCKET[small];
		if(BEST->from->visited == 1 && BEST->to->visited == 1){
			//myList.erase(myList.begin() + index);
			BUCKET.erase(BUCKET.begin()+small);
			BEST = NULL;
		}
	}
	return BEST;
}

//MST_PEIM
void MST_PEIM(Node* START){
	vector<Edge*> MST_Edges;
	int Total_Weight = 0;
	for(int i =0; i< line1.length();i++){
		allNode[i]->visited = 0;
	}
	//RESIZE EVERYTIME
	BUCKET.resize(line1.size());
	BUCKET = START->getNeihbor();
	Edge* E = GET_BEST_EDGE();
	cout <<E->from->startChar << " - " << E->to->startChar <<endl;
	int Number_of_MST = 0;
	while(E->cost != NULL){
		E->from->visited = 1;
		E->to->visited = 1;
		Total_Weight += E->cost;
		
		MST_Edges.resize(Number_of_MST+1);
		MST_Edges[Number_of_MST] = E;
		/////////////////////////////////////////
		vector<Edge*>neihbor1;
		neihbor1 = E->from->getNeihbor();
		for (int k =0; k < neihbor1.size(); k++){
			BUCKET.push_back(neihbor1[k]);
		}
		vector<Edge*>neihbor2;
		neihbor2 = E->to->getNeihbor();
		for (int k =0; k < neihbor2.size(); k++){
			BUCKET.push_back(neihbor2[k]);
		}
		////////////////////////////////////////
		
		E = GET_BEST_EDGE();
		if ( !E){
			break;
		}
		cout <<E->from->startChar << " - " << E->to->startChar <<endl;
	}
	cout <<"MST has a weight of "<< Total_Weight<< " and consists of these edges:"<<endl;
};


//helper method
int checkM(char a){
	char standard = 'A';
	int number = a - standard;
	//cout << a << number <<endl;
	return number;
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
	getline(input, line1);
	//cout<< line1.length()<< endl;
	allNode.resize(line1.length()+1);
	for(int i = 0;  i< line1.length(); i++){
		Node* n = new Node(line1[i]);
		allNode[i] = n;
	}

	//Making all edge
	string edge;
	int countEdge= 0;
	while (input.good()) {	
		getline(input, edge);
		stringstream ss(edge);
		
		int cost;
		char a;
		ss >> a;
		int check = checkM(a);

		char b;
		ss >> b;
		int check2 = checkM(b);

		ss >> cost;
		Edge* node = new Edge(allNode[check], allNode[check2], cost);

		countEdge++;
		allEdge.resize(countEdge+1);
		allEdge[countEdge] = node;
		allNode[check]->neihbor.push_back(node);
		allNode[check2]->neihbor.push_back(node);  /// may be there are some resize problem
	}


	//call MST_PRIM
	MST_PEIM(allNode[0]);


	return 0;
}

