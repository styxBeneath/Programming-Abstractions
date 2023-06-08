#include <iostream>
#include <fstream>
#include <string>
#include "console.h"
#include "tokenscanner.h"
#include "simpio.h"
#include "filelib.h"
#include "vector.h"
#include "map.h"
#include "queue.h"
#include "random.h"

using namespace std;

const int numOfLetters = 2000;

string inputFile(){
	
	string file;
	ifstream stream;

	while (true) {
		
		cout<<"Enter the source text: ";
		cin>>file;
		
		if (openFile(stream,file)){
			stream.close();
			break;
		}

	}

	return file;
}

Vector<char> scanFile(string file){
	
	ifstream stream;
	Vector<char> res;
	char c;

	if(openFile(stream,file)){

		while (stream.get(c)) {
			res.add(c);
		}
	
		stream.close();
	
		return res;
	}
}

string queueToString(Queue<char> queue) {
	string res="";

	while(!queue.isEmpty())
		res+=queue.dequeue();

	return res;
}

Map<string,Vector<char>>  scanInformation(Vector<char> &text, int &order){
		
	Map<string,Vector<char>> res;
	Queue<char> queue;
	
	for (int i=0;i<order;i++)
		queue.enqueue(text[i]);

	for (int i=order;i<text.size();i++) {
		
		res[queueToString(queue)]+=text[i];
		queue.dequeue();
		queue.enqueue(text[i]);
	
	}

	return res;

}

string initialSequence(Map<string,Vector<char>> &map){
	
	int size =0;
	string res;

	foreach(string key in map){ //84

		if(map[key].size()>size){

		res=key;
		size = map[key].size();

		}

	}

	return res;
}
string finalSequence(string &initial, Map<string,Vector<char>> &map, int &order){ //92
	
	string nextSeq;
	string res;
	res =initial;
	
	for(int i=order;i<numOfLetters;i++){
		
		nextSeq = res.substr(i-order,i);
		if(!map.containsKey(nextSeq)) break;
		res+=map[nextSeq][randomInteger(0, map[nextSeq].size()-1)];

	}

	return res;
}
int main() {
	
	int order;
	string file;
	string initial;
	string result;
	Vector<char> vec;
	Map<string,Vector<char>> map;

	file = inputFile();

	cout<<"Enter the Markov order [1-10]: ";
	cin>>order;
	
	vec = scanFile(file);
	map = scanInformation(vec,order);
	
	initial = initialSequence(map);
	
	result = finalSequence(initial,map,order);

	cout<<result<<endl;

	return 0;
}
