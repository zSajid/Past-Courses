// BSTree.cpp
/**
 * @BSTree.cpp
 * @Author Zeeshan Sajid
 * @version 5.0 final
 *
 * BSTree class implementation. 
 */
// Header Files
#include"BSTree.h"
#ifndef BSTREE_CPP
#define BSTREE_CPP
using namespace std;

// Class implementation   
	 /**
	 * Constructor for BST
	 * @param No parameters for this function is needed
	 * @pre Has a root that points to random information
	 * @post Sets root to null, to make sure there's no junk data 
	 * @return None
	 * @algorithm Manually sets the root to null
	 */ 
template < typename DataType, class KeyType > 
BSTree<DataType, KeyType> :: BSTree ()
	{
	 // Variables

	 // Set root to null
 	 root= NULL;
	}                        

	 /**
	 * Copy Constructor
	 * @param A reference to a data structure instantiation with data already in it
	 * @pre Root along with it's children nodes are pointing to information that was used for the function
	 * @post Clears the data within the function, and then copies the information from the other BST
	 * @return Returns the tree, with new and copied data implicity as a reference
	 * @algorithm Calls a copy constructor helper, in which that will copy the left leafs, and then copy 		 * the right hand side, and then the middle and keeps doing the same thing
	 */ 
template < typename DataType, class KeyType > 
BSTree<DataType, KeyType> ::  BSTree ( const BSTree<DataType,KeyType>& other )
	{
  	 // Variables

	 // Copy over the data through a recursive helper function
	 if(other == NULL)
		{
	 	 clear();
	 	 root = NULL;
		}
	 
	 else
		{
	 	 clear();
	 	 copyHelper(other>root, root);
		}
	}

	 /**
	 * Overloaded equals operator
	 * @param  A data structure that points to other and contains data to be copied
	 * @pre Root, that has information, whether it has important info is then destroyed
	 * @post Root along with its children has new information from the other referenced BST
	 * @return Returns it at as a reference
	 * @algorithm Calls copy constructor helper.
	 */ 
template < typename DataType, class KeyType > 
BSTree<DataType, KeyType>& BSTree<DataType,KeyType> ::  operator= ( const BSTree<DataType,KeyType>& other )
	{
	  // Variables

	 // Copy over the data through a recursive helper function
	 if(other == NULL)
		{
	 	 clear();
	 	 root = NULL;
		}
	 
	 else
		{
	 	 clear();
	 	 copyHelper(other>root, root);
		}
	}
    
	 /**
	 * Destructor
	 * @param None
	 * @pre Data that was pertinent prior to this call
	 * @post Removes all the nodes, after calling clear, and then sets the main root to null
	 * @return None
	 * @algorithm Calls clear, and that calls clearHelper
	 */ 
template < typename DataType, class KeyType > 
BSTree<DataType, KeyType> :: ~BSTree ()
	{
	 // Variable

	 // Utilize and call clear
	 clear();
	}

	 /**
	 * Insert
	 * @param The dataitem from the main program, that has a struct 
	 * @pre Material that was either random or null
	 * @post Then copies over the newDataItem into the slow necessary
	 * @return None
	 * @algorithm Calls insert algorithm, which checks for if it's less than or greater than, and at the 		 * appropriate place, it creates a new pointer node, and adds the info
	 */ 
template < typename DataType, class KeyType > 
void BSTree<DataType, KeyType> :: insert ( const DataType& newDataItem )
	{
	 // Variables

	 // Start the recrusive process of finding where to insert the dataItem
 	 insertHelper(root, newDataItem);	
	}  

	 /**
	 * Retrieve, function that checks to see if the data was found 
	 * @param searchKey, the thing to find  
	 * @param searchDataItem, the return of whatever we find
	 * @pre Same data information
	 * @post Same data information
	 * @return A boolean, stating if the data was found
	 * @algorithm Calls the retrieve helper, and then checks throughout using post-order for the var
	 */ 
template < typename DataType, class KeyType > 
bool BSTree<DataType, KeyType> :: retrieve ( const KeyType& searchKey,DataType& searchDataItem ) const
	{
	 // Variables

	 // Call retrieve helper
	 return retrieveHelper (searchKey, searchDataItem, root);
	}
            
	 /**
	 * Remove, goes through the information, and removes the specific int or whatever, and resets pointers
	 * @param  deleteKey, the key to delete from the file
	 * @pre The same information before this function changes it
	 * @post The same information minus the information if there was something found
	 * @return boolean, stating whether or not the deleteKey was found
	 * @algorithm It goes through in some kind of traversal, and finds deletes it, and sends back a bool
	 */ 
template < typename DataType, class KeyType >                                     
bool BSTree<DataType, KeyType> :: remove ( const KeyType& deleteKey )
	{
	 // Variables
	 DataType returnType;

	 if(root == NULL)
		{
	 	 return false;
		}

	 else 
		{
	 	 return removeHelper(deleteKey, root);
		}
	}           

	 /**
	 * writeKeys, just couts the keys
	 * @param None
	 * @pre Same information prior
	 * @post Same information prior
	 * @return Nothing
	 * @algorithm Goes from the left, then couts, and then the right, in order to show it in ascending values
	 */ 
template < typename DataType, class KeyType > 
void BSTree<DataType, KeyType> :: writeKeys () const
	{
	 // Variables

	 writeKeyHelper(root);	
	 cout << endl;
	}

	 /**
	 * clear function, to delete all of the nodes
	 * @param None 
	 * @pre information that became useless after using it
	 * @post A null root pointer
	 * @return Nothing
	 * @algorithm A clear Helper is called, which goes to the left, the right, and then deletes the node.
	 */ 
template < typename DataType, class KeyType > 
void BSTree<DataType, KeyType> :: clear ()
	{
	 // Variables

	 // Check if the root is null
	 if(root == NULL)
		{

		}

	 // Else, call clear helper
	 else
		{
	 	 clearHelper(root);
		}
	}                      

	 /**
	 * IsEmpty
	 * @param None
	 * @pre Random info
	 * @post Random info
	 * @return Bool, if a null is found as the root
	 * @algorithm Just checks with two statements if root  == null
	 */ 
template < typename DataType, class KeyType > 
bool BSTree<DataType, KeyType> ::  isEmpty () const
	{
	 // Variables

	 // Check if the root is null
	 if(root == NULL)
		{
	 	 return true;
		}

	 else
	 	{
	 	 return false; 
		}
	}

	 /**
	 * showStrucutre
	 * @param None
	 * @pre Important info
	 * @post Important info
	 * @return None
	 * @algorithm Just calls showHelper, and from there, it uses a level traversal to cout data
	 */ 
template < typename DataType, class KeyType > 
void BSTree<DataType, KeyType> :: showStructure () const
	{
	 // Variables

	 // Check if it's empty, and if so, then state a cout message
    	 if ( isEmpty() )
		{ 	  	
		  cout << "Empty tree" << endl;
    		}

	 else
	       {
 	          cout << endl;
       	 	  showHelper(root,1);
       	 	  cout << endl;
  	       }
	}

	 /**
	 * getHeight
	 * @param None
	 * @pre 
	 * @post 
	 * @return An integer, saying how big
	 * @algorithm 
	 */ 
template < typename DataType, class KeyType > 
int BSTree<DataType, KeyType> ::  getHeight () const
	{
	 // Variable

	 // Call the get height helper
	  return heightHelper(root);
	}

	 /**
	 * getCount, just counts the data in the binarytree
	 * @param None
	 * @pre information
	 * @post Important information
	 * @return Returns the amount of data found in the binary search
	 * @algorithm Calls clear helper with a reference int, that then counts the nodes and checks if it's 		 * null, and keeps adding, in which sends back the data, and that is then returned to the main.
	 */ 
template < typename DataType, class KeyType > 
int BSTree<DataType,KeyType> :: getCount () const
	{
	 // Variables
	 int count = 0;

	 // Check if the root is null
	 if(root == NULL)
		{
		 count = 0;
	 	 return count;		
		}

	 // Otherwise, use the getCount Helper and count up the amount of nodes that aren't null
	 else
		{
	 	 countHelper(root, count);
		 return count;
		}
	}

	 /**
	 * Write less than
	 * @param searchKey, which will cout all of the information less htan the search key
	 * @pre None
	 * @post None
	 * @return Nothing
	 * @algorithm checks, left and right, and if it's less tham it keeps going down that certain path, 		 * couting the information that's less than
	 */ 
template < typename DataType, class KeyType > 
void BSTree<DataType, KeyType> :: writeLessThan ( const KeyType& searchKey ) const
	{
	 // Variables

	 writeLessThanHelper(root, searchKey);

	}

	 /**
	 * Contructor for the leaf/ node
	 * @param nodeDataItem, the element/info to add within the node 
	 * @param leftPtr, where its children is pointing to
	 * @param rightPtr, where its children that's greater than points to
	 * @pre Random info?
	 * @post Information that's relevant
	 * @return Nothing
	 * @algorithm Just set the items to whatever was passed into from the parameter
	 */ 
template <typename DataType, class KeyType>
BSTree<DataType, KeyType> :: BSTreeNode :: BSTreeNode ( const DataType &nodeDataItem, BSTreeNode *leftPtr, BSTreeNode *rightPtr ) :dataItem(nodeDataItem),left(leftPtr),right(rightPtr)
	{
 	 // Variables
	 
	 // Set the nodeDataItem, to dataItem
	 dataItem = nodeDataItem;
	 left = leftPtr;
	 right = rightPtr;
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// These are helper functions in order
template <typename DataType, class KeyType>
 void BSTree<DataType, KeyType>  ::  showHelper ( BSTreeNode *p, int level ) const
	{  int j;   // Loop counter

     if ( p != 0 )
     {
        showHelper(p->right,level+1);         // Output right subtree
        for ( j = 0 ; j < level ; j++ )    // Tab over to level
            cout << "\t";
        cout << " " << p->dataItem.getKey();   // Output key
        cout << " " << p->dataItem.attached;
        if ( ( p->left != 0 ) &&           // Output "connector"
             ( p->right != 0 ) )
           cout << "<";
        else if ( p->right != 0 )
           cout << "/";
        else if ( p->left != 0 )
           cout << "\\";
        cout << endl;
        showHelper(p->left,level+1);          // Output left subtree
    }
	}

	 /**
	 * Insert Helper function for insert
	 * @param p is a pointer from the root, and is primarily used to do the indirect recursion
	 * @param newDataItem is the data Item to place within the BST
	 * @pre Information that could be random, or is pertinent
	 * @post Information from before is connected to other information now
	 * @return Nothing
	 * @algorithm Checks for null, if not null, then checks for less than or greater than, and places them 		 * in the appropriate place. Null means that the pointer, meaning root or not need to have a new node
	 */ 
template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>  :: insertHelper(BSTreeNode *&p, const DataType& newDataItem)
	{
	 // Variables

	 // Check if the root is null
	 if(p == NULL)
		{ 	
	  	 p = new BSTreeNode(newDataItem, NULL, NULL);
	
		}

	 else if( newDataItem.getKey () < p->dataItem.getKey ())
		{
		 insertHelper(p->left, newDataItem);
		}

	 else
		{
 	 	 insertHelper(p->right, newDataItem);
		}
	}

	 /**
	 * Helper function for retrieve
	 * @param searchKey, the thing we are searching for
	 * @param searchDataItem, the information we have to send back from the node we found
	 * @param p, a pointer for the indirect recursion process
	 * @pre Information that was gathered through insert or whatever program we used for it
	 * @post Same information, as this function is constant
	 * @return Nothing
	 * @algorithm Checks for null, if not found, then checks if the param value is equal to it, and if it, 		 * then sets the value, otherwise, it checks left and right.
	 */ 
template<typename DataType, class KeyType>
bool BSTree<DataType, KeyType> :: retrieveHelper ( const KeyType& searchKey, DataType& searchDataItem, BSTreeNode *p ) const
	{
	  bool result;   // Result returned

   	  if ( p == 0 )
   		 {
       	 	  result = false;
    	 	 }
 	 
	   else if ( searchKey < p->dataItem.getKey() )
    	 	 {
      	 	  result = retrieveHelper(searchKey,searchDataItem, p->left);
    		 }

 	   else if ( searchKey > p->dataItem.getKey() )
    		 {
       	 	  result = retrieveHelper(searchKey,searchDataItem, p->right);
    	 	 }

 	  else
    	 	{
 		  // Found the desired item
 	         searchDataItem = p->dataItem;
       	  	 result = true;
    	 	}
    	  return result;
	}

	 /**
	 * Helper for the clear function
	 * @param p is the pointer for the recursion, it's a reference since the BST has to change itself
	 * @pre Information that was used in the previous program
	 * @post Deletes all of the information
	 * @return Nothing
	 * @algorithm Checks if p is null to avoid seg faults, then otherwise, it goes through the left and 		 * the right and then deletes the node
	 */ 
template<typename DataType, class KeyType>
void BSTree<DataType, KeyType> :: clearHelper(BSTreeNode *&p)
	{
	 // Variables

	 // Go through and keep checking if the root one is a null
	 if(p != NULL)
		{
		 clearHelper(p->left);
		 clearHelper(p->right);
		 delete p;
	 	 p = NULL;
	 	}
	}

	 /**
	 * Remove function for helper
	 * @param deleteKey, the key to delete
	 * @param p, pointer for the reference in order to delete the node
	 * @pre Information that was important prior to this call
	 * @post See if the key is locatable, otherwise,it deletes it
	 * @return Nothing
	 * @algorithm Checks for null, and then checks for the left right hand side, and then checks the three 	 	 * cases in which it calls the removeHelperHelper function in order to do the last test case.
	 */ 
template<typename DataType, class KeyType>
bool BSTree<DataType, KeyType> :: removeHelper( const KeyType& deleteKey, BSTreeNode *& p)
	{	
	 // Variables
	 BSTreeNode *tmp;  // Temp pointer
	 bool result;                 // Result returned in terms of a boolean from each of the checks

  	 if ( p == NULL )
		{
	 	  // Search has failed to do/ find anything
	         result = false;                  
	 	}
	 
         else if ( deleteKey < p->dataItem.getKey() )
     		{
 		 // Search the less than the root area
 	         result = removeHelper(deleteKey,p->left);   
		}
	
	 else if ( deleteKey > p->dataItem.getKey() )
       		{
	 	 // If it's not in the left hand district, it must be in the right hand
		 result = removeHelper(deleteKey, p->right);   
		}

	 else
 	       {     
	 	// Pointer that takes the address for the thing to delete                                       
       		tmp = p;
	
		 // Check the first test case
	        if ( p->left == 0 )
       		  	{
		         p = p->right;                    
        	         delete tmp;
       		 	 }

	  	// The second test case
	        else if ( p->right == 0 )
       			 {
 		          p = p->left;                    
        		  delete tmp;
 		         }

	 	 // Otherwise, the third one with both children
	        else
		        {
	                 BSTreeNode* temp = p->left;

		  	 // Go to the right hand most side           
			 while( temp->right )
				 {
    			          temp = temp->right;
           			 }

           		  p->dataItem = temp->dataItem;        
           
			  // Redo this process but using the left and the key as the one to find
           		  removeHelper(  temp->dataItem.getKey(),p->left);
       			}
      		 	 result = true; // Set as true to show that the test cases worked
    		 }
	  return result; // Return if it was true or not
	}

 	 /**
	 * Helper for writing keys
	 * @param p, pointer to write the nodes
	 * @pre Information that was founded by the program
	 * @post Same information within the test
	 * @return Nothing
	 * @algorithm Checks for null, other wise, it uses a in-order function and prints it
	 */ 
template<typename DataType, class KeyType>
void BSTree<DataType, KeyType> :: writeKeyHelper(BSTreeNode *p) const
	{
	 // Variables

	 if(p != NULL)
		{
		 // Start the recursive process from the left hand side
		 writeKeyHelper(p->left);
	
		 cout << p->dataItem.getKey() << " ";
		 // Then go the right hand side if left hand side is finally done
 	 	 writeKeyHelper(p->right);
		}
	}

	 /**
	 * copy helper function
	 * @param main, pointer for the root in order to do recursion
	 * @param source, the BST source pointer in order to copy data over
	 * @pre Information that might be important, but it's replaced
	 * @post Copies over the source BST information
	 * @return Nothing
	 * @algorithm Checks if source is null at all, other wise, it goes through and copies it from the 	 	 * root, to left to the right
	 */ 
template <typename DataType, class KeyType>
void BSTree<DataType, KeyType> :: copyHelper(BSTreeNode *source, BSTreeNode *& main)
	{
	 // Variables

	 // If source doesn't equal null
	 if(source != NULL)
		{
	 	 main = new BSTreeNode(source->dataItem, NULL, NULL);
	 	 copyHelper(source->left, main->left);
	 	 copyHelper(source->right, main->right);
		}
	}

	 /**
	 * Helper for counter function
	 * @param p, pointer to do the recursion and find if numbers exist 
	 * @param counter, a refrence int that will return indirectly
	 * @pre Information that might be pertinent
	 * @post No change in information
	 * @return Nothing
	 * @algorithm Checks if it's null, other wise, it increases counter and then checks left and right
	 */ 
template<typename DataType, class KeyType>
void BSTree<DataType, KeyType> :: countHelper(BSTreeNode *p, int &counter) const
	{
	 // Variables

	 // While p doesn't equal null
	 if(p!= NULL)
		{
	 	 counter ++;
	  	 countHelper(p->left, counter);
	 	 countHelper(p->right, counter);
		}
	}

template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>:: writeLessThanHelper(BSTreeNode *p, const KeyType& searchKey) const
	{
	 // Variables

	 // Check 
	 if(p != NULL)
		{
	  	 if(searchKey >= (p->dataItem).getKey())
			{
		 	 writeLessThanHelper(p->right, searchKey);
		 	 
	 	  	 if(p->left != NULL)
				{
		 	 	 if(searchKey > ((p->left)->dataItem).getKey())
					{	
			 	 	 writeLessThanHelper(p->left, searchKey);
		 		 	
					}	
				}
	 	 	 cout << (p->dataItem).getKey();
			}
	 	 else if(searchKey <= (p->dataItem).getKey())
			{
	 	 	 cout << "This is going" << endl;
		 	 if((p->right) != NULL)
				{
	 	 		 writeLessThanHelper(p->right, searchKey);
				}
	 	 	 writeLessThanHelper(p->left, searchKey);
	 	 	 cout << (p->dataItem).getKey();
			}

		}
	}

	 /**
	 * Height helper function
	 * @param node, pointer used for recursion
	 * @pre Pertinent information
	 * @post No alterations in info
	 * @return Nothing
	 * @algorithm Checks for null, otherwise,it 1 to the max of left and right
	 */ 
template<typename DataType, class KeyType>
int BSTree<DataType, KeyType> :: heightHelper(BSTreeNode *node) const
	{
 	 // Variables
	 int right =0, left=0;

	 // Check if the node is null, meaning there's no left or right, and in return, return a 0, to represent that there's no level
	 if(node == NULL)
		{
			return 0;
		}

	 // Otherwise, go through the recursive process and get if the nodes are available and return the max of the left and the right hand side after end time checking it
	 else
		{
	  	 left= heightHelper(node->left);
		 right = heightHelper(node->right);
		 return 1+ max(left, right);		 
		}
	}
#endif
