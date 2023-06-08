/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
using namespace std;

int combinations(int n, int k){
	if(n==k) return 1;
	if(k==0) return 1;
	return combinations(n-1,k-1) + combinations(n-1,k);
}
int main() {
    // [TODO: fill in the code]
	int n;
	int k;
	cin>>n>>k;
	cout<<combinations(n,k)<<endl;
    return 0;
}
