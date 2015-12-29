// ****************************************************************
// 						Non-dominated Points Problem

// Point (a,b) dominates point (c,d) if a >= c and b >= d

// Input: 		Takes in the number of points and a list of
//				points on a cartesian plane

// Output: 		 The points that are not dominated by any other
//				 point

// Restrictions: Input doesn't have error
//				 Amount must be represented as an integer (pennies)

// Complexity:   O(nlogn) where n is the number of points

// Sample Input: 
// 5
// 1 5
// 2 4
// 3 3
// 4 1
// 5 0

// Sample Output:
// (1,5)
// (2,4)
// (3,3)
// (4,1)
// (5,0)
// ****************************************************************

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Point{
	int x;
	int y;

public:

	Point(){}
	Point(int x, int y) : x(x), y(y) {}
	Point(const Point &p){
		x = p.x;
		y = p.y;
	}
	~Point(){}

	int getX(){
		return x;
	}

	int getY(){
		return y;
	}

	void setX(int v){
		x = v;
	}

	void setY(int v){
		y = v;
	}

	bool operator < (const Point& p) const
    {
        return (x < p.x);
    }
	void printPoint(){
		cout << "("<< x << "," << y << ")" << endl;
	}
};

void printPoints(vector<Point> p){
	for(vector<Point>::iterator it = p.begin(); it != p.end(); ++it){
		it->printPoint();
	}
}

vector<Point> copyPoints(vector<Point> a, vector<Point> b, int offset, int size){
	for(int i = 0; i < size; i++){
		a.push_back(b[i+offset]);
	}
}

vector<Point> nondominatedPoints(vector<Point> S, int size){

	if(S.size() == 1){
		vector<Point> r; 
		r.push_back(S[0]);
		return r;
	}

	int l = size/2;
	int m = size - l;

	vector<Point> Q;
	vector<Point> R;

	//divide the set into halves
	for(int i = 0; i < l; i++){
		Q.push_back(S[i]);
	}

	for(int i = 0; i < m; i++){
		R.push_back(S[i+l]);
	}
	
	Q = nondominatedPoints(Q, l);
	R = nondominatedPoints(R, m);

	//size of the vectors have possibly changed
	l = Q.size();
	m = R.size();
	
	int i = 0;
	while(i < l && Q[i].getY() > R[0].getY()){
		i++;
	}
	
	vector<Point> ret;

	//merge
	for(int j = 0; j < i; j++){
		ret.push_back(Q[j]);
	}
	
	for(int j = 0; j < m; j++){
		ret.push_back(R[j]);

	}

	return ret;
}

int main(){
	int points;
	cin >> points;
	vector<Point> p;

	for(int i = 0; i < points; i++){
		int x, y;
		cin >> x;
		cin >> y;
		p.push_back(Point(x,y));
	}

	//sort the set with respect to x in increasing order
	sort(p.begin(), p.end());

	printPoints(nondominatedPoints(p, points));
}