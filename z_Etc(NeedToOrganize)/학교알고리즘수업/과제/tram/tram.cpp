#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

class MinCost{
private:
	int cost[4];	//cost of Tram for each day 
	int tramDay;	//Day that use Tram	
	int day;	//the day 
	int count[365] = {0}; //times that use tram in a day. //initialization of array
	int minCost[365] = {0};//minCost of day. it is for using dynamic programming.
public:
	void readInput();
	void findMinCost();
	//later, check the usage of variable factor function.
	int findMin(int a, int b, int c);//find min of three
	int findMin(int a, int b, int c, int d); //find min of four	
	void writeOutput();
};

void MinCost::readInput(){
	ifstream inStream("3.inp");
	for(int i=0; i<4; ++i){
		inStream >> cost[i];
	}
	inStream >> tramDay;
	for(int i=0; i<tramDay; ++i){
		inStream >> day;
		inStream >> count[day];
	}
}

void MinCost::findMinCost(){
	for(int i=0; i<365; ++i){
		if(count[i] != 0){	//
			if(i == 0) { minCost[i] = min(cost[0]*count[i],cost[1]); } 
			else if((i+1)%7 == 0){
				if( (i+1) == 7 ){
					minCost[i] = findMin(cost[3], cost[2]+minCost[i-3],
					cost[1]+minCost[i-1], cost[0]*count[i]+minCost[i-1]);
				}
				else{
					minCost[i] = findMin(cost[3]+minCost[i-7],
				 	cost[2]+minCost[i-3],cost[1]+minCost[i-1],
					cost[0]*count[i]+minCost[i-1]);
				}
			}	
			else if((i+1) >= 3){
				if( (i+1) == 3){
					minCost[i] = findMin(cost[2], cost[1]+minCost[i-1],
					cost[0]*count[i]+minCost[i-1]);
				}
				else{
					minCost[i] = findMin(cost[2]+minCost[i-3],
					cost[1]+minCost[i-1], cost[0]*count[i]+minCost[i-1]);
				}				
	 		}
		}
		else{
			if(i!=0){minCost[i] = minCost[i-1];}	
		}
	}
	writeOutput();
}

int MinCost::findMin(int a, int b, int c){
	int temp;
	if(a >= b){temp = b;}
	else{temp = a;}

	if(temp >= c){temp = c;}
	return temp;
}

int MinCost::findMin(int a, int b, int c, int d){
	int temp;
	if(a>=b){temp=b;}
	else{temp = a;}

	if(temp >= c){temp = c;}

	if(temp >= d){temp = d;}

	return temp;
}

void MinCost::writeOutput(){
	ofstream outStream("test.out");
	outStream << minCost[364];	
} 

int main(void)
{
	MinCost mc;
	mc.readInput();
	mc.findMinCost();
	
	return 0;
}

