#include <iostream>
#include <string>
#include <fstream>
#include "set.h"
#include "map.h"
#include "console.h"
using namespace std;

void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons);

Map<char, Set<string> > loadCodonMap();

//same function with extra parameter
void listAllRNAStrands(string protein, string result, Map<char, Set<string> >& codons){
	if(protein.size()==0){
		cout<<result<<endl;
	}

	foreach(string value in codons[protein[0]]){
		listAllRNAStrands(protein.substr(1,protein.length()-1),result+value,codons);
	}

	
}

int main() {
    /* Load the codon map. */
    Map<char, Set<string> > codons = loadCodonMap();
	string protein;
	cin>>protein;
	listAllRNAStrandsFor(protein,codons);
    return 0;
}

/* You do not need to change this function. */
Map<char, Set<string> > loadCodonMap() {
    ifstream input("codons.txt");
    Map<char, Set<string> > result;

    /* The current codon / protein combination. */
    string codon;
    char protein;

    /* Continuously pull data from the file until all data has been
     * read.
     */
    while (input >> codon >> protein) {
        result[protein] += codon;
    }

    return result;
}


void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons){
	string result ="";
	listAllRNAStrands(protein,result,codons);
}
