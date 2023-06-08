/*
 * File: FleschKincaid.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Flesch-Kincaid problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <fstream>
#include <string>
#include "console.h"
#include "tokenscanner.h"
#include "simpio.h"
#include "filelib.h"
using namespace std;
bool isVowel(char ch) {
	if (ch=='a' || ch=='e' || ch=='i' || ch=='o' || ch=='u' || ch=='y'){
		return true;
	}

	if (ch=='A' || ch=='E' || ch=='I' || ch=='O' || ch=='U' || ch=='Y'){
		return true;
	}
	return false;
}

bool hasVowel(string word) {
	for (int i=0;i<word.length();i++){
		if (isVowel(word[i])){
			return true;
		}
	}
	return false;
}


bool isAWord(string word){
	if ((word[0]>='a' && word[0]<='z') || (word[0]>='A' && word[0]<='Z')){
			if(hasVowel(word)){
			return true;
			}
	}
		return false;
}
int numOfWords(string line) {
	int counter = 0;
	TokenScanner scanner(line);
	scanner.ignoreWhitespace();
	while (scanner.hasMoreTokens()) {
		string word = scanner.nextToken();
		if (isAWord(word)){
			counter++;
			}	
	}
	return counter;
}
bool hasSentenceSign(string str) {
	for (int i=0;i<str.length();i++){
		if (str[i]=='!' || str[i]=='.' || str[i]=='?'){
			return true;
		}
	}

	return false;
}
int numOfSentences(string line) {
	int counter = 0;
	TokenScanner scanner(line);
	scanner.ignoreWhitespace();
	while (scanner.hasMoreTokens()) {
		if (hasSentenceSign(scanner.nextToken()))
			counter++;
	}

	return counter;
}

int syllablesInWord(string word) {
	int counter=0;
	for (int i=0;i<word.length();i++) {
		if (isVowel(word[i])) {
			if (i!=(word.length()-1)) {
				if (!isVowel(word[i+1])){
					counter++;
				}
			} else {
				if (word[i]!='e'){
					counter++;
				}
			}
		}
	}

	if (counter==0 && hasVowel(word)){
		counter = 1;
	}
	return counter;
}

int numOfSyllables(string line) {
	int counter = 0;
	TokenScanner scanner(line);
	scanner.ignoreWhitespace();
	while (scanner.hasMoreTokens()) {
		counter+=syllablesInWord(scanner.nextToken());
	}

	return counter;

}


const double C0=-15.59;
const double C1=0.39;
const double C2=11.8;

int main() {
    // [TODO: fill in the code]
	double words =0;
	double sentences = 0;
	double syllables =0;
	string file;
	ifstream stream;
	string line;
	while (true) {
		cout<<"Enter file name: "<<endl;
		cin>>file;
		if (openFile(stream,file))
			break;
	}
	while (getline(stream,line)) {
		words+=numOfWords(line);
		sentences+=numOfSentences(line);
		syllables+=numOfSyllables(line);
	}
	stream.close();
	if (sentences==0) sentences=1;
	if (words==0) words=1;

	double grade = C0+C1*(words/sentences)+C2*(syllables/words);
	cout<<"grade level: "<<grade<<endl;
	//cout<<words<<endl;
	//cout<<syllables<<endl;
	//cout<<sentences<<endl;
	

    return 0;
}
