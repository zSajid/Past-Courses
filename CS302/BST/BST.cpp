#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;

struct Node{
		Node(int data, Node *l, Node *r);
		Node *left;
		Node *right;
		int info;
	};

class BST{
	public:
		BST();
		~BST();
		BST(const BST& originalBST);
		void operator=(BST& originalBST);
		void MakeEmpty();
		bool isEmpty() const;
		bool isFull() const;
		int length();
		void RetrieveItem(int& item, bool& found) const;
		void InsertItem(int item);
		void DeleteItem(int item);
		void print() const;	

	private:
		void insertHelper(Node *& treeNode, int item);
		void deleteHelper(Node *& treeNode, int item);
		void MakeEmptyHelper(Node *& treeNode);
		void printHelper(Node * treeNode) const;
		Node *root;
	};

int main()
	{
	 BST firstTree;
	
	srand(time(NULL));

	firstTree.InsertItem(10);
	firstTree. InsertItem(1);
	firstTree. InsertItem(30);
	firstTree. InsertItem(14);
	firstTree. InsertItem(40);
	firstTree. InsertItem(3);

	firstTree.print();

	 return 0;
	}

BST :: BST(){
	// Set root to null until data comes in
	root = NULL; 
}
BST ::	~BST(){

}
BST :: BST(const BST& originalBST){

}

void BST ::  operator=(BST& originalBST){
	
}

void BST :: MakeEmpty(){

}

bool BST :: isEmpty() const{

}

bool BST :: isFull() const{

}

int BST :: length(){

}

void BST :: RetrieveItem(int& item, bool& found) const{

}

void BST :: InsertItem(int item){
	insertHelper(root, item);
}

void BST :: DeleteItem(int item){

}

void BST :: print() const{
	printHelper(root);
}


Node :: Node(int data, Node *l, Node *r)
	{
		info =data;
		left = l;
		right = r;
	}

void BST :: insertHelper(Node *& treeNode, int item)
	{
		if(treeNode == NULL)
			{
				treeNode = new Node(item, NULL, NULL);
			}

		else if(item < (*treeNode).info)
			{
				insertHelper(treeNode->left, item);
			}

		else
			{	
				insertHelper(treeNode->right, item);
			} 

	}

void BST :: deleteHelper(Node *& treeNode, int item){

	}

void BST :: MakeEmptyHelper(Node *& treeNode){

	}

void BST :: printHelper(Node * treeNode)  const{
		if(treeNode != NULL)
			{
				printHelper(treeNode ->left);
				cout << treeNode -> info << " ";
				printHelper(treeNode ->right);
			}
	}

