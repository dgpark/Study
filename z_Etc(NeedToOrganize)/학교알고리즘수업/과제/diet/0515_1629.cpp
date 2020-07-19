#include <iostream>
#include <fstream>

using namespace std;

class Diet{
private:
	int num;
	int **gred;
	int goal[4] = {0};
	int sum[5] = {0}; // Saved sum of each ingredient.
	int best[5] = {0}; // Saved best combination of ingredient
	bool visit[20] = {0}; // 20 is max number
	bool bestVisit[20] = {0}; //Saved Combination of Gredient.
	// If we find the best combination, Set C[20] = 1, Using Visit[i] 
public:
	void readInput();
	int getNum();
	void start();
	void backtracking(int *sum1); // At here, sum means sum[5] 
	void check(int n);
};

void Diet::readInput(){
	ifstream inStream("1.inp");
	inStream >> num;
	
	gred = new int *[num];
	for(int i=0; i<num; i++){
		gred[i] = new int [5];
		for(int j=0; j<5; j++){
			inStream >> gred[i][j];
			cout << gred[i][j] << " ";
		}
		cout << endl;
	}
	
	for(int i=0; i<4; i++){
		inStream >> goal[i];
		cout << goal[i] << " ";
	}
}

int Diet::getNum(){
	return num;
}

void Diet::start(){
	backtracking(sum);
}

void Diet::backtracking(int *sum1){
	int bvCount = 0, vCount = 0;
	//check if sum1 is satisfying goal or not.
	for(int i=0; i<4; i++){
		if(sum1[i] >= goal[i]){
			if(i==3){
				return;
			}
		}
		else{ // Combination is not satisfying goal yet.
			if(best[4] > sum1[4]){
				for(int j=0; j<5; j++){
					best[j] = sum1[j];
				}
				
				for(int save=0; save<20; save++){
					bestVisit[save] = visit[save];
				}
			}
			else if(best[4] == sum1[4]){
				for(int k=0; k<20; k++){
					if(bestVisit[k] == 1){
						bvCount++;
					}
					if(visit[k] == 1){
						vCount++;
					}
				}
				if(bvCount > vCount){
					for(int j=0; j<5; j++){
						best[j] = sum1[j];
					}
					
					for(int save=0; save<20; save++){
						bestVisit[save] = visit[save];
					}
				}
				
				if(bvCount == vCount){
					for(int save=0; save<20; save++){
						if(bestVisit[save] != 1 && visit[save] == 1){
							for(int save2=0; save2<5; save2++){
								best[save2] = sum1[save2];
							}
							
							for(int save2=0; save2<20; save2++){
								bestVisit[save2] = visit[save2];
							}
							break;
						}
						else if(bestVisit[save] == 1 && visit[save] != 1){
							break;
						}
					}
				}
			}
			break; //if one of sum1 is less than goal, do else part. and then, break the original for loop.
		}
	}
	
	for(int i=0; i<num; i++){
		if(visit[i] == 0){
			visit[i] = 1;
			for(int j=0; j<5; j++){
				sum1[j] = sum1[j] + gred[i][j];
			}
			backtracking(sum1);
			visit[i] = 0;
		}
	}
}


/*
void Diet::check(int n){
	int x[n];
	
	for(int i=0; i<n; i++){
		x[i] = i;
		cout << x[i];// Container to get a Combination
	}
	
	//while(n>0){
		for(int i=0; i<num; i++){
			for(int j=0; j<5; j++){
				
			}
		}
		
		if(x[0] == num-(n+1)){
			break;
		}
	}
}*/


int main(void)
{	
	Diet d;
	d.readInput();
	d.start();
	//d.check(5);
	/*for(int i=0; i<d.getNum(); i++){
		check(i);
	}
	*/
	
	return 0;
}


//


