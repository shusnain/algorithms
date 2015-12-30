// ****************************************************************
// 						Interval Selection Problem

// Input: 		The number of intervals, the start and finish
//				times of each interval

// Output: 		 A subset of pairwise disjoint intervals of
//				 maximum size using the greedy technique

// Restrictions: Input doesn't have error 

// Complexity:   O(nlogn) where n is the number of intervals


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
// [2,7]
// [15,18]
// [22,31]
// [35,39]
// ****************************************************************

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
        return (finish < i.finish);
    }
};

void printIntervals(vector<Interval> in){
	int size = in.size();
	for(int i = 0; i < size; i++){
		cout << "[" << in[i].getStart() << "," << in[i].getFinish() << "]" << endl;
	}
}

vector<Interval> intervalSelection(vector<Interval> in){
	//sort with respect to finishing time in increasing order
	sort(in.begin(), in.end());

	int size = in.size();
	vector<Interval> ret;
	ret.push_back(in[0]);
	int prev = 0;

	for(int i = 1; i < size; i++){
		if(in[i].getStart() >= in[prev].getFinish()){
			ret.push_back(in[i]);
			prev = i;
		}
	}

	return ret;
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

	printIntervals(intervalSelection(in));
}