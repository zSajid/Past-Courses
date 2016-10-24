// Small Linked_Queue dt with general functionalities of Enqueueing and Dequeueing

#include<iostream>
using namespace std;

class Linked_Queue{
	public:
		Linked_Queue(); // Constructor
		~Linked_Queue(); // Destructor
		void Enqueue(int item);
		int Dequeue();
		bool isEmpty() const;
		void print() const;

	private:
		struct Node
			{
				Node(int data, Node *nxt);
				int data;
				Node *next;
			};
		Node *front;
		Node *rear;
	};


int main()
	{
	Linked_Queue Q1;

	// Loop through and add the values of i to the queue
	for(int i = 0; i < 10; i++)
		{
		 Q1.Enqueue(i);
		}
	
	// Print out all of the values
	Q1.print();

	// Dequue from the front of the stack
	int val = Q1.Dequeue();

	// State what was Dequeued
	cout << "Dequeued " <<val << " from Queue" << endl;
	Q1.print();
	return 0;
	}

Linked_Queue :: Linked_Queue(){
	//Set both variables to NULL until allocated
	front = rear = NULL;
}


Linked_Queue :: ~Linked_Queue(){
	// Variables
	Node *tmp = front;

	while(tmp != NULL)
		{
		front = front->next;
		delete tmp;
		tmp = front;
		}
}


void Linked_Queue :: Enqueue(int item){
	// Variables

	if(isEmpty())
		{
		 // Allocate node for the front if null
		 front = new Node(item, NULL);


		 // Set the rear to the front since there's only one value
		 rear = front;
		}

	else
		{
		 rear->next = new Node(item, NULL);
		 rear = rear->next;
		}
}


int Linked_Queue :: Dequeue(){
	if(isEmpty())
		{
		 cout << "I AM EMPTY";
		 return 0;
		}

	else
		{	
		 Node *tmp = front;

	 	 front =front->next;
		
		 int retVal = tmp->data;
		 delete tmp;
		 cout << retVal;
		 return retVal;
		}
}

bool Linked_Queue :: isEmpty() const{
	// Check to see if front == null
	return(front == NULL);
}


void Linked_Queue :: print() const{
	// Variables
	Node *tmp = front;
	if(isEmpty())
		{
		 cout << "Nothing to print out";
		}
	
	else{
		while(tmp != NULL)
			{
			 if(tmp == front)
				{	
				 cout << "[" << tmp->data << "]" << " ";

				}

			 else
				{
				 cout << tmp->data << " ";
				}
			 tmp = tmp->next;
			}
		}
	cout << endl;
}

Linked_Queue :: Node :: Node(int info, Node *nxt){
	data = info;
	next = nxt;

}

