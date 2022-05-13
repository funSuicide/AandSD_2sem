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
	if (root) {
		ClearTree(root->left);
		ClearTree(root->right);
		delete root;
	}
}

MyTree* Map::Insert(int key, string data, MyTree* tree) { 
	if (tree == nullptr){
		tree = new MyTree(key, data);
	}
	else if (key < tree->key)
	{
		tree->left = Insert(key, data, tree->left);
	}
	else if (key > tree->key) {
		tree->right = Insert(key, data, tree->right);
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
	return Height(tree->left) - Height(tree->right);
}

void Map::FixHeight(MyTree* tree){
	unsigned height_left = Height(tree->left);
	unsigned height_right = Height(tree->right);
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
	FixHeight(tree);
	FixHeight(tree2);
	return tree2;
}

MyTree* Map::BalanceTree(MyTree* tree){
	FixHeight(tree);
	if (BalanceReason(tree) == -2)
	{
		if (BalanceReason(tree->right) == 1)
			tree->right = RotateLeft(tree->right);
		return RotateLeft(tree);
	}
	if (BalanceReason(tree) == 2)
	{
		if (BalanceReason(tree->left) == -1)
			tree->left = RotateRight(tree->left);
		return RotateRight(tree);
	}
	return tree;
}

void Map::PrintTree(MyTree* tree, int stl) const{
	if (tree){
		PrintTree(tree->right, stl + 1);
		for (int i = 0; i < stl; i++) std::cout << "		 ";
		std::cout << tree->key << std::endl;
		PrintTree(tree->left, stl + 1);
	}
}

void Map::Print() const{
	if (!root){
		std::cout << "The container is empty..." << std::endl;
	}
	else PrintTree(root, 0);
}

MyTree* Map::FindMin(MyTree* tree){
	return tree->left ? FindMin(tree->left) : tree;
}

MyTree* Map::EraseMin(MyTree* tree){
	if (tree->left == nullptr)
		return tree->right;
	tree->left = EraseMin(tree->left);
	return BalanceTree(tree);
}

MyTree* Map::EraseElement(MyTree* tree, int key){
	if (!tree) return nullptr;
	if (key < tree->key){
		tree->left = EraseElement(tree->left, key);
	}
	else if (key > tree->key){
		tree->right = EraseElement(tree->right, key);
	}
	else{
		MyTree* tmp_left = tree->left;
		MyTree* tmp_right = tree->right;
		delete tree;
		if (!tmp_right) return tmp_left;
		if (!tmp_left) return tmp_right;
		MyTree* min = FindMin(tmp_right);
		min->right = EraseMin(tmp_right);
		min->left = tmp_left;
		return BalanceTree(min);
	}
	return BalanceTree(tree);
}

bool Map::Erase(int key){
	root = EraseElement(root, key);
	return true;
}