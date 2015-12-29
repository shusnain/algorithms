// ****************************************************************
// 						Coin Changing Problem

// Input: 		Takes an amount of money, in pennies, that is
//				denominated in Canadian currency. Also takes in
//				whether the user wants to find the solution
//				through the greedy or dynamic method.

// Output: 		 The lowest number of coins needed to output
//				 the inputted amount with the chosen algorithm.

// Restrictions: Input doesn't have error
//				 Amount must be represented as an integer (pennies)

// Complexity:   
//	   Greedy:  O(nlogn) where n is the size of the denominations
//    Dynamic:  O(n*m) where n is the size of the denominations and
//				m is the size of the input

// Sample Input: 
// 1453
// g

// Sample Output:
// 10000: 0
// 5000: 0
// 2000: 0
// 1000: 1
// 500: 0
// 200: 2
// 100: 0
// 10: 5
// 5: 0
// 1: 3
// Number of coins: 11
// ****************************************************************

#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>

using namespace std;

void printArray(int *arr, int size){
	for(int i = 0; i < size; i++){
		cout << arr[i] << " ";
	}
	cout << endl;
}

void printCount(int *d, int* A, int size, int N){
	for(int i = 0; i < size; i++){
		cout << d[i] << ": " << A[i] << endl;
	}
	cout << "Number of coins: " << N << endl;
}

int* merge(int* arr1, int size1, int* arr2, int size2, int* arr, int size){
	int j = 0; int k = 0;
	for(int i = 0; i < size; i++){
		if(j == size1){
			arr[i] = arr2[k++];
		}else if(k == size2){
			arr[i] = arr1[j++];
		}else if(arr1[j] > arr2[k]){
			arr[i] = arr1[j++];
		}else{
			arr[i] = arr2[k++];
		}
	}

	return arr;
}

int* mergeSort(int* arr, int size){ //sorts in decreasing order
	if(size <= 1){
		return arr;
	}

	int size1 = size/2;
	int size2 = size - size1;

	int arr1[size1];
	int arr2[size2];

	for(int i = 0; i < size1; i++){
		arr1[i] = arr[i];
	}
	for(int i = 0; i < size2; i++){
		arr2[i] = arr[i+size1];
	}

	mergeSort(arr1, size1);
	mergeSort(arr2, size2);
	arr = merge(arr1, size1, arr2, size2, arr, size);
	return arr;
}

void greedyCoinChanging(int* d, float target, int size){
	//sort denominations in decreasing order
	d = mergeSort(d, size);

	int N = 0;
	int A[size];

	for(int i = 0; i < size; i++){
		A[i] = target/d[i];
		target -= A[i]*d[i];
		N += A[i];
	}
	if(target > 0){
		cout << "fail" << endl;
	}else{
		printCount(d, A, size, N);
	}
}

void dynamicCoinChanging(int* d, int target, int size){

	int **N;
	int **A;

	N = new int *[size];
	A = new int *[size];

	for(int i = 0; i < size; i++){
		N[i] = new int[target+1];
		A[i] = new int[target+1];
	}

	for(int t = 0; t <= target; t++){
		N[0][t] = t;
		A[0][t] = t;
	}

	for(int i = 1; i < size; i++){
		for(int t = 0; t <= target; t++){
			N[i][t] = N[i - 1][t];
			A[i][t] = 0;
			for(int j = 0; j <= t/d[i]; j++){
				int a = j + N[i - 1][t - j*d[i]];
				int b = N[i][t];
				if(a < b){
					N[i][t] = a;
					A[i][t] = j;
				}
			}
		}
	}

	int x[size];
	int t = target;

	for(int i = size - 1; i >= 0; i--){
		x[i] = A[i][t];
		t -= d[i]*A[i][t];
	}

	printCount(d, x, size, N[size - 1][target]);
}

int main(){
	int size = 10;
	int denominations[10] = {1, 5, 10, 100, 200, 500, 1000, 2000, 5000, 10000};
	
	int target;
	string type;
	
	cout << "What is the target?" << endl;
	cin >> target;
	
	cout << "Algorithm type? g for greedy, d for dynamic" << endl;
	cout << "Note default is greedy" << endl;

	cin >> type;
	if(type == "g"){
		greedyCoinChanging(denominations, target, size);
	} else{
		dynamicCoinChanging(denominations, target, size);
	}
}