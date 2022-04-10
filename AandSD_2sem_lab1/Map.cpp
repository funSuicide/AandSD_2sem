#include "Map.h"
using namespace std;

Map::Map() {
	root = nullptr;
}

Map::~Map() {
	ClearTree(root);
	root = nullptr;
}

void Map::ClearTree(MyTree* root) {
	while (root) {
		ClearTree(root->left);
		ClearTree(root->right);
		delete root;
	}
}

MyTree* Map::Insert(int key, string data, MyTree* tree) { //добавить балансировку
	if (tree == nullptr){
		tree = new MyTree(key, data);
	}
	else if (key > root->key){
		tree->right = Insert(key, data, tree->right);
	}
	else if (key < root->key)
	{
		tree->left = Insert(key, data, tree->left);
	}
	else throw "This element is already present...";
}

bool Map::Insert(int key, string data)
{
	root = Insert(key, data, root);
	return true;
}