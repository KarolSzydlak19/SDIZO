#include<iostream>
#include <string>
using namespace std;
class BSTelem {
public:
	
	struct node {
		int data;
		node* parent;
		node* right;
		node* left;
	};
	node *root;
	BSTelem();
	~BSTelem();
	int loadFromFile(string FileName);

	bool IsValueInBST(int val);

	void addValue(int value);

	node* findPredecessor(node* node);

	node* findSuccessor(node* node);

	void deleteFromBST(node *&root, int value);

	void display(string sp, string sn, node *node);
	
	void rotateRight(node*& node);

	void rotateLeft(node*& node);

	void CreateLinear();

	void CreateBalancedTree();

	void DSW();

	void generateBST(int size);
	
	void deleteBST(node*& root);

	void deleteRoot(node*& root);

	void measureBST();

	void mesDisplay();
};
