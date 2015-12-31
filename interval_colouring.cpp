// ********************************************************************************************************************************
// 						Interval Colouring Problem

// Input: 		The number of intervals, the start and finish
//				times of each interval

// Output: 		Assigns each interval a colour and two intervals
//				that recieve that same colour are disjoint. Outputs
//				the feasible greedy solution and the number of colours

// Restrictions: Input doesn't have error 

// Complexity:   O(n^2) where n is the number of intervals
//				 Can be improved through using a heap


// Sample Input: 
// 16
// 36 42
// 27 33
// 14 23
// 3 12
// 26 40
// 25 32
// 5 20
// 1 9
// 35 39
// 22 31
// 10 19
// 4 8
// 29 38
// 16 24
// 15 18
// 2 7

// Sample Output:
// [1,9] colour: 0
// [2,7] colour: 1
// [3,12] colour: 2
// [4,8] colour: 3
// [5,20] colour: 4
// [10,19] colour: 0
// [14,23] colour: 1
// [15,18] colour: 2
// [16,24] colour: 3
// [22,31] colour: 0
// [25,32] colour: 1
// [26,40] colour: 2
// [27,33] colour: 3
// [29,38] colour: 4
// [35,39] colour: 0
// [36,42] colour: 1
// Number of Colours: 4
// ********************************************************************************************************************************

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Interval{
	int start;
	int finish;

public:
	Interval(){}
	Interval(int s, int f): start(s), finish(f){}
	~Interval(){}
	
	int getStart(){
		return start;
	}

	int getFinish(){
		return finish;
	}

	bool operator < (const Interval& i) const
    {
        return (start < i.start);
    }
};

void printIntervals(vector<Interval> in){
	int size = in.size();
	for(int i = 0; i < size; i++){
		cout << "[" << in[i].getStart() << "," << in[i].getFinish() << "]" << endl;
	}
}

void printColouring(int* colouring, vector<Interval> in){
	sort(in.begin(), in.end());
	int size = in.size();
	int nc = 0;
	for(int i = 0; i < size; i++){
		cout << "[" << in[i].getStart() << "," << in[i].getFinish() << "] colour: " << colouring[i] <<endl;
		if(colouring[i] > nc) nc = colouring[i];
	}
	cout << "Number of Colours: " << nc << endl;
}
int* intervalColouring(vector<Interval> in);

int* intervalColouringWrapper(vector<Interval> in){
	//sort with respect to starting time in increasing order
	sort(in.begin(), in.end());
	
	return intervalColouring(in);
}

int* intervalColouring(vector<Interval> in){
	
	int size = in.size();
	int nc = 0;
	int *colour = new int[size];
	colour[0] = nc;
 	int finish[size];
 	finish[0] = in[0].getFinish();
 	
 	for(int i = 1; i < size; i++){
 		bool avail = false;
 		int c = 0;
 		while(c <= nc && !avail){
 			if(finish[c] <= in[i].getStart()){
 				colour[i] = c;
 				finish[c] = in[i].getFinish();
 				avail = true;
 			}else{
 				c++;
 			}
 		}
 		if(!avail){
 			nc++;
 			colour[i] = nc;
 			finish[nc] = in[i].getFinish();
 		}
 	}

 	return colour;
}

int main(){
	int num;
	cin >> num;
	vector<Interval> in;

	for(int i = 0; i < num; i++){
		int s, f;
		cin >> s;
		cin >> f;
		if (f >= s){
			in.push_back(Interval(s,f));
		}
	}

	printColouring(intervalColouringWrapper(in), in);
}