#include <iostream>
#include <fstream>

using namespace std;

class Diet{
private:
	int num;
	double **gred;
	int goal[4] = {0};
	int sum[5] = {0}; // Saved sum of each ingredient.
	int best[5] = {0}; // Saved best combination of ingredient
	bool visit[20] = {0}; // 20 is max number
	bool bestVisit[20] = {0}; //Saved Combination of Gredient.
	// If we find the best combination, Set bestVisit[i] = 1, Using visit[i] 
public:
	void readInput();
	void swap(double **gred1, double **gred2);
	void partition(double **gred1, int left, int right, int& pivot);
	void quickSort(double ** gred1, int left, int right);	
	
	void start();
	void backtracking(int *sum1); // At here, sum means sum[5] 
	void writeOutput();
};

void Diet::readInput(){
	ifstream inStream("1.inp");
	inStream >> num;
	
	gred = new double *[num];
	for(int i=0; i<num; i++){
		gred[i] = new double [6]; // change 5 to 6
		for(int j=0; j<5; j++){
			inStream >> gred[i][j];
			cout << gred[i][j] << " ";
		}
		gred[i][5] = 0;
		cout << endl;
	}
	
	for(int i=0; i<4; i++){
		inStream >> goal[i];
		cout << goal[i] << " ";
	}
	
	for(int i=0; i<num; i++){
		for(int j=0; j<4; j++){
			gred[i][5] += (gred[i][j] / gred[i][4]) ;
		}
	}
	
	quickSort(gred, 0, num-1);
	
	cout << endl;
	cout << endl;
	
	for(int i=0; i<num; i++){
		for(int j=0; j<6; j++){
			cout << gred[i][j] << " ";
		}
		cout << endl;
	}
}

void Diet::swap(double **gred1, double **gred2){
	double temp[6] = {0};
	
	for(int i=0; i<6; i++){
		temp[i] = gred1[0][i];
		gred1[0][i] = gred2[0][i];
		gred2[0][i] = temp[i];
	}
}

void Diet::partition(double **gred1, int left, int right, int &pivot){
	int i,j;
	double pivotItem;
	
	pivotItem = gred1[left][5];
	j = left;
	
	for(i = left+1; i <= right; i++){
		if(gred1[i][5] > pivotItem){
			j++;
			swap(&gred1[i], &gred1[j]);
		}
	}
	pivot = j;
	swap(&gred1[left], &gred1[pivot]);
}

void Diet::quickSort(double **gred1, int left, int right){
	int pivot;
	
	if(right > left){
		partition(gred1, left, right, pivot);
		quickSort(gred1, left, pivot-1);
		quickSort(gred1, pivot+1, right);
	}
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
			cout << i << ": " << sum1[0] << sum1[1] << sum1[2] << sum1[3] << " ";
			for(int j=0; j<5; j++){
				sum1[j] = sum1[j] + gred[i][j];
				//cout << "!!! " << sum1[j] << "!!! ";
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
			
			//cout << "backtracking" << i << endl;
			backtracking(sum1);
			visit[i] = 0;
			for(int j=0; j<5; j++){
				sum1[j] = sum1[j] - gred[i][j]; //ERROR
			}
		}
	}
}

void Diet::writeOutput(){
	ofstream outStream("test.out");
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


//


