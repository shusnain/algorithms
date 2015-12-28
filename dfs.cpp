// ****************************************************************
// 					Depth First Search

// Input: The number of vertices on the first line, an adjacency
// 	   list thereafter

// Output: A depth first search where each line specifies a root
// 		vertex or an edge

// Restrictions: Vertices in input listed in ascending order
// 			  No Error in Input

// Sample Input:
// 6
// 1 : 2 4
// 2 : 5
// 3 : 5 6
// 4 : 2
// 5 : 4
// 6 : 6

// Sample Output:
// 1 root
// 1 2
// 2 5
// 5 4
// 3 root
// 3 6
// ****************************************************************

#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>

using namespace std;


class vertex{
	public:
		int value;
		vertex *next;
		vertex(int value): value(value) {}
		vertex(int value, vertex *next): value(value), next(next) {}
};

void DFSvisit(vertex *g[], string *colour, int *d, int *f, int n, int t, int v);

void DFS(vertex *g[], string *colour, int *d, int *f, int n){
	for(int i = 0; i < n; i++){
		colour[i] = "white";
	}
	int t = 0;
	
	for(int i = 0; i < n; i++){
		if(colour[i] == "white"){
			cout << i+1 << " root" << endl;
			DFSvisit(g, colour, d, f, n, t, i);
		}
	}
}

void DFSvisit(vertex *g[], string *colour, int *d, int *f, int n, int t, int v){
	colour[v] = "gray";
	t++;
	d[v] = t;
	vertex *ver = g[v]->next;
	while(ver != NULL){
		if(colour[ver->value - 1] == "white"){
			cout << v+1 << " " << ver->value << endl;
			DFSvisit(g, colour, d, f, n, t, ver->value - 1);
		}
		ver = ver->next;
	}
	colour[v] = "black";
	t++;
	f[v] = t;
}

int main(){
	int numberOfVertices;
	cin >> numberOfVertices;

	vertex *graph[numberOfVertices];
	string colour[numberOfVertices];
	int d[numberOfVertices];
	int f[numberOfVertices];

	int value;
	int current = 0;

	string temp;
	string s;

	
	while(getline(cin, s)){
		istringstream iss(s);
		iss >> temp; //get leftside

		current = atoi(temp.c_str());
		
		iss >> temp; //get :
		vertex *v = new vertex(current);	
		graph[current - 1] = v;

		vertex *ver = graph[current - 1];

		while(iss >> temp){
			value = atoi(temp.c_str());
			vertex *w = new vertex(value);
			ver->next = w;
			ver = ver->next;
			current = value;
		}
	}

	DFS(graph, colour, d, f, numberOfVertices);

}

