#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>

using namespace std;

/*

Energy = weight * distance
Start from 1 -> visit all spots -> come back to 1 with empty state

> How to branch the case?
1) if W == 0 at the trash dump point, Visit that point later.
//2) If possible, make Weight 0 at the farthest point

3) When revisit point 1, if W is not 0, Don't save that.

4) save best case. and if result is worse than best case, pass that result.
-> It means, If the case Energy is bigger than best case, stop backtracking at that point.

> Needed variables
1) int N (number of point)
2) int *point (point = new int[N];), int *bestRoute (save values of each point)
int *visit;
3) int energy(W*(abs(index N - index N-k) + 1), 
weight(can be change when it visit each point)
int bestEnergy;

//When I do backtracking, After make visit = 1 -> visit = 0
make weight = weight - point[index N]; 
//distance is the index+1 of point

*/

class Trash{
private:
	int N;
	int *point; int *visit; int *route; int*bestRoute;
	int energy=0, bestEnergy=0, weight=0, r=1; //tempWeight=0, tempEnergy=0;
public:
	void readInput();
	void backTracking(int weight1, int energy1, int index);
	void start();
	void writeOutput();
};

void Trash::readInput(){
	ifstream inStream("1.inp");
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
	
	//memset(visit, 0, sizeof(visit));
	//memset(route, -1, sizeof(route));
	//memset(bestRoute, -1, sizeof(bestRoute));
	
	
	for(int i=0; i<N; ++i){
		inStream >> point[i];
	}
	
	cout << N << endl;
	for(int i=0; i<N; ++i){
		cout << point[i] << " ";
	}
}

void Trash::backTracking(int weight1, int energy1, int index){
	int tempEnergy = 0;
	int tempWeight = 0;
	if(energy1 > bestEnergy && bestEnergy != 0){
		//cout << " !";
		return;
	}
	int leftCheck = weight1;
	for(int i=1; i<N; ++i){
		if(visit[i] == 0){
			leftCheck += point[i];
		}
	}
	if(leftCheck > 0){return;}
	
	for(int i=1; i<N; ++i){
		if(visit[i] == 0){
			visit[i] = 1; route[r++] = i+1; tempEnergy = energy1;
			energy1 = energy1 + abs(((i+1)-index)*weight1);				
			if(weight1 + point[i] > 0){
				weight1 = weight1 + point[i];
				backTracking(weight1, energy1, i+1);
				visit[i] = 0; r--;
				weight1 = weight1 - point[i];
				energy1 = tempEnergy;
			}
			else{
				tempWeight = weight1;
				weight1 = 0;
				backTracking(weight1, energy1, i+1);					visit[i] = 0; r--;
				weight1 = tempWeight;
				energy1 = tempEnergy;
			}
			
		}
	}
	
	for(int i=1; i<N; ++i){
		if(visit[i] == 0){
			return;
		}
	}
	
	if(bestEnergy == 0){
		bestEnergy = energy1;
		cout << "bestEnergy1: " << bestEnergy;
		for(int i=0; i<N; ++i){
			cout << "answer: " << route[i] << " ";
			bestRoute[i] = route[i];
		}
		cout << endl;
	}
	else if(energy1 < bestEnergy){
		bestEnergy = energy1;
		for(int i=0; i<N; ++i){
			cout << "??" << route[i] << " ";
			bestRoute[i] = route[i];
		}
		cout << endl;
	}
}

void Trash::start(){
	backTracking(point[0], energy, 1);
}

void Trash::writeOutput(){
	ofstream outStream("test.out");
	cout << "bestEnergy: " << bestEnergy << endl;
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
