#include <iostream>
#include <fstream>

using namespace std;

int main(void)
{
	long long U, D;
	//double U, D;
	double eNum, checkNum;
	
	ifstream inStream("3.inp");
	ofstream outStream("test.out");
	
	inStream >> U;
	inStream >> D;
	
	cout << U << " " << D << endl;
	
	eNum = U/D;
	checkNum = 0;
	cout << eNum << endl;
	
	
	for(int i=2; U>0; ++i){
		if(U*i > 1*D ){
			U = U*i - 1*D;
			D = D*i;
			cout << i << " ";
			outStream << i << " ";
		}
		else if(U*i - 1*D == 0){
			U = U*i - 1*D;
			D = D*i;
			cout << i;
			outStream << i;
			break;
		}
	}
	
	/*
	for(double i=2; eNum != checkNum; i++){
		if( ((1/i)+checkNum) < eNum ){
			checkNum = checkNum + 1/i;
			outStream << i << " ";
			cout << i;
		}
		else if( ((1/i)+checkNum) == eNum )
		{
			break;
		}
	}
	*/
	
	return 0;
}
