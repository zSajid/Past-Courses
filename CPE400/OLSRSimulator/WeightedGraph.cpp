#include "WeightedGraph.h"
#include <iterator>
#include "BSTree.cpp"


WeightedGraph::WeightedGraph( int maxNumber )
{
	if( maxNumber > 0 )
	{
		maxSize = maxNumber;
	}
	else
	{
		maxSize = MAX_GRAPH_SIZE;
	}
	
	size = 0;
	
	vertexList = new Vertex[ maxSize ];
	adjMatrix = new int[ maxSize * maxSize ];
	pathMatrix = new int[ maxSize * maxSize ];
	
	for( int i = 0; i < maxSize * maxSize; i++ )
	{
		adjMatrix[ i ] = INFINITE_EDGE_WT;
	}
	
	for( int i = 0; i < maxSize * maxSize; i++ )
	{
		pathMatrix[ i ] = INFINITE_EDGE_WT;
	}	
}

WeightedGraph::WeightedGraph( const WeightedGraph &source )
{
	maxSize = source.maxSize;
	size = source.size;
	
	vertexList = new Vertex[ maxSize ];
	adjMatrix = new int[ maxSize * maxSize ];
	pathMatrix = new int[ maxSize * maxSize ];
	
	for( int i = 0; i < size; i++ )
	{
		vertexList[ i ] = source.vertexList[ i ];
	}	
	
	for( int i = 0; i < maxSize * maxSize; i++ )
	{
		adjMatrix[ i ] = source.adjMatrix[ i ];
	}
	
	for( int i = 0; i < maxSize * maxSize; i++ )
	{
		pathMatrix[ i ] = source.pathMatrix[ i ];
	}			
}

WeightedGraph& WeightedGraph::operator=( const WeightedGraph &source )
{
	if( this == &source )
	{
		return *this;
	}
	else
	{
		delete[]vertexList;
		delete[]adjMatrix;
		delete[]pathMatrix;
		
		maxSize = source.maxSize;
		size = source.size;
		
		vertexList = new Vertex[ maxSize ];
		adjMatrix = new int[ maxSize * maxSize ];
		pathMatrix = new int[ maxSize * maxSize ];
		
		for( int i = 0; i < size; i++ )
		{
			vertexList[ i ] = source.vertexList[ i ];
		}	
		
		for( int i = 0; i < maxSize * maxSize; i++ )
		{
			adjMatrix[ i ] = source.adjMatrix[ i ];
		}
		
		for( int i = 0; i < maxSize * maxSize; i++ )
		{
			pathMatrix[ i ] = source.pathMatrix[ i ];
		}					
	}
	
	return *this;
}

WeightedGraph::~WeightedGraph()
{
	delete[]vertexList;
	delete[]adjMatrix;
	delete[]pathMatrix;
	vertexList = NULL;
	adjMatrix = NULL;
	pathMatrix = NULL;
}

void WeightedGraph::insertVertex( const Vertex& newVertex ) throw ( logic_error )
{
	if( isFull() )
	{
		throw logic_error( "GRAPH IS FULL!" );
	}
	
	Vertex temp;
	
	if( retrieveVertex( newVertex.getLabel(), temp ) )
	{
		for( int i = 0; i < size; i++ )
		{
			if( vertexList[ i ].getLabel() == newVertex.getLabel() )
			{
				vertexList[ i ] = newVertex;
				break;
			}
		}
	}	
	else
	{
		vertexList[ size ] = newVertex;
		size++;
		
		for( int j = 0; j < maxSize; j++ )
		{
			adjMatrix[ ( ( ( size - 1 ) * maxSize ) + j ) ] = INFINITE_EDGE_WT;
		}		
	}
}


void WeightedGraph::insertEdge( const string& v1, const string& v2, int wt ) throw ( logic_error )
{
	Vertex temp;
	
	if( !retrieveVertex( v1, temp ) || !retrieveVertex( v2, temp ) )
	{
		throw logic_error( "VERTEX NOT IN GRAPH!" );		
	}
	
	if( v1 != v2 )
	{
		int v1Location, v2Location;
		v1Location = getIndex( v1 );
		v2Location = getIndex( v2 );
		
		setEdge( v1Location, v2Location, wt );
		setEdge( v2Location, v1Location, wt );
		
		int t1, t2; // Location in the vertex list of the first vertex and the second one
		bool loc1 = false, loc2 = false;

		t1 = getIndex(v1);
		t2 = getIndex(v2);

	}		
}


bool WeightedGraph::retrieveVertex( const string& v, Vertex& vData ) const
{
	for( int i = 0; i < size; i++ )
	{
		if( vertexList[ i ].getLabel() == v )
		{
			vData = vertexList[ i ];
			return true;
		}
	}
	
	return false;
}


bool WeightedGraph::getEdgeWeight( const string& v1, const string& v2, int& wt ) const throw ( logic_error )
{
	Vertex temp;
	
	if( !retrieveVertex( v1, temp ) || !retrieveVertex( v2, temp ) )
	{
		throw logic_error( "VERTEX NOT IN GRAPH!" );
	}
	
	int v1Location, v2Location;
	
	v1Location = getIndex( v1 );
	v2Location = getIndex( v2 );
		
	wt = getEdge( v1Location, v2Location );
	
	if( wt == INFINITE_EDGE_WT )
	{
		return false;
	}
	
	return true;
}


void WeightedGraph::removeVertex( const string& v ) throw ( logic_error )
{
	Vertex temp;
	int vLocation = getIndex( v );
	
	if( !retrieveVertex( v, temp ) )
	{
		throw logic_error( "VERTEX NOT IN GRAPH!" );
	}
	
	for( int i = vLocation; i < size; i++ )
	{
		vertexList[ i ] = vertexList[ i + 1 ];
	}
	
	for( int i = vLocation; i < size; i++ )
	{
		 for( int j = 0; j < maxSize; j++ )
		 {
			 adjMatrix[ ( ( i * maxSize ) + j ) ] =
			 adjMatrix[ ( (  ( i + 1 ) * maxSize ) + j ) ];
		 }
	}
	
	for( int i = 0; i < size; i++ )
	{
		 for( int j = vLocation; j < maxSize; j++ )
		 {
			 adjMatrix[ ( ( i * maxSize ) + j ) ] =
			 adjMatrix[ ( ( i * maxSize ) + j + 1 ) ];
		 }
	}			
	
	size--;		
}


void WeightedGraph::removeEdge( const string& v1, const string& v2 ) throw ( logic_error )
{
	Vertex temp;
	
	if( !retrieveVertex( v1, temp ) || !retrieveVertex( v2, temp ) )
	{
		throw logic_error( "VERTEX NOT IN GRAPH!" );
	}
		
	int v1Location, v2Location;
	
	v1Location = getIndex( v1 );
	v2Location = getIndex( v2 );
		
	setEdge( v1Location, v2Location, INFINITE_EDGE_WT );
	setEdge( v2Location, v1Location, INFINITE_EDGE_WT );
}


void WeightedGraph::clear()
{
	for( int i = 0; i < maxSize * maxSize; i++ )
	{
		adjMatrix[ i ] = INFINITE_EDGE_WT;
	}
	
	size = 0;
}

// Check if size == 0, meaning no vertices
bool WeightedGraph::isEmpty() const
{
	return ( size == 0 );
}

// Check for max size
bool WeightedGraph::isFull() const
{
	return( size == maxSize );
}

// Get the index the vertex is on
int WeightedGraph::getIndex( const string &v ) const
{
	int index = -99999;
	
	for( int i = 0; i < size; i++ )
	{
		if( vertexList[ i ].getLabel() == v )
		{
			index = i;
			return index;
		}		
	}
	
	return index;
}

// Get the edge between said vertices
int WeightedGraph::getEdge( int row, int col ) const
{
	int edge;
	
	if( !isEmpty() )
	{
		edge = adjMatrix[ ( ( row * maxSize ) + col ) ];
	}
	
	return edge;
}


// Set the edge
void WeightedGraph::setEdge ( int row, int col, int wt)
{
	if( !isEmpty() )
	{
		adjMatrix[ ( ( row * maxSize ) + col ) ] = wt;
	}
}

// Loop through and find the shortest path, and after finding it, then set it to the array of shortest path
void WeightedGraph::showShortestPaths () 
{	
	for( int p = 0; p < ( maxSize * maxSize ); p++ )
		pathMatrix[ p ] = adjMatrix[ p ];
		
	for( int i = 0; i < size; i++ )
		pathMatrix[ ( i * maxSize ) + i ] = 0;
	
	for( int m = 0; m < size; ++m )
	{
		for( int j = 0; j < size; ++j )
		{
			for( int k = 0; k < size; ++k )
			{
				// check if there is a path between j and k through m
				if( ( pathMatrix[ ( j * maxSize ) + m ]  > 0 && 
						pathMatrix[ ( j * maxSize ) + m ] < INT_MAX ) && 
						( pathMatrix[ ( m * maxSize ) + k ] > 0 && 
							pathMatrix[ ( m * maxSize ) + k ] < INT_MAX )
							&& ( j != k && j != m && m != k ) )
				{
					// check to see if path is shorter than direct path
					if( ( pathMatrix[ ( j * maxSize ) + m ] + pathMatrix[ ( m * maxSize ) + k ] )
							< pathMatrix[ ( j * maxSize ) + k ] ) 
					{
						pathMatrix[ ( j * maxSize ) + k ] = 
							( pathMatrix[ ( j * maxSize ) + m ] +
							pathMatrix[ ( m * maxSize ) + k ] );
					}
				}
			}
		}
	}
		
	// Print it out if shortest path exist
	if ( size != 0 ) 
	{
       cout << endl << "Shortest Path matrix : " << endl << '\t';
       
       for ( int col = 0 ; col < size ; col++ )
           cout << col << '\t'; 
       cout << endl;    
       for ( int row = 0 ; row < size ; row++ )
       {
           cout << row << '\t';
           for ( int col = 0 ; col < size ; col++ )
           {
			   int wt = pathMatrix[ ( ( row * maxSize ) + col ) ];
               if ( wt == INFINITE_EDGE_WT )
                  cout << "- \t";
               else
                  cout << wt << '\t';
           }
           cout << endl;
       }
    }
    else
		cout << endl << "Path matrix : " << endl << endl;


	// Loop through and do somewhat the same except calculate total distance
	int totalWeight = 0;
	if(size != 0 )
	{
		cout << endl;
		for ( int row = 0 ; row < size ; row++ )
	       {
	       		totalWeight =0;
				cout << "Total cost for  " << vertexList[row].getLabel() <<  " to get through the whole network is ";

	           for ( int col = 0 ; col < size ; col++ )
	           {
				   int wt = pathMatrix[ ( ( row * maxSize ) + col ) ];
				   
				   
	               if ( wt != INFINITE_EDGE_WT )
		               totalWeight += wt;

	           }
	           cout << totalWeight << endl;
	       }
	}
}


bool WeightedGraph::hasProperColoring() const
{
	for( int i = 0; i < size; i++ )
	{
		for( int j = ( i + 1 ); j < size; j++ )
		{
			if( vertexList[ i ].getColor() == vertexList[ j ].getColor() )
			{
				return false;
			}
		}
	}
	
	return true;
}

bool WeightedGraph::areAllEven() const
{
	int currentCount= 0;
	
	for( int i = 0; i < size; i++ )
	{
		for( int j = 0; j < size; j++ )
		{
			if( getEdge( i, j ) > 0 && getEdge( i, j ) < INT_MAX )
			{
				currentCount++;
			}
		}
		
		if( currentCount % 2 == 1 )
		{
			return false;
		}
		else
		{
			currentCount = 0;
		}
	}
		
	return true;
}

void WeightedGraph:: showStructure () const
{
    if ( size == 0 ) {
       cout << "Empty graph" << endl;
    } else {
       cout << endl << "Router list : " << endl;
       for ( int row = 0 ; row < size ; row++ )
           cout << row << '\t' << vertexList[row].getLabel()
           << '\t'		<< endl;

       cout << endl << "Routing Table : " << endl << '\t';
       for ( int col = 0 ; col < size ; col++ )
           cout << col << '\t';
       cout << endl;
       for ( int row = 0 ; row < size ; row++ )
       {
           cout << row << '\t';
           for ( int col = 0 ; col < size ; col++ )
           {
               int wt = getEdge(row,col);
               if ( wt == INFINITE_EDGE_WT )
                  cout << "- \t";
               else
                  cout << wt << '\t';
           }
           cout << endl;
       }
    }
}

// Sends message from one vertex to others based on user choice
void WeightedGraph  :: sendTopologicalMessage(const string &v ) const
{
	// Variables
	vector< int> pushMessages; // Holds the integers for the vertices
	vector<string> pushedVertex;
	int index = getIndex(v); // Get index of the vertexList

	cout << endl << endl << "Optimized Link State Routing hello message topology, starting at node " << vertexList[index].getLabel() << endl;
	
	// Loop through the vertex vertex and check to see if any other vertexes are attached
	for(int col = 0; col < size; col++)
	{
		int wt = getEdge(index,col);

		// If there are then send a message from original vertex to other ones, and save it into a map by inserting it
		if(wt != INFINITE_EDGE_WT)
			{
				pushMessages.push_back(col); 
				cout << "Choosing multipoint relay: " << vertexList[col].getLabel() << " and Sending hello message from " << vertexList[index].getLabel() << " to " << vertexList[col].getLabel()  << endl;
				vertexList[col].vertexName.push_back(vertexList[index].getLabel());
				pushedVertex.push_back(vertexList[index].getLabel()); // This will add A or F or whatever it starts on

				cout << "Saving topology message into " << vertexList[index].getLabel() << " and " << vertexList[col].getLabel() << endl;
				vertexList[index].topo.insert(std:: pair<std:: string, int>(vertexList[col].getLabel(), wt));
				vertexList[col].topo.insert(std:: pair<std:: string, int>(vertexList[index].getLabel(), wt));
			}
	}

	// Loop through the intial vertex and then go through them and send messages
	for(int row = pushMessages.size(); row >0 ; row--)
		{
			for(int col = 0; col < size; col++)
				{
					int wt = getEdge(row,col);

					if(wt != INFINITE_EDGE_WT)
						{
							bool topoExist = false;

							pushMessages.pop_back();
							pushMessages.push_back(col); 

							for(int i = 0; i < pushedVertex.size(); i++)
								{
									if(vertexList[col].getLabel() == pushedVertex[i])
									{
										topoExist = true;
									}
								}

							if(!topoExist)
								{	
									cout << "sending hello message from " << vertexList[col].getLabel() << " to " << vertexList[row].getLabel()  << endl;
									vertexList[col].vertexName.push_back( vertexList[row].getLabel());
									pushedVertex.push_back(vertexList[row].getLabel()); // This will add A or F or whatever it starts on

									cout << "Saving topology message into " << vertexList[col].getLabel() <<  " and " << vertexList[row].getLabel() << endl;

								    vertexList[col].topo.insert(std:: pair<std:: string, int>(vertexList[row].getLabel(), wt));
									
								    vertexList[row].topo.insert(std:: pair<std:: string, int>(vertexList[col].getLabel(), wt));
								}
						}

				}
		}

	// Loop through all the vertices and all of the maps in the vertices and print the data
    cout << endl;
	cout << "Printing out toplogical map at each node" << endl;
	for(int i = 0; i < size; i++)
		{
			cout << "At node " << vertexList[i].getLabel() << " : ";
			for(std :: map<std :: string, int> :: iterator it = vertexList[i].topo.begin(); it != vertexList[i].topo.end() ; it++)
			{
			cout << " Node: " << it->first <<  "  distance: " << it->second << " ";
			}
			cout << endl;
		}	
}

// Count the number of hops
int WeightedGraph ::  hopCount(const string &v , const string &v2, int Count)
	{
	// Variables
	int index = getIndex(v);
	int index2 = getIndex(v2);
	int messagesPushedin = 0;
	int hop = Count ;

	// Loop through 
	for(int col = 0; col < size; col++)
	{
		hop =Count;
		int wt = getEdge(index,col);


				for(int i = 0; i < vectorName.size(); i++)
					{
						if(vertexList[col].getLabel() == vectorName[i])
						{
							wt = INFINITE_EDGE_WT;
						}
					}
		if(wt != INFINITE_EDGE_WT)
			{
				bool topoExist = false;

				hop+=1;


				if(!topoExist)
				{
					if(vertexList[col].getLabel() == v2)
					{

						//cout << "Found HOP when sending " << vertexList[index].getLabel() << " to " << vertexList[col].getLabel()<< " HOP COUNT " << hop << endl << endl;
						vertexList[col].key = hop;
						vertexList[col].attached = vertexList[index].getLabel(); 
						bst.insert(vertexList[col]);
						//numberOfCounts.push_back(hop);
						//return hop ;
					}

					else
					{
					vectorName.push_back(vertexList[index].getLabel()); // This will add A or F or whatever it starts on
					vectorName.push_back(vertexList[col].getLabel()); // This will add A or F or whatever it starts on
						

						hop = hopCount(vertexList[col].getLabel(), v2, hop);			
					}
				}
			}

	}
		return hop;
	}

void WeightedGraph ::  clearTopoGraph()
{

	for(int i = 0; i < size; i++)
		{
			vertexList[i].topo.clear();

			while(vertexList[i].vertexName.size() != 0)
			{
				vertexList[i].vertexName.pop_back();
			}
		}
}

void WeightedGraph :: clearVectorNames()
{

	for(int i = vectorName.size(); i > 0; i--)
	{
		vectorName.pop_back();
	}

}