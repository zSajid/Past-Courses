#include<stdio.h>
#include<iostream>

class Node
    {
     private:
     // Constructor
     Node(const int elem, Node *nextPtr);

     // Data Members
     int element;
     Node *next;

     friend class LinkedList;
    };

class LinkedList
    {
     public:

     // Constructor
     LinkedList();

     // Destructor
     ~LinkedList();

     // List Manipulation
     void insert(const int &newElement); // Insert after cursor
     void remove(); // Remove element
     void replace(const int &newElement); // Replace element
     void clear(); // Clear all elements in the LL

     // List status operations
     int empty() const; // List is empty
     int full() const; // List is full

     // List iteration operations
     int goToBeginning(); // Go to beginning
     int goToEnd();
     int goToNext();
     int goToPrior();
     int getCursor() const; // Return the element the cursor is pointing on

     // Show structure
     void printLL() const; // Prints the linked List and it's content

     private:
        // Data Members
     Node *head, // Pointer to the beginning of the list
           *cursor;  // Pointer to the cursor pointer

    };

int main()
    {
     LinkedList ptr;

     for(int i = 0; i < 10; i ++)
     {
         ptr.insert(i);
     }
     ptr.goToBeginning();
     ptr.goToNext();
     ptr.goToPrior();

     int ElementValue = ptr.getCursor();
     std :: cout << ElementValue << std::endl;

     ptr.replace(3);
     ptr.remove();
     ptr.goToEnd();
     ptr.remove();
     ptr.goToNext();
     ptr.remove();

     ptr.printLL();

     return 0;
    }


Node ::  Node(const int elem, Node *nextPtr)
    {
        // Variables

        element = elem;
        next = nextPtr;
    }

LinkedList :: LinkedList()
    {
        // Variables

        // Set both to null
        head = NULL;
        cursor = NULL;
    }

LinkedList :: ~LinkedList()
    {
        // Variables

        // Call clear
        clear ();
    }

     // List Manipulation
void LinkedList :: insert(const int &newElement)
    {
        // Variables

        // Check if the head is null
        if(head == NULL)
        {
            head = new Node(newElement, NULL);
            cursor = head;
        }

        else
        {
            cursor->next = new Node(newElement, NULL);
            cursor = cursor->next;
        }

    }

void LinkedList :: remove()
    {
        // Variables
        Node *ptr;

        // Check if does not equate to null
        if(cursor == head)
        {
            ptr = head;
            head = head->next;
            cursor = head;
            delete ptr;
        }

        else if(cursor ->next != NULL)
        {
            ptr = cursor->next;
            cursor->element = ptr->element;
            cursor->next = ptr->next;
        }

        else
        {
            ptr = cursor;

            Node *head2 = head;

            while(head2->next != cursor)
            {
                head2 = head2->next;

            }
            head2->next = NULL;
            cursor = head;
            delete ptr;
        }

    }

void LinkedList :: replace(const int &newElement)
     {
         // Variables

         cursor -> element = newElement;

     }


void LinkedList :: clear()
    {
     // Variables
     Node *ptr, *nextPtr;

     ptr = head;

     while(ptr != NULL)
     {
      nextPtr = ptr->next;
      delete ptr;
      ptr = nextPtr;
     }
     head = cursor = NULL;
    }

     // List status operations
int LinkedList :: empty() const
    {
        // Variables

        return(head == NULL);
    }

int LinkedList ::full() const
    {
        // Variables
        Node *ptr = new Node(3,0);

        // Return true, unless allocation failes
        if(ptr == NULL)
        {
            return true;
        }

        else
        {
            delete ptr;
            return false;
        }
    }

     // List iteration operations
int LinkedList :: goToBeginning()
    {
     // Variables

     if(head != NULL)
     {
         cursor = head;
         return 1;
     }

     else
     {
         return 0;
     }

    }

int LinkedList :: goToEnd()
    {
     // Variables

     // Loop until end
     if(head != NULL)
     {
        while(cursor->next != NULL)
        {
            cursor = cursor->next;
        }
        return true;
     }

     else{
        return false;
     }
    }
int LinkedList :: goToNext()
    {
     // Variables

     if(cursor->next != NULL)
     {
         cursor = cursor->next;
         return 1;
     }

     else {
        return 0;
     }

    }

int LinkedList ::goToPrior()
    {
     // Variables
     Node *ptr;

     if(cursor != head)
     {
        ptr = head;
        while(ptr->next != cursor)
        {
            ptr = ptr->next;
        }
        cursor = ptr;
        return 1;
     }

     else {
        return 0;
     }

    }

int LinkedList :: getCursor() const
    {
     // Variables

     if(head != NULL)
     {
         return cursor->element;
     }

     else{
        return NULL;
     }
    }

void LinkedList :: printLL() const
    {
     // Variables

     // Check if head  = null
     if(head == NULL)
     {
         std :: cout << "empty List " << std :: endl;
     }

     else
     {
         Node *ptr = head;

         while(ptr != NULL)
         {
             if(ptr == cursor )
             {
                 std :: cout << "[" << ptr->element << "]";
             }
             else{
                 std :: cout << ptr->element << " ";
             }
             std :: cout << std :: endl;
             ptr = ptr->next;
         }
     }
    }
