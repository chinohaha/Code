// zhiweihouwei.cpp : Defines the entry point for the console application.
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

class Node{
	public:
		int key;
		Node* left;
		Node* right;
		Node(int n){
			key = n;
			left = NULL;
			right = NULL;
		}
};

Node* root;

void Print(Node* n){
	if(n != NULL){
		cout<< "Node: "<< n->key << " L: ";
			if ( n->left == NULL ){  
				cout << " NULL "; }
			else {
				cout << n->left->key;
			}
			cout << " R: ";
				if ( n->right == NULL ){  
				cout << " NULL "; }
			else {
				cout << n->right->key;
			}
			cout << endl;
			Print( n->left );
			Print( n->right );
	}
};

void TreeInsert(Node* z){
	Node* y = NULL;
	Node* x = root;
	while( x != NULL ){
		y = x;
		if ( z->key < x->key ){
			x = x->left;
		}else {
			x = x->right;
		}
	}
	if ( y == NULL ){
		root = z;
	}
	else if( z->key < y->key ){
		y->left = z;
	}
	else{
		y->right = z;
	}
};

void Inorder(Node* n){
	if (n != NULL){
		Inorder(n->left);
		cout << n->key << " ";		
		Inorder(n->right);
	}
};

void Postorder(Node* n){
if (n != NULL){
		Postorder(n->left);
		Postorder(n->right);
		cout << n->key << " ";		
	}
};

void Preorder(Node* n){
if (n != NULL){
		cout << n->key << " ";	
		Preorder(n->left);
		Preorder(n->right);
	}
};

void Find(Node* n, int m){
	if(n != NULL){
		//cout << n->key;
		if(n->key >m){
			//cout<< "key, go n->left" <<endl;
			cout << n->key << " ";
			Find(n->left,m);
		}
		else if(n->key < m){
			//cout<< "key, go n->right" <<endl;
			cout << n->key << " ";
			Find(n->right,m);
		}
		else if(n->key == m) {
			cout << n->key ;
			cout << " : Found!";
		}
	}
	else {cout << " : Not Found!";}
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

	//size of array m 
	string line1;
	getline(input, line1);
	firline = stoi(line1);
	//cout  << "size of array m :"<<firline << endl;

	for (int i=0; i<firline; i++) {
		string cmd;
		string tmp; // too close
		getline(input, tmp);
		stringstream ss(tmp);
		ss >> cmd;
		if (cmd == "ADD") {
			int n;
			ss >> n;
			Node* node = new Node(n);// n be inside
			TreeInsert(node);
			cout << "Adding "<< n <<endl;
		}
		else if(cmd == "FIND"){
			int m;
			ss >> m;
			cout <<"Looking for " << m <<" ... " ;
			Find(root, m);
			cout << endl;
		}
		else if(cmd == "CLEAR"){
			root = NULL;
		}
		else if(cmd == "INORDER"){
			cout << "Inorder" <<endl;
			Inorder(root);
			cout << endl;
		}
		else if(cmd == "POSTORDER"){
			cout << "Postorder" <<endl;
			Postorder(root);
			cout << endl;
		}
		else if(cmd == "PREORDER"){
			cout << "Preorder" <<endl;
			Preorder(root);
			cout << endl;
		}
		else if(cmd == "PRINT"){
			Print(root);
		}
	}

	return 0;
}

