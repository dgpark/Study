#include <iostream>
#include <fstream>

using namespace std;

int main(void)
{
	int U,D;
	
	ifstream inStream("exchange.inp");
	ofstream outStream("exchange.out");
	
	inStream >> U;
	inStream >> D;
	
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
	
	return 0;
}
