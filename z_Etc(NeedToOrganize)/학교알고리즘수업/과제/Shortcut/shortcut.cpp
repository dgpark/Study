#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

class MinDistance{
private:
	double Point[3][3]; 
	double midPoint[3];
	double distance1, distance2, midDistance=-1;
	double minDistance;
public:
	void readInput();
	void findMin();
	void recursiveFind(double (*tPoint)[3], double *tDistance1, double *tDistance2);
	void writeOutput();
};

void MinDistance::readInput(){
	ifstream inStream("shortcut.inp");
	for(int i=0; i<3; ++i)
		for(int j=0; j<3; ++j)
			inStream >> Point[i][j];
	distance1 = pow(pow(Point[2][0]-Point[0][0],2) + pow(Point[2][1]-Point[0][1],2) + pow(Point[2][2]-Point[0][2],2), 0.5);
	distance2 = pow(pow(Point[2][0]-Point[1][0],2) + pow(Point[2][1]-Point[1][1],2) + pow(Point[2][2]-Point[1][2],2), 0.5);
}

void MinDistance::findMin(){
	recursiveFind(Point, &distance1, &distance2);
	writeOutput();
}

void MinDistance::recursiveFind(double (*tPoint)[3], double *tDistance1, double *tDistance2){
	for(int i=0; i<3; ++i)
		midPoint[i] = 0.5*(tPoint[0][i]) + 0.5*(tPoint[1][i]);
	midDistance = pow(pow(tPoint[2][0]-midPoint[0],2) + pow(tPoint[2][1]-midPoint[1],2) + pow(tPoint[2][2]-midPoint[2],2), 0.5);
	if(*tDistance1 == *tDistance2){
		minDistance = midDistance;
		return;
	}
	else if( (ceil(*tDistance1) == ceil(midDistance) && ceil(*tDistance2) == ceil(midDistance) ) && abs(tDistance1 - tDistance2) <= 1){
		minDistance = midDistance;
		return;
	}
		
	if(*tDistance1<*tDistance2){
		for(int i=0; i<3; ++i)
			tPoint[1][i] = midPoint[i];
		*tDistance2 = midDistance;
		recursiveFind(tPoint, &distance1, &distance2);
		return;
	}
	else{
		for(int i=0; i<3; ++i)
			tPoint[0][i] = midPoint[i];
		*tDistance1 = midDistance;
		recursiveFind(tPoint, &distance1, &distance2);
		return;
	}
}

void MinDistance::writeOutput(){
	ofstream outStream("shortcut.out");
	outStream << ceil(minDistance) << endl;
}

int main(void)
{
	MinDistance md;
	md.readInput();
	md.findMin();
	
	return 0;
}
