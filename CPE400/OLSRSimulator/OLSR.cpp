#include <utility>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <string>
#include <fstream>
#include "WeightedGraph.cpp"
#include <stdlib.h>
#include <time.h>    
using namespace std;

// Reads in data from a file which will tell where each node is and the destination is, yet no flooding is known
bool readInNodes(WeightedGraph *&, string nameofFile);
void displayOptions();
void createNetwork(WeightedGraph *&);
void clearScreen(int o);

// Main program
int main(int argv, char *arc[])
{
  // Input integer from the user, hopCount the number of hops needed from node x to node y
  int input, hopCount= -1; 
  WeightedGraph *network; // Create a network for which it will gather the list of stuff from a file
  srand(time(NULL)); // Time seeding, used for random generation of network
  string nodeName, nodeName2; // Input names for the nodes from the user
  WeightedGraph :: Vertex a; // Temporary Vertex to store name
  WeightedGraph :: Vertex b;

  // Clear the screen
  clearScreen(20);


  // Tell the user data is being read in
  cout << "READING IN NETWORK DATA FROM TXT FILE" << endl;

  // Read the information of the network from the file
  bool fileStatus = readInNodes(network,"node.txt");
  if(!fileStatus)
    {
      cerr << "File from the user was bad, exiting simulation" << endl;
      return 0;
    }
  
  // Do this until the user wants to quit
  do{
      // Show him the options
      displayOptions();

      // Get an input from the user
      cin >> input;

      // Clear the screen for new information
      clearScreen(40);

      // Check to see if any of those inputs match
      switch(input)
      	{  		
      		case 1:
            // Delete the network, set to null and start a new network
            delete network;
            network = NULL;
            createNetwork(network);
      			break;

          case 2:
            // Show the shortest path by using the routing matrix
            network->showShortestPaths ();
            break;

      		case 3:
            // Ask for the name of the node to start the flooding
            cout << "Enter starting node/router name for flooding"<< endl; 
            cin >> nodeName;

            // Check to see if the node exist, if so, clear the topological map created in each vertex and redo it
            if(network->retrieveVertex(nodeName, a))
            {
              network->clearTopoGraph();
              network->sendTopologicalMessage(nodeName);
            }

            else
              cout << "Node/Router does not exist in this network" << endl;
          	break;

          case 4:
            cout << "Showing graph structure: " << endl; 
            // Show the structure of how the network looks using arrays
            network->showStructure();
            break;
          
          case 5:
            // Check to see if it is not full
            if(!network->isEmpty())
              {
                cout << "Name a router that you want to remove in this network ";

                // Get input for the node to be removed
                cin >> nodeName;
                cout << endl;

                // Check to see if node exist
                while(!network->retrieveVertex(nodeName, a))
                  {
                  cout << "Please enter a router that is in this network ";
                  cin >> nodeName;
                  cout << endl;
                  }

                network->removeVertex(nodeName);
              }
            // Otherwise full
            else
              {
               cout << "Graph is empty" << endl; 
              }
            break;

          case 6:
            if(!network->isFull())
              {
                // Insert a new node, if the node does not already exist it will not show up on the graph
                cout << "Enter a name for a new node"<< endl; 
                cin >> nodeName;
                a.setLabel(nodeName);

                
                cout <<"Enter a prexisting node to connect the new node and the weight will be 20" << endl;
                cin >> nodeName2;

                while(!network->retrieveVertex(nodeName2, b))
                  {

                    cout <<"Enter a prexisting node to connect the new node and the weight will be 20" << endl;
                    cin >> nodeName2;

                  }

                b.setLabel(nodeName);

                network->insertVertex(a);
                network->insertEdge(nodeName, nodeName2, 20);
              }
            else
              {
                cout << "Graph is full " << endl; 
              }
            break;

          case 7:
            // Do the hop count for Optimized Link State routing
            cout << "Enter the name of the destination router for the hop count"<< endl; 
            cin >> nodeName;

            cout << "Enter the name of the source router for the hop count"<< endl; 
            cin >> nodeName2;

            // Clear the names of vectors that have been recorded
            network-> clearVectorNames();

            if(network->retrieveVertex(nodeName, a) && network->retrieveVertex(nodeName2, a))
            {
              hopCount = network-> hopCount(nodeName , nodeName2,0);
            }
      
            else
            {
              cout << "Node/router does not exist in this network" << endl;
            }

            cout << endl;

            if(hopCount != -1 && network->retrieveVertex(nodeName, a) && network->retrieveVertex(nodeName2, a))
              {
                cout << "This is the list of hop counts it take going from one node to another " << endl;
              }

              // Show the bst structure and clear it
              network->bst.showStructure();
              network->bst.clear();
            break;

          case 8:
            exit(0); // Exit the program
            break;

            // Default if no ints are met
          default:
            cout << "Make a valid input " << endl;
      	}
    } while(input != 8);


  // Deallocate the graph
  delete network ;
  network = NULL; // Set to Null;

  return 0;
}

/*
  Function that reads in information from a .txt file,
  It allocates vertexes to the network WeightedGraph object and assigns it edges
*/
bool readInNodes(WeightedGraph *& network, string nameofFile)
{
  // Instantiate a read in variable while opening the file
  ifstream fin(nameofFile.c_str());
  int size = 0;

  // Get the first letter to see how big the network is
  if(fin)
    {
      fin >> size;
      network = new WeightedGraph(40);

      // Create two vertexes that will be pushed into the Weighted Graph
      WeightedGraph :: Vertex node1;
      WeightedGraph :: Vertex node2;

      // Create string temps
      string name1, name2;

      // Int temp
      int weight;
      
      // Loop through until eof
      while(!fin.eof())
        {
          // Get the name of v1 and v2 and weight between those two
          fin >>  name1 >> name2 >> weight;

          // Set the name for both of them
          node1.setLabel(name1);
          node2.setLabel(name2);

          // Insert them
          network->insertVertex(node1);
          network->insertVertex(node2);

          // Insert the edge between the two vertices
          network->insertEdge(name1, name2, weight);
        }
    }

  // If file is bad then exit the program
  else{
    return false;
  }


  return true;
}

void displayOptions()
{
  // Print out the title
  cout << "               ________    _       ______   __________" << endl;
  cout << "               ||  __  | || |     ||        ||  ___  |" << endl;
  cout << "               || |  | | || |     ||        || |___| |" << endl;
  cout << "               || |  | | || |     ||_____   ||   __  |" << endl;
  cout << "               || |  | | || |           ||  || |  | |  " << endl;
  cout << "               || |__| | || |__         ||  || |  | |  " << endl;  
  cout << "               ||______| ||____|  ______||  ||_|  |_|  " << endl;
  cout << "               ===================================  " << endl;
  cout << "                       Author: Zeeshan Sajid" << endl;

  cout << " Options: " << endl;
  cout << "Press 1 to randomly generate a new network with nodes" << endl;
  cout << "Press 2 to calculate shortest path " << endl;
  cout << "Press 3 to show the flooding process, and shows topological map at each vertex" << endl;
  cout << "Press 4 to show the structure of the network" << endl;
  cout << "Press 5 to remove node from the network" << endl;
  cout << "Press 6 to add a node and add edge between another prexisting node and newly created node" << endl;
  cout << "Press 7 to do hop count which is part of OLSR" << endl;
  cout << "Press 8 to quit the simulation" << endl;
}

/*
  Creates a randomely generated network
  Essentially loops through, creates a string name of one letter size, assigns it to a vertices, and then assigns and edge in between said vertices
*/
void createNetwork(WeightedGraph *& network)
{
  // Init
  network = new WeightedGraph(40);

  // Temp nodes to be pushed in
  WeightedGraph :: Vertex node1;
  WeightedGraph :: Vertex node2;


  // Loop through 10 vertices or less depending on duplicates
  for(int i = 0; i < 10; i++)
      {
        int num = rand() % 6; // Choose a number between 0 and 26 on the alpha
       
        // Type cast it to a character
        char letter =static_cast<char>('A' + num);

        int num2 = rand() %6;

        while(num2 == num)
        {
          num2 = rand() % 6;
        }

        char letter2 = static_cast< char>('A' + num2);

        int weight = rand() % 20 + 3;

        string name;
        string name2;

        name += letter;
        name2 += letter2;

        // Place all of those things into the network after assigning them
        node1.setLabel(name);
        node2.setLabel(name2);
        network->insertVertex(node1);
        network->insertVertex(node2);
        network->insertEdge(name, name2, weight);
      }
}

/*
  Function prints out a number of print end lines based on the number the user wants
*/
void clearScreen(int o)
{
  for(int i = 0; i < o; i++)
  {
    cout << '\n';
  }
}