#include <iostream>
#include <string>
#include "console.h"

using namespace std;

bool isSubsequence(string text, string subsequence) {
	
	//base case
	if(text.length()==0 && subsequence.length()==0) return true;
	else if(text.length()==0) return false;
	else if(subsequence.length()==0) return true;
	
	//recursive decomposition
	if(text[0]==subsequence[0]) return isSubsequence(text.substr(1,text.size()-1),subsequence.substr(1,subsequence.size()-1));
	
	else return isSubsequence(text.substr(1,text.size()-1),subsequence);

}

int main() {

    string text;
	string subsequence;
	
	cin>>text;
	cin>>subsequence;
	
	cout<<isSubsequence(text,subsequence)<<endl;
	
    return 0;
}
