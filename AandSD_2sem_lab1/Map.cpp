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

MyTree* Map::Insert(int key, string data, MyTree* tree) { 
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
	return BalanceTree(tree);
}

bool Map::Insert(int key, string data)
{
	root = Insert(key, data, root);
	return true;
}

const string& Map::FindElement(int key) const{
	MyTree* tmp = root;
	while (tmp != nullptr){
		if (key == tmp->key) return tmp->data;
		if (key < tmp->key){
			tmp = tmp->left;
		}
		else if (key > tmp->key){
			tmp = tmp->right;
		}
	}
	throw "This element was not found...";
}

unsigned Map::Height(MyTree* tree){
	if (tree) return tree->height;
	return 0;
}

int Map::BalanceReason(MyTree* tree){
	return Height(tree->right) - Height(tree->left);
}

void Map::FixHeight(MyTree* tree){
	unsigned height_right = Height(tree->right);
	unsigned height_left = Height(tree->left);
	tree->height = (height_left > height_right ? height_left : height_right) + 1;
}

MyTree* Map::RotateRight(MyTree* tree){
	MyTree* tree2 = tree->left;
	tree->left = tree2->right;
	tree2->right = tree;
	FixHeight(tree);
	FixHeight(tree2);
	return tree2;
}

MyTree* Map::RotateLeft(MyTree* tree){
	MyTree* tree2 = tree->right;
	tree->right = tree2->left;
	tree2->left = tree;
	FixHeight(tree2);
	FixHeight(tree);
	return tree2;
}

MyTree* Map::BalanceTree(MyTree* tree){
	FixHeight(tree);
	if (BalanceReason(tree) == 2)
	{
		if (BalanceReason(tree->right) < 0)
			tree->right = RotateRight(tree->right);
		return RotateLeft(tree);
	}
	if (BalanceReason(tree) == -2)
	{
		if (BalanceReason(tree->left) > 0)
			tree->left = RotateLeft(tree->left);
		return RotateRight(tree);
	}
	return tree;
}
