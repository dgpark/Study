#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>

using namespace std;

class Trash{
private:
	int N;
	int *point; int *visit; int *route; int*bestRoute;
	int energy=0, bestEnergy=0, weight=0, r=1;
public:
	void readInput();
	void backTracking(int weight1, int energy1, int index);
	void start();
	void writeOutput();
};

void Trash::readInput(){
	ifstream inStream("3.inp");
	inStream >> N;
	
	point = new int[N];
	visit = new int[N];
	route = new int[N];
	bestRoute = new int[N];
	
	visit[0] = 1;
	route[0] = 1;
	bestRoute[0] = 1;
	
	for(int i=1; i<N; ++i){
		visit[i] = 0;
		route[i] = -1;
		bestRoute[i] = -1;
	}
	
	for(int i=0; i<N; ++i){
		inStream >> point[i];
	}
}

void Trash::backTracking(int weight1, int energy1, int index){
	int tempEnergy = 0;
	int tempWeight = 0;
	
	for(int i=1; i<N; ++i){
		if(visit[i] == 0){
			visit[i] = 1; route[r++] = i+1; tempEnergy = energy1;
			energy1 = energy1 + abs(((i+1)-index)*weight1);
			if(energy1 > bestEnergy && bestEnergy != 0){ // Cut1
				visit[i] = 0; r--;
				energy1 = tempEnergy;
				continue;
			}	
			else{
				if(weight1 + point[i] > 0){
					weight1 = weight1 + point[i];
					
					int leftCheck = weight1; // Cut2-1
					for(int k=1; k<N; ++k){
						if(visit[k] == 0){
							leftCheck += point[k];
						}
					}
					if(leftCheck > 0){ 
						visit[i] = 0; r--;
						weight1 = weight1 - point[i];
						energy1 = tempEnergy;
						continue;
					} // Cut2-1
					backTracking(weight1, energy1, i+1);
					visit[i] = 0; r--;
					weight1 = weight1 - point[i];
					energy1 = tempEnergy;
				}
				else{
					tempWeight = weight1;
					weight1 = 0;
						
					int leftCheck = weight1;
					for(int k=1; k<N; ++k){
						if(visit[k] == 0){
							leftCheck += point[k];
						}
					}
					if(leftCheck > 0){
						visit[i] = 0; r--;
						weight1 = tempWeight;
						energy1 = tempEnergy;
						continue;
					}
					
					backTracking(weight1, energy1, i+1);
					visit[i] = 0; r--;
					weight1 = tempWeight;
					energy1 = tempEnergy;
				}
			}		
		}
	}
	
	for(int i=N-1; i>0; --i){
		if(visit[i] == 0){
			return;
		}
	}
	
	if(bestEnergy == 0){
		bestEnergy = energy1;
		for(int i=0; i<N; ++i){
			bestRoute[i] = route[i];
		}
	}
	else if(energy1 < bestEnergy){
		bestEnergy = energy1;
		for(int i=0; i<N; ++i){
			bestRoute[i] = route[i];
		}
	}
}

void Trash::start(){
	backTracking(point[0], energy, 1);
}

void Trash::writeOutput(){
	ofstream outStream("trash.out");
	for(int i=0; i<N; ++i){
		outStream << bestRoute[i] << " ";
	}
	outStream << "1" << endl;
}

int main(void)
{
	Trash t;
	t.readInput();
	t.start();
	t.writeOutput();
	return 0;
}
