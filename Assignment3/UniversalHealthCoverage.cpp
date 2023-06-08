#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
using namespace std;

// returns whetrer chosen hospitals can cover all cities
bool isCovered(Set<string>& cities,  Vector< Set<string> >& result){
	Set<string> set;
	
	for(int i=0;i<result.size();i++){
		set+=result[i];
	}

	return set==cities;
}

bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
							   Vector< Set<string> >& result){

	if(numHospitals == 0){
		
		if(isCovered(cities,result)) return true;
		else return false;
		
	}
	
	if(locations.size()==0){ 
		return false;
	}
	
	// for each hospital, I form two kinds of sets, in the first one
	// I pick the hospital, in the second one - I don't. before I take a recursive step,
	// I save the chosen hospital in 'extraSet', add it in 'result' vector and remove
	// from 'location' vector, then I take recursive step.
	Set<string> extraSet;
	extraSet = locations[0];
	result.add(extraSet);
	locations.remove(0);
	
	if(canOfferUniversalCoverage(cities,locations,numHospitals-1, result)) return true;
	
	// before I take the second recursive step, in which I don't consider the hospital,
	// I remove it from the 'result' vector.
	result.remove(result.size()-1);
	
	if(canOfferUniversalCoverage(cities,locations,numHospitals, result)) return true;
	
	// after I take recursive step for the hospital, in which the hospital is
	// both considered and not, I put it back in 'locations' vector.
	locations.add(extraSet);
	
	return false;
}

int main() {

	Set<string> cities;
	Vector< Set<string> > locations;
	int numHospitals;
	Vector< Set<string> > result;

	if(canOfferUniversalCoverage(cities,locations,numHospitals,result)){
        for(int i=0; i<result.size(); i++){
            cout<<result[i]<<endl;
        }
    }

    return 0;
}
