// ********************************************************************************************************************************
// 			Floyd Warshall Shortest Path Algorithm

// Input: 		Takes a the number of vertices on the first line, the
// 	      		number of edges on the second line, a list of edges,
// 	      		and then a query.

// Output: 		 Outputs the shortest path and the length of the path

// Restrictions: There are at most 1000 vertices
// 			     The weight of each edge is in-between 1 and 100
// 			     Edges can be listed in any order
// 			     At least two vertices and one edge in input
// 			     There are no errors in input

// Complexity:   O(n^3) where n is the number of vertices

// Sample Input: 
// 6
// 7
// 1 2 3
// 1 4 7
// 2 5 2
// 3 5 6
// 3 6 6
// 4 2 3
// 5 4 1
// 1 4

// Sample Output:
// 1
// 2
// 5
// 4
// 6
// ********************************************************************************************************************************

#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <stack>

using namespace std;

#define INF 101

void printDoubleArray(int **w, int vertices, int offset){
	for(int i = 0; i < vertices; i++){
		for(int j = 0; j < vertices; j++){
			cout << w[i][j]+offset << " ";
		}
		cout << endl;
	}
}

void printStack(stack<int> s){
	while(!s.empty()){
		cout << s.top() + 1 << endl;
		s.pop();
	}
}

void getShortestPath(int **predecessor, int i, int j){
	stack<int> sequence;
	int k = j;
	while(k != i){
		k  = predecessor[i][k];
		sequence.push(k);
	}
	printStack(sequence);
}

int** FloydWarshall(int **w, int n, int b, int e){
	
	int **predecessor;
	predecessor = new int *[n];

	for(int i = 0; i < n; i++){
		predecessor[i] = new int[n];
		
		for(int j = 0; j < n; j++){
			if(i == j || w[i][j] == INF){
				predecessor[i][j] = -1;
			}else{
				predecessor[i][j] = i;
			}
		}
	}

	for(int m = 0; m < n; m++){
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				if(w[i][j] <= w[i][m] + w[m][j]){
					w[i][j] = w[i][j];
				}else{
					w[i][j] = w[i][m] + w[m][j];
					predecessor[i][j] = predecessor[m][j];
				}
			}
		}
	}

	getShortestPath(predecessor, b, e);
	cout << e + 1 << endl;
	cout << w[b][e] << endl;
	return w;
}

int main(){
	int vertices;
	int edges;

	cin >> vertices;

	int **w;
	w = new int *[vertices];

	for(int i = 0; i < vertices; i++){
		w[i] = new int[vertices];
		for(int j = 0; j < vertices; j++){
			if(i == j){
				w[i][j] = 0;
			}else{
				w[i][j] = INF;
			}
		}
	}

	cin >> edges;

	int value;
	int current = 0;

	string temp;
	string s;

	int c = 0;

	getline(cin, s);
	while(c < edges){
		getline(cin, s);
		int tail, head, weight;

		istringstream iss(s);
		iss >> temp; //get tail
		tail = atoi(temp.c_str());

		iss >> temp; //get head
		head = atoi(temp.c_str());

		iss >> temp; //get weight
		weight = atoi(temp.c_str());

		w[tail- 1][head - 1] = weight;
		c++;
	}

	int begin, end;

	cin >> begin;
	cin >> end;

	FloydWarshall(w, vertices, begin - 1, end - 1);
}
