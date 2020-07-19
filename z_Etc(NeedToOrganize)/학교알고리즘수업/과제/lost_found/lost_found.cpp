#include <iostream>
#include <fstream>

using namespace std;

int main(void)
{
	int maxNum;
	ifstream inStream("lost_found.inp");
	ofstream outStream("lost_found.out");
	inStream >> maxNum;
	
	int saveNum[maxNum-2];
	int checkNum[maxNum-2];
	int solution[2];
	int j;
	
	for(int i=0; i<maxNum-2; i++)
	{
		inStream >> saveNum[i];
		checkNum[saveNum[i]] = saveNum[i];
	}
	
	for(int i=1; i<maxNum+1; i++)
	{
		if(checkNum[i] != i)
		{
			outStream << i << " ";
		}
	}
	
	
	return 0;
}
