#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

class LCS{
private:
	int kNum;
	string input[3][2];
	int **lcsMatrix;
	int count[3][2];
public:
	void readInput();
	void checkLCS();
	void writeOutput();
	bool checkLastString(int num, int row, int col);
	int minValue(int a, int b);
	int maxValue(int a, int b);
	int maxValue(int a, int b, int c);
	void print();
};

void LCS::readInput(){
	ifstream inStream("2.inp");
	inStream >> kNum;
	for(int i=0; i<3; i++){
		for(int j=0; j <2; ++j){
			inStream >> input[i][j];
		}
		count[i][0] = input[i][0].length();
		count[i][1] = input[i][1].length();
	}	
}

int LCS::minValue(int a, int b){
	int minNum;
	minNum = min(a,b);

	return minNum;
}

int LCS::maxValue(int a, int b){
	int maxNum;
	maxNum = max(a,b);

	return maxNum;
}
int LCS::maxValue(int a, int b, int c){
	int maxNum;
	maxNum = max(max(a,b),c);

	return maxNum;
}

bool LCS::checkLastString(int num, int row, int col){
	bool check = false;
	for(int i=0; i < num; ++i){
		if(i>row){ break; }
		else if(input[i][0][row-i] == input[i][1][col]){
			check = true;
		}
		else if(input[i][0][row] == input[i][1][col-i]){
			check = true;
		}
	}
	for(int i=0; i < num; ++i){
		if(i>col){ break; }
		else if(input[i][0][row-i] == input[i][1][col]){
			check = true;
		}
		else if(input[i][0][row] == input[i][1][col-i]){
			check = true;
		}
	}
	return check;
}

void LCS::checkLCS(){
	ofstream outStream("music.out");
	
	int common=0;
	for(int i=0; i<3; ++i){
		int max=0;
		lcsMatrix = new int *[count[i][0]];
		
		for(int j=0; j<count[i][0]; ++j){
			lcsMatrix[j] = new int [count[i][1]];
		}
		
		for(int row=0; row<count[i][0]; ++row){
			for(int col=0; col<count[i][1]; ++col){
				if(row == 0 || col == 0){
					if(input[i][0][row] == input[i][1][col])
					{
						lcsMatrix[row][col] = 1;
					}
					else{ 
						if(checkLastString(kNum,row,col) == true){
							if(row==0 && col==0){
								lcsMatrix[row][col]=0;
							}
							else if(row == 0){
								lcsMatrix[row][col] = maxValue(lcsMatrix[row][col-1],0);
							}
							else if(col == 0){
								lcsMatrix[row][col] = maxValue(lcsMatrix[row-1][col],0);
							}
						}
						else{
							lcsMatrix[row][col] = 0;							
						} 
					}
				}
				else{
					if( input[i][0][row] == input[i][1][col] ){ // 같은문자열 
						lcsMatrix[row][col] = lcsMatrix[row-1][col-1]+1;
						if(lcsMatrix[row][col]>max){max=lcsMatrix[row][col];}
					}			
					else{ //row, col 모두 0이 아닐때  
						if(kNum == 1){
							lcsMatrix[row][col]=0;
						}
						else if((checkLastString(kNum,row,col) == true)){
							lcsMatrix[row][col] = maxValue(lcsMatrix[row-1][col], lcsMatrix[row][col-1]);
						}
						else{
							lcsMatrix[row][col] = 0;
						} 
					}
				}
			}
		}
		if(max >= (minValue(count[i][0], count[i][1])/3.0) ){
			outStream << "Plagia" << endl;
		}
		else{
			outStream << "Origin" << endl;
		}
	}
}

int main(void)
{
	LCS lcs;
	lcs.readInput();
	lcs.checkLCS();

	return 0;
}

