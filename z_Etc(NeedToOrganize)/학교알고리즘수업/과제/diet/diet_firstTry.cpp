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
	// If we find the best combination, Set bestVisit[i] = 1, Using visit[i] 
public:
	void readInput();
	int getNum();
	void start();
	void backtracking(int *sum1); // At here, sum means sum[5] 
	void writeOutput();
};

void Diet::readInput(){
	ifstream inStream("diet.inp");
	inStream >> num;
	
	gred = new int *[num];
	for(int i=0; i<num; i++){
		gred[i] = new int [5];
		for(int j=0; j<5; j++){
			inStream >> gred[i][j];
		}
	}
	
	for(int i=0; i<4; i++){
		inStream >> goal[i];
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
	
	if(best[4] != 0 && best[4] < sum1[4]){
		return;
	}
	
	for(int i=0; i<num; i++){
		if(visit[i] == 0){
			visit[i] = 1;
			for(int j=0; j<5; j++){
				sum1[j] = sum1[j] + gred[i][j];
			}
			
			for(int j=0; j<4; j++){
				if(sum1[j] >= goal[j]){
					if(j==3){
						if(best[4] == 0){
							for(int temp=0; temp<5; temp++){
								best[temp] = sum1[temp];
							}
							for(int temp2=0; temp2<20; temp2++){
								bestVisit[temp2] = visit[temp2];
							}
						}
						else if(best[4] > sum1[4]){
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
							else if(bvCount == 0 && vCount == 0 ){
								for(int save=0; save<5; save++){
									best[save] = sum1[save];
								}
						
								for(int save2=0; save2<20; save2++){
									bestVisit[save2] = visit[save2];
								}
							}
							else if(bvCount == vCount){
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
						}//
					}
				} // end of if loop
				else{ // if sum1[j] < goal[j] break the loop.
					break;
				}
			}
			
			backtracking(sum1);
			visit[i] = 0;
			for(int j=0; j<5; j++){
				sum1[j] = sum1[j] - gred[i][j];
			}
		}
	}
}


void Diet::writeOutput(){
	ofstream outStream("diet.out");
	cout << endl;
	for(int i=0; i<5; i++){
		cout << best[i] << " ";
	}
	
	for(int i=0; i<20; i++){
		if(bestVisit[i] == 1){
			outStream << i+1 << " ";
		}
	}
}

int main(void)
{	
	Diet d;
	d.readInput();
	d.start();
	d.writeOutput();
	
	return 0;
}


