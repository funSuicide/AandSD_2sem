#pragma once
#include <iostream>
#include <string>

using namespace std; 

struct MyTree {
	int key;
	string data;
	unsigned int height;
	MyTree* right; 
	MyTree* left; 
	MyTree(int key, string data) : key(key), data(data), right(nullptr), left(nullptr), height(1) {};
};

class Map {
private:
	MyTree* root;
	void ClearTree(MyTree* root);
	MyTree* Insert(int key, string data, MyTree* tree);
public:
	Map();
	~Map();
	bool Insert(int key, string data);

};