#include <iostream>
#include "console.h"
#include "lexicon.h"
#include <string>
#include "vector.h"
#include "queue.h"
#include "set.h"
#include "stack.h"

using namespace std;

Vector<string> equivalentWords(string &word, Lexicon &lex){
	
	Vector<string> res;
	
	for(int i=0;i<word.length();i++){
		for(int j='a';j<='z';j++){
			
			string s=word;
			s[i]=j;
			
			if(lex.contains(s)) 
				if(s!=word)	
					res.add(s);
		}
	}

	return  res;
}

Stack<string> wordLadder(string &start, string &end, Lexicon &lex){
	
	Vector<string> v;
	Stack<string> res;
	Stack<string> stack1;
	Queue<Stack<string>> queue;
	Set<string> set;
	
	set.add(start);
	res.push(start);
	queue.enqueue(res);
	
	while(!queue.isEmpty()){

		res = queue.dequeue();
		if(res.peek()==end)
			return res;
		
		v = equivalentWords(res.peek(),lex);
		
		for(int i=0;i<v.size();i++){

			if(!set.contains(v[i])){
				
				stack1 = res;
				stack1.push(v[i]);
				queue.enqueue(stack1);
				set.add(v[i]);
			
			}

		}

	}

	res.clear();
	return res;
	
}

int main() {
	string start;
	string end;
	Stack<string> res;
	Lexicon lex("EnglishWords.dat");
	
	
	cout<<"Enter the starting word: ";
	cin>>start;

	cout<<"Enter the ending word: ";
	cin>>end;

	if(start.length()!=end.length()) 
		cout<<"No word ladder could be found."<<endl;
	else{
		res = wordLadder(start,end,lex);
		
		if(res.isEmpty())
			cout<<"No word ladder could be found."<<endl;
		else 
			cout<<"Ladder found: "<<res.toString()<<endl;
	}

    return 0;
}
