#pragma once
#ifndef _BINTREE_H_
#define _BINTREE_H_
#include <iostream>
#include <string.h>

template<class T>
class BinTree {
private:
	struct Node {
		T* value;
		Node* left;
		Node* right;
	};
	Node* cur;
	Node* root;
	Node* pre;
	FILE* flPtr;
	char** data;
	int SizeMemON;
	int NumElemTree;
	int lenStr;
	int count;
	int countOut;
	bool condition;
	int GetLenStr();
	char* GetStr(char*);
	void* SearchNode(Node*, char*);
	void PrintRec(Node*);
	void AddNode(char*);
	void* removeRec(Node*, const char*);
	void removeTreeRec(Node*);
	int comparisonStr(const char*, const char*);
public:
	BinTree();
	void addItem();
	int GetCount();
	void openFile(const char*, const char*);
	void PrintAll();
	void addApp(const char*);
	void removeNode(const char*);
	void removeAll();
	~BinTree();
};

#endif