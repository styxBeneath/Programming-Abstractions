/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Consecutive Heads problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "random.h"
#include "console.h"
using namespace std;

int main() {
    // [TODO: fill in the code]
	 int heads = 0;
	 int tails = 0;
	 int counter = 0;

	while(true) {
		if(randomChance(0.5)) {
			cout<<"heads"<<endl;
			heads++;
			tails = 0;
		} else {
			cout<<"tails"<<endl;
			tails++;
			heads = 0;
		}
		
		counter++;

		if (heads == 3) {
			cout<<"It took "<<counter<<" flips to get 3 consecutive heads."<<endl;
			return 0;
		}

		if (tails == 3) {
			cout<<"It took "<<counter<<" flips to get 3 consecutive tails."<<endl;
			return 0;
		}
	}
    return 0;
}
