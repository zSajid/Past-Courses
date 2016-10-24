#include<iostream>
using namespace std;


class Stack_Linked{
public:
	Stack_Linked();
	~Stack_Linked();
	Stack_Linked(const Stack_Linked &other);
	void push(int value);
	int pop();
	void showStack();
	bool isEmpty();
	bool isFull();

private:
	class node{
	public:
		node (int dataItem, node *nextPtr);
		node *next;
		int data;		
	};
	node *top;
};



int main()
{
	// Variables
	Stack_Linked Item; // Creates object

	// Loop through and push object in
	for (int i = 0; i < 3; i++)
	{
		Item.push(i);
	}

	// Print stack prior to poping
	Item.showStack();

	// After pop, show stack
	Item.pop();
	Item.showStack();

	// Declare a new object by using a copy constructor and check its values using show stack function
	Stack_Linked New = Item;
	New.showStack();

	system("Pause");
	return 0;
}

Stack_Linked::Stack_Linked()
{
	// Variables

	// Intialize top to null 
	top = NULL;
}

Stack_Linked :: ~Stack_Linked()
{
	// Variables
	node *tmp = top;

	// Use a tmp pointer, go from top till null and delete all of the allocated memory
	while (tmp->next != NULL)
	{
		top = top->next;
		delete tmp;
		tmp = top;
	}
	tmp = top = NULL;
}

Stack_Linked::Stack_Linked(const Stack_Linked& other)
{
	// Variables
	node *tmp = other.top;
	node *tmp2 = NULL;

	if (other.top != NULL)
	{
		tmp2 = new node(tmp->data, NULL);
		top = tmp2;
		tmp = tmp->next;

		while (tmp != NULL)
		{
			tmp2->next = new node(tmp->data, NULL);
			tmp = tmp->next;
			tmp2 = tmp2->next;

		}
	}

	else
	{
		top = NULL;
	}

}

void Stack_Linked::push(int value)
{
	// Variables
	node *ptr = new node(value, NULL);
	node *tmp = NULL;

	// Check to see if top is null
	if (top == NULL)
	{
		top = ptr;
		ptr = NULL;
	}

	else{
		tmp = top;
		top = ptr;
		top->next = tmp;
		tmp = NULL;
		ptr = NULL;
	}
}

int Stack_Linked::pop()
{
	node *ptr = NULL;
	int storage = 0;

	if (top != NULL)
	{
		ptr = top;
		top = top->next;
	}

	else{
		cout << "Empty";
	}
	return ptr->data;
}

// This function was not written by me, it was received from my CS302 class at UNR to debug the stack and check the class stack.
void Stack_Linked::showStack()
{
	// Variables
	node *tmp = top;

	if (top == NULL)
	{
		cout << "Empty stack" << endl;
	}

	else
	{
		while (tmp->next != NULL)
		{
			if (tmp == top)
			{
				cout << "Top	" << "[" << tmp->data << "]" << "	";
			}

			else
			{
				cout << tmp->data << "	";
			}
			tmp = tmp->next;
		}
		if (tmp == top)
		{
			cout << "Top	" << "[" << tmp->data << "]" << "	";
		}

		else
		{
			cout << tmp->data << "	";
		}

		cout << "Bottom" << endl;
		tmp = NULL;
	}
}

bool Stack_Linked::isEmpty() 
{
	// Variables

	// Check to see if the top pointer is pointing to null
	if (top == NULL)
	{
		return 1;
	}

	return 0;
}

bool Stack_Linked::isFull()
{

	return false;
}

Stack_Linked::node::node(int dataItem, node *nextPtr)
{
	data = dataItem;
	next = nextPtr;

}