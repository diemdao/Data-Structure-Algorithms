/***************************************************************************
 * Name: Diem Dao
 * Email: ddao@email.sc.edu
 * Date/Time of Completion: 10/27/19 9:44pm
 *
 * Functions: read in text file, exhaustive search, depth-first search, counting operations
 *
 * Input: read in a text file, first number of the set of integers will be the size (n).
 *        The rest of the integers use to populate the elements of the adjacency matrix.
 *        The next line of the input file will be a list of characters denoting the vertex names.
 *
 * Output: shows the adjacency matrix, order of nodes, number of operations
 *
 * Additional comments: I don't have time to make the vertex names (ex: S, G1, E), so the vertices names are numbers (index)
 *                      so, that might effect how the order of nodes output, but I hope that's ok since the logic looks "ok"
 *
 ***************************************************************************/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include <vector>
#include <list>

//Graph class for DFS
class Graph {
    int N;  // Numbers of vertices
    list<int> *adjList;  // adjacency using list
    void DFS_util(int v, bool visited[]);  // A function used by DFS

  public:
    Graph(int N){
      this->N = N;
      adjList = new list<int>[N];
    }

    //addEdge function
    void addEdge(int v, int a){
      adjList[v].push_back(a); // Add a to v’s list.
    }

    // DFS function
    void DFS();
};

void Graph::DFS_util(int v, bool visited[]){
  visited[v] = true; // Set current node as visited

  cout << v << " ";

  list<int>::iterator i;

  // For every node of the graph
  // If some node is adjacent to the current node
  // and it has not already been visited
  for(i = adjList[v].begin(); i != adjList[v].end(); ++i){
    if(!visited[*i]){
      DFS_util(*i, visited);
    }
  }
}

void Graph::DFS(){
  // initially none of the vertices are visited
  bool *visited = new bool[N];
  for (int i = 0; i < N; i++) {
      visited[i] = false;
  }

  // explore the vertices one by one by recursively calling DFS_util
  for (int i = 0; i < N; i++){
    if (visited[i] == false){
        DFS_util(i, visited);
    }
  }
}


int main (int argc, char **argv)
{

	ifstream myfile ("Maze2.txt");
	if (!myfile.is_open()) return -1;

  if (myfile.is_open())
  {
		string line;
		getline (myfile,line);
		// cout << "at line[0]: " << line << endl;  // assume line is the first line in the text file
		// cout << "type of line " << typeid(line).name() << endl;

		string firstLine = line;
		cout << firstLine << endl;
		int n = stoi(firstLine);  // to set the size of the array or vector the value have to be integer
		// cout << n << endl;

		// Create a vectors containing n x n
		vector<vector<int>> vec( n , vector<int> (n));

		for (int i = 0; i < n; i++) {
		    for (int j = 0; j < n; j++){
		        myfile >> vec[i][j];
		    }
		}

		//------------
		Graph G(n);
		//-----------

		// print out adjacency matrix
		for (int i = 0; i < n; i++) {
			// cout << "i[index]: " << i << " ";
		    for (int j = 0; j < n; j++){
		      cout <<vec[i][j] << " ";
					if(vec[i][j] == 1){  // if 2 vertices connect then it's equal one and consider as an edge
						G.addEdge(i,j);
					}
		    }
		   cout <<"\n";
		}

		// The next line of the input file will be a list of characters denoting the vertex names.
		string testing;
		while (myfile >> testing)
    {
        cout << testing << " ";
    }
		cout<< endl;

		cout << "--------------------------------------" << endl;
		cout << "Order of nodes: ";

    // Perform DFS
    G.DFS();
  	cout<< endl;

    cout << "Number of operations: " << n << endl; // number of operations should be equal to the numbers of nodes

  myfile.close();
	}
}
